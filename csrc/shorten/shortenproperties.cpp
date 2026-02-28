#include "shortenproperties.h"

#define T Shorten::Properties
#define TT TagLib::T
#define XSTR(s) STR(s)
#define STR(s) #s
#define NAME XSTR(TT)

using namespace LuaTagLib;

/* no __call function - the constructor depends on
 * an undefined struct type (PropertyValues),
 * since that's not available I'm going to assume
 * that the constructor isn't really part of the
 * public API. */

static int Properties_shortenVersion(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->shortenVersion());
    return 1;
}

static int Properties_fileType(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->fileType());
    return 1;
}

static int Properties_bitsPerSample(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->bitsPerSample());
    return 1;
}

static int Properties_sampleFrames(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->sampleFrames());
    return 1;
}

static
const luaL_Reg Properties__index[] = {
    { "shortenVersion", Properties_shortenVersion },
    { "fileType", Properties_fileType },
    { "bitsPerSample", Properties_bitsPerSample },
    { "sampleFrames", Properties_sampleFrames },
    { NULL, NULL },
};

LTAGLIB_PUBLIC
int luaopen_TagLib_Shorten_Properties(lua_State *L) {
    return T::open(L);
}

template<>
const UserdataTable Shorten::Properties::base::mod = {
    NULL, /* __call */
    NULL, /* __index */
    NULL, /* init */
};

template<>
const UserdataMetatable Shorten::Properties::base::metatable = {
    NAME, /* name */
    Properties__index, /* indextable */
    NULL, /* indexfunc */
};

#undef T
#include "../shared/userdata.tcc"
template class LuaTagLib::DerivedUserdata<TagLib::Shorten::Properties, LuaTagLib::AudioProperties>;

