#include "xingheader.h"

#include "mpegheader.h"
#include "../tbytevector.h"

using namespace LuaTagLib;

static int XingHeader__call(lua_State* L) {
    int args = lua_gettop(L);
    TagLib::MPEG::XingHeader* x = NULL;

    switch(args) {
        case 1: {
            x = new TagLib::MPEG::XingHeader(ByteVector::looseValue(L, 2));
            break;
        }
        default: break;
    }

    if(x == NULL) return luaL_error(L, "invalid arguments");
    MPEG::XingHeader::pushPtr(L, x);
    return 1;
}

#if LTAGLIB_HAS_MPEG_XINGHEADER_TYPE
static int XingHeader_type(lua_State* L) {
    TagLib::MPEG::XingHeader* x = MPEG::XingHeader::checkPtr(L, 1);
    MPEG::XingHeader::HeaderType::pushValue(L, x->type());
    return 1;
}
#endif

static int XingHeader_isValid(lua_State* L) {
    TagLib::MPEG::XingHeader* x = MPEG::XingHeader::checkPtr(L, 1);
    lua_pushboolean(L, x->isValid());
    return 1;
}

static int XingHeader_totalFrames(lua_State* L) {
    TagLib::MPEG::XingHeader* x = MPEG::XingHeader::checkPtr(L, 1);
    lua_pushinteger(L, x->totalFrames());
    return 1;
}

static int XingHeader_totalSize(lua_State* L) {
    TagLib::MPEG::XingHeader* x = MPEG::XingHeader::checkPtr(L, 1);
    lua_pushinteger(L, x->totalSize());
    return 1;
}

static
const luaL_Reg XingHeader__index[] = {
#if LTAGLIB_HAS_MPEG_XINGHEADER_TYPE
    { "type", XingHeader_type },
#endif
    { "isValid", XingHeader_isValid },
    { "totalFrames", XingHeader_totalFrames },
    { "totalSize", XingHeader_totalSize },
    { NULL, NULL }
};

#if LTAGLIB_UNDER(LTAGLIB_1_12)
static int XingHeader_static_xingHeaderOffset(lua_State* L) {
    lua_pushinteger(L, TagLib::MPEG::XingHeader::xingHeaderOffset(
      MPEG::Header::Version::checkValue(L, 1),
      MPEG::Header::ChannelMode::checkValue(L, 2)
    ));
    return 1;
}
#endif

static const luaL_Reg XingHeader__static[] = {
#if LTAGLIB_UNDER(LTAGLIB_1_12)
    { "xingHeaderOffset", XingHeader_static_xingHeaderOffset },
#endif
    { NULL, NULL }
};

static int XingHeader__submodules(lua_State* L) {
#if LTAGLIB_HAS_MPEG_XINGHEADER_TYPE
    luaL_requiref(L, "TagLib.MPEG.XingHeader.HeaderType", luaopen_TagLib_MPEG_XingHeader_HeaderType, 0);
    lua_setfield(L, -2, "HeaderType");
#else
    (void)L;
#endif
    return 0;
}

LTAGLIB_PUBLIC
int luaopen_TagLib_MPEG_XingHeader(lua_State *L) {
    return MPEG::XingHeader::open(L);
}

template<>
const UserdataTable MPEG::XingHeader::base::mod = {
    XingHeader__call, /* call */
    XingHeader__static, /* __index */
    XingHeader__submodules, /* init */
};

template<>
const UserdataMetatable MPEG::XingHeader::base::metatable = {
    "TagLib::MPEG::XingHeader", /* name */
    XingHeader__index, /* indextable */
    NULL, /* indexfunc */
};

#if LTAGLIB_HAS_MPEG_XINGHEADER_TYPE

#define E(x) { #x, sizeof(#x) - 1, TagLib::MPEG::XingHeader::x }

static const MPEG::XingHeader::HeaderType::enum_type headerType[] = {
    E(Invalid), E(Xing), E(VBRI)
};

LTAGLIB_PUBLIC
int luaopen_TagLib_MPEG_XingHeader_HeaderType(lua_State* L) {
    return MPEG::XingHeader::HeaderType::open(L);
}

template<>
const MPEG::XingHeader::HeaderType::enum_type*
MPEG::XingHeader::HeaderType::m_values = headerType;

template<>
const size_t MPEG::XingHeader::HeaderType::m_len = sizeof(headerType) / sizeof(headerType[0]);

#include "../shared/enum.tcc"
template class Enum<TagLib::MPEG::XingHeader::HeaderType>;

#endif

#include "../shared/userdata.tcc"
template class BaseUserdata<TagLib::MPEG::XingHeader>;
