#include "wavpackproperties.h"

#if LTAGLIB_HAS_WAVPACK_PROPERTIES

#include "../tbytevector.h"
#include "../audioproperties.h"

#if LTAGLIB_ATLEAST(LTAGLIB_1_7)
#include "wavpackfile.h"
#endif

#define T WavPack::Properties
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
#if LTAGLIB_ATLEAST(LTAGLIB_1_7)
            if(WavPack::File::isValid(L,1)) {
                p = new TT(WavPack::File::checkPtr(L,1), luaL_checkinteger(L, 2));
                break;
            }
#endif
#if LTAGLIB_UNDER(LTAGLIB_1_12)
            p = new TT(ByteVector::looseValue(L, 1), luaL_checkinteger(L, 2));
#endif
            break;
        }
        case 3: {
#if LTAGLIB_ATLEAST(LTAGLIB_1_7)
            if(WavPack::File::isValid(L,1)) {
                p = new TT(WavPack::File::checkPtr(L,1), luaL_checkinteger(L, 2), AudioProperties::ReadStyle::checkValue(L,3));
                break;
            }
#endif
#if LTAGLIB_UNDER(LTAGLIB_1_12)
            p = new TT(ByteVector::looseValue(L, 1), luaL_checkinteger(L, 2), AudioProperties::ReadStyle::checkValue(L, 3));
#endif
            break;
        }
        default: break;
    }

    if(p == NULL) return luaL_error(L, "invalid arguments");
    T::pushPtr(L, p);
    return 1;
}

static int Properties_bitsPerSample(lua_State* L) {
    TT* ap = T::checkPtr(L, 1);
    lua_pushinteger(L, ap->bitsPerSample());
    return 1;
}

static int Properties_version(lua_State* L) {
    TT* ap = T::checkPtr(L, 1);
    lua_pushinteger(L, ap->version());
    return 1;
}

#if LTAGLIB_ATLEAST(LTAGLIB_1_8)
static int Properties_sampleFrames(lua_State* L) {
    TT* ap = T::checkPtr(L, 1);
    lua_pushinteger(L, ap->sampleFrames());
    return 1;
}
#endif

#if LTAGLIB_ATLEAST(LTAGLIB_1_10)
static int Properties_isLossless(lua_State* L) {
    lua_pushboolean(L, T::checkPtr(L,1)->isLossless());
    return 1;
}
#endif

static
const luaL_Reg Properties__index[] = {
    { "bitsPerSample", Properties_bitsPerSample },
    { "version", Properties_version },
#if LTAGLIB_ATLEAST(LTAGLIB_1_8)
    { "sampleFrames", Properties_sampleFrames },
#endif
#if LTAGLIB_ATLEAST(LTAGLIB_1_10)
    { "isLossless", Properties_isLossless },
#endif
    { NULL, NULL },
};


LTAGLIB_PUBLIC
int luaopen_TagLib_WavPack_Properties(lua_State *L) {
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
template class DerivedUserdata<TagLib::WavPack::Properties, LuaTagLib::AudioProperties>;

#endif
