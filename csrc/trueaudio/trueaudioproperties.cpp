#include "trueaudioproperties.h"

#if LTAGLIB_HAS_TRUEAUDIO_PROPERTIES

#include "../tbytevector.h"

#define T TrueAudio::Properties
#define TT TagLib::T
#define XSTR(s) STR(s)
#define STR(s) #s
#define NAME XSTR(TT)

using namespace LuaTagLib;

static int Properties__call(lua_State* L) {
    int args = lua_gettop(L);
    TT* p = NULL;

    switch(args) {
        case 2: {
            p = new TT(ByteVector::looseValue(L, 1), luaL_checkinteger(L, 2));
            break;
        }
        case 3: {
            p = new TT(ByteVector::looseValue(L, 1), luaL_checkinteger(L, 2), AudioProperties::ReadStyle::checkValue(L, 3));
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

static int Properties_ttaVersion(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->ttaVersion());
    return 1;
}

#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,8,0)
static int Properties_sampleFrames(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->sampleFrames());
    return 1;
}
#endif

static
const luaL_Reg Properties__index[] = {
    { "bitsPerSample", Properties_bitsPerSample },
    { "ttaVersion", Properties_ttaVersion },
#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,8,0)
    { "sampleFrames", Properties_sampleFrames },
#endif
    { NULL, NULL },
};

LTAGLIB_PUBLIC
int luaopen_TagLib_TrueAudio_Properties(lua_State *L) {
    return T::open(L);
}

template<>
const UserdataTable T::base::mod = {
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
template class DerivedUserdata<TagLib::TrueAudio::Properties, LuaTagLib::AudioProperties>;

#endif
