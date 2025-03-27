#include "flacmetadatablock.h"

#if LTAGLIB_HAS_FLAC_METADATABLOCK

#include "../tbytevector.h"

using namespace LuaTagLib;

static int MetadataBlock_code(lua_State* L) {
    TagLib::FLAC::MetadataBlock* block = FLAC::MetadataBlock::checkPtr(L, 1);
    lua_pushinteger(L, block->code());
    return 1;
}

static int MetadataBlock_render(lua_State* L) {
    TagLib::FLAC::MetadataBlock* block = FLAC::MetadataBlock::checkPtr(L, 1);
    ByteVector::pushValue(L, block->render());
    return 1;
}

static
const luaL_Reg MetadataBlock__index[] = {
    { "code", MetadataBlock_code },
    { "render", MetadataBlock_render },
    { NULL, NULL }
};

static int MetadataBlock__submodules(lua_State* L) {
    luaL_requiref(L, "TagLib.FLAC.MetadataBlock.BlockType",
      luaopen_TagLib_FLAC_MetadataBlock_BlockType, 0);
    lua_setfield(L, -2, "BlockType");
    return 0;
}

#define E(x) { #x, sizeof(#x) - 1, TagLib::FLAC::MetadataBlock::x }
static const FLAC::MetadataBlock::BlockType::enum_type blockTypes[] = {
    E(StreamInfo), E(Padding), E(Application), E(SeekTable),
    E(VorbisComment), E(CueSheet), E(Picture)
};

LTAGLIB_PUBLIC
int luaopen_TagLib_FLAC_MetadataBlock_BlockType(lua_State* L) {
    return FLAC::MetadataBlock::BlockType::open(L);
}


LTAGLIB_PUBLIC
int luaopen_TagLib_FLAC_MetadataBlock(lua_State* L) {
    return FLAC::MetadataBlock::open(L);
}

template<>
const UserdataTable FLAC::MetadataBlock::base::mod = {
    NULL,
    NULL,
    MetadataBlock__submodules,
};

template<>
const UserdataMetatable FLAC::MetadataBlock::base::metatable = {
    "TagLib::FLAC::MetadataBlock", /* name */
    MetadataBlock__index, /* indextable */
    NULL, /* indexfunc */
};


template<>
const FLAC::MetadataBlock::BlockType::enum_type*
FLAC::MetadataBlock::BlockType::m_values = blockTypes;

template<>
const size_t FLAC::MetadataBlock::BlockType::m_len = sizeof(blockTypes) / sizeof(blockTypes[0]);

#include "../shared/enum.tcc"
template class LuaTagLib::Enum<TagLib::FLAC::MetadataBlock::BlockType>;

#include "../shared/userdata.tcc"
template class LuaTagLib::BaseUserdata<TagLib::FLAC::MetadataBlock>;

#endif
