#include "flacproperties.h"

#include "../tbytevector.h"
#if LTAGLIB_UNDER(LTAGLIB_1_2)
#include "flacfile.h"
#endif

#define T FLAC::Properties
#define TT TagLib::T
#define XSTR(s) STR(s)
#define STR(s) #s
#define NAME XSTR(TT)

using namespace LuaTagLib;

static int Properties__call(lua_State* L) {
    int args = lua_gettop(L);
    TT* p = NULL;

#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,2,0)
    switch(args) {
        case 2: {
            p = new TT(ByteVector::looseValue(L, 1), luaL_checkinteger(L, 2));
            break;
        }
        case 3: {
            p = new TT(ByteVector::looseValue(L, 1), luaL_checkinteger(L, 2), AudioProperties::ReadStyle::checkValue(L, 3));
            break;
        }
#else
    switch(args) {
        case 1: {
            p = new TT(FLAC::File::checkPtr(L, 1));
            break;
        }
        case 2: {
            p = new TT(FLAC::File::checkPtr(L, 1), AudioProperties::ReadStyle::checkValue(L, 2));
            break;
        }
#endif
        default: break;
    }
    if(p == NULL) return luaL_error(L, "invalid arguments");
    FLAC::Properties::pushPtr(L, p);
    return 1;
}

#if LTAGLIB_VERSION < LTAGLIB_VERSION_NUM(1,12,0)
static int Properties_sampleWidth(lua_State* L) {
    TT* ap = T::checkPtr(L, 1);
    lua_pushinteger(L, ap->sampleWidth());
    return 1;
}
#endif

#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,10,0)
static int Properties_bitsPerSample(lua_State* L) {
    TT* ap = T::checkPtr(L, 1);
    lua_pushinteger(L, ap->bitsPerSample());
    return 1;
}
#endif

#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,8,0)
static int Properties_sampleFrames(lua_State* L) {
    TT* ap = T::checkPtr(L, 1);
    lua_pushinteger(L, ap->sampleFrames());
    return 1;
}
#endif

#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,7,0)
static int Properties_signature(lua_State* L) {
    TT* ap = T::checkPtr(L, 1);
    ByteVector::pushValue(L, ap->signature());
    return 1;
}
#endif

static
const luaL_Reg Properties__index[] = {
#if LTAGLIB_VERSION < LTAGLIB_VERSION_NUM(1,12,0)
    { "sampleWidth", Properties_sampleWidth },
#endif
#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,10,0)
    { "bitsPerSample", Properties_bitsPerSample },
#endif
#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,8,0)
    { "sampleFrames", Properties_sampleFrames },
#endif
#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,7,0)
    { "signature", Properties_signature },
#endif
    { NULL, NULL },
};

LTAGLIB_PUBLIC
int luaopen_TagLib_FLAC_Properties(lua_State *L) {
    return T::open(L);
}

template<>
const UserdataTable FLAC::Properties::base::mod = {
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
template class DerivedUserdata<TagLib::FLAC::Properties, LuaTagLib::AudioProperties>;
