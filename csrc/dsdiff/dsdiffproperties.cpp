#include "dsdiffproperties.h"

#if LTAGLIB_HAS_DSDIFF_PROPERTIES

#include "../tbytevector.h"

#define T DSDIFF::Properties
#define TT TagLib::T
#define XSTR(s) STR(s)
#define STR(s) #s
#define NAME XSTR(TT)

using namespace LuaTagLib;

static int Properties__call(lua_State* L) {
    int args = lua_gettop(L);
    TT* p = NULL;

    switch(args) {
        case 5: {
            p = new TT(
              /* samplerate, channels, samplescount, bitrate */
              luaL_checkinteger(L,1), luaL_checkinteger(L,2),
              luaL_checkinteger(L,3), luaL_checkinteger(L,4),
              AudioProperties::ReadStyle::checkValue(L,5));
            break;
        }
        default: break;
    }

    if(p == NULL) return luaL_error(L, "invalid arguments");
    T::pushPtr(L, p);
    return 1;
}

static int Properties_bitsPerSample(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->bitsPerSample());
    return 1;
}

static int Properties_sampleCount(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->sampleCount());
    return 1;
}

static
const luaL_Reg Properties__index[] = {
    { "bitsPerSample", Properties_bitsPerSample },
    { "sampleCount", Properties_sampleCount },
    { NULL, NULL },
};


LTAGLIB_PUBLIC
int luaopen_TagLib_DSDIFF_Properties(lua_State *L) {
    return T::open(L);
}

template<>
const UserdataTable DSDIFF::Properties::base::mod = {
    Properties__call,
    NULL,
    NULL,
};

template<>
const UserdataMetatable T::base::metatable = {
    NAME, /* name */
    Properties__index, /* indextable */
    NULL, /* indexfunc */
};

#undef T
#include "../shared/userdata.tcc"
template class LuaTagLib::DerivedUserdata<TagLib::DSDIFF::Properties, LuaTagLib::AudioProperties>;

#endif
