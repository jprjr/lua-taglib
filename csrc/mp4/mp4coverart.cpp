#include "mp4coverart.h"

#if LTAGLIB_HAS_MP4_COVERART

using namespace LuaTagLib;

static int CoverArt__call(lua_State* L) {
    int args = lua_gettop(L);
    TagLib::MP4::CoverArt* c = NULL;

    switch(args) {
        case 1: {
            c = new TagLib::MP4::CoverArt(MP4::CoverArt::checkValue(L,1));
            break;
        }
        case 2: {
            c = new TagLib::MP4::CoverArt(MP4::CoverArt::Format::checkValue(L, 1),
              ByteVector::looseValue(L, 2));
            break;
        }
        default: break;
    }

    if(c == NULL) return luaL_error(L, "invalid arguments");
    MP4::CoverArt::pushPtr(L, c);
    return 1;
}

static int CoverArt_format(lua_State* L) {
    MP4::CoverArt::Format::pushValue(L,
      MP4::CoverArt::checkPtr(L,1)->format());
    return 1;
}

static int CoverArt_data(lua_State* L) {
    ByteVector::pushValue(L,
      MP4::CoverArt::checkPtr(L,1)->data());
    return 1;
}

#if LTAGLIB_ATLEAST(LTAGLIB_1_11)
static int CoverArt_swap(lua_State* L) {
    MP4::CoverArt::checkPtr(L,1)->swap(MP4::CoverArt::checkValue(L,2));
    lua_settop(L,1);
    return 1;
}
#endif

static const luaL_Reg CoverArt__index[] = {
    { "format", CoverArt_format },
    { "data", CoverArt_data },
#if LTAGLIB_ATLEAST(LTAGLIB_1_11)
    { "swap", CoverArt_swap },
#endif
    { NULL, NULL }
};

#define E(x) { #x, sizeof(#x) - 1, TagLib::MP4::CoverArt::x }
static const MP4::CoverArt::Format::enum_type coverArtFormat[] = {
    E(JPEG), E(PNG)
#if LTAGLIB_ATLEAST(LTAGLIB_1_8)
    , E(BMP), E(GIF)
#endif
#if LTAGLIB_ATLEAST(LTAGLIB_1_9)
    , E(Unknown)
#endif
};

static int CoverArt__submodules(lua_State* L) {
    luaL_requiref(L, "TagLib.MP4.CoverArt.Format", luaopen_TagLib_MP4_CoverArt_Format, 0);
    lua_setfield(L, -2, "Format");
    return 0;
}

LTAGLIB_PUBLIC int
luaopen_TagLib_MP4_CoverArt(lua_State* L) {
    return MP4::CoverArt::open(L);
}

LTAGLIB_PUBLIC int
luaopen_TagLib_MP4_CoverArt_Format(lua_State* L) {
    return MP4::CoverArt::Format::open(L);
}

template<>
const UserdataTable MP4::CoverArt::base::mod = {
    CoverArt__call,
    NULL,
    CoverArt__submodules,
};

template<>
const UserdataMetatable MP4::CoverArt::base::metatable = {
    "TagLib::MP4::CoverArt", /* name */
    CoverArt__index, /* indextable */
    NULL, /* indexfunc */
};


template<>
const MP4::CoverArt::Format::enum_type* MP4::CoverArt::Format::m_values = coverArtFormat;

template<>
const size_t MP4::CoverArt::Format::m_len = sizeof(coverArtFormat) / sizeof(coverArtFormat[0]);

#include "../shared/enum.tcc"
template class Enum<TagLib::MP4::CoverArt::Format>;

#include "../shared/userdata.tcc"
template class BaseUserdata<TagLib::MP4::CoverArt>;

#endif
