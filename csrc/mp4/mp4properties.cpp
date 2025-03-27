#include "mp4properties.h"

#if LTAGLIB_HAS_MP4

#include "mp4file.h"
#include "../tbytevector.h"

#define T MP4::Properties
#define TT TagLib::T
#define XSTR(s) STR(s)
#define STR(s) #s
#define NAME XSTR(TT)

using namespace LuaTagLib;

/* no __call function - the constructor depends on
 * a TagLib::MP4::Atoms pointer, the headers state
 * that's not part of the public API. I'm not going
 * to stress about using parts of a private API */

static int Properties_bitsPerSample(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->bitsPerSample());
    return 1;
}

#if LTAGLIB_ATLEAST(LTAGLIB_1_8)
static int Properties_isEncrypted(lua_State* L) {
    lua_pushboolean(L, T::checkPtr(L,1)->isEncrypted());
    return 1;
}
#endif

#if LTAGLIB_ATLEAST(LTAGLIB_1_10)
static int Properties_codec(lua_State* L) {
    T::Codec::pushValue(L, T::checkPtr(L,1)->codec());
    return 1;
}
#endif

static
const luaL_Reg Properties__index[] = {
    { "bitsPerSample", Properties_bitsPerSample },
#if LTAGLIB_ATLEAST(LTAGLIB_1_8)
    { "isEncrypted", Properties_isEncrypted },
#endif
#if LTAGLIB_ATLEAST(LTAGLIB_1_10)
    { "codec", Properties_codec },
#endif
    { NULL, NULL }
};

static int Properties__submodules(lua_State* L) {
#if LTAGLIB_ATLEAST(LTAGLIB_1_10)
    luaL_requiref(L, "TagLib.MP4.Properties.Codec", luaopen_TagLib_MP4_Properties_Codec, 0);
    lua_setfield(L, -2, "Codec");
#else
    (void) L;
#endif
    return 0;
}

LTAGLIB_PUBLIC
int luaopen_TagLib_MP4_Properties(lua_State *L) {
    return T::open(L);
}

#if LTAGLIB_ATLEAST(LTAGLIB_1_10)
LTAGLIB_PUBLIC
int luaopen_TagLib_MP4_Properties_Codec(lua_State *L) {
    return T::Codec::open(L);
}
#endif

template<>
const UserdataTable MP4::Properties::base::mod = {
    NULL,
    NULL,
    Properties__submodules,
};

template<>
const UserdataMetatable MP4::Properties::base::metatable = {
    NAME, /* name */
    Properties__index, /* indextable */
    NULL, /* indexfunc */
};

#undef T

#if LTAGLIB_ATLEAST(LTAGLIB_1_10)

#define E(x) { #x, sizeof(#x) - 1, TagLib::MP4::Properties::x }
static const MP4::Properties::Codec::enum_type mp4Codec[] = {
    E(Unknown), E(AAC), E(ALAC)
};

template<>
const MP4::Properties::Codec::enum_type* MP4::Properties::Codec::m_values = mp4Codec;

template<>
const size_t MP4::Properties::Codec::m_len = sizeof(mp4Codec) / sizeof(mp4Codec[0]);

#include "../shared/enum.tcc"
template class LuaTagLib::Enum<TagLib::MP4::Properties::Codec>;

#endif

#include "../shared/userdata.tcc"
template class LuaTagLib::DerivedUserdata<TagLib::MP4::Properties, LuaTagLib::AudioProperties>;

#endif
