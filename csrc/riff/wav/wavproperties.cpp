#include "wavproperties.h"

#if LTAGLIB_HAS_RIFF_WAV_PROPERTIES

#include "../../tbytevector.h"
#if LTAGLIB_ATLEAST(LTAGLIB_1_10)
#include "wavfile.h"
#endif

#define T RIFF::WAV::Properties
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
#if LTAGLIB_ATLEAST(LTAGLIB_1_10)
            if(RIFF::WAV::File::isValid(L,1)) {
                p = new TT(RIFF::WAV::File::checkPtr(L,1), AudioProperties::ReadStyle::checkValue(L, 2));
                break;
            }
#endif
#if LTAGLIB_UNDER(LTAGLIB_1_12)
            p = new TT(ByteVector::looseValue(L, 1), AudioProperties::ReadStyle::checkValue(L, 2));
#endif
            break;
        }
#if LTAGLIB_ATLEAST(LTAGLIB_1_7) && LTAGLIB_UNDER(LTAGLIB_1_12)
        case 3: {
            p = new TT(ByteVector::looseValue(L, 1), luaL_checkinteger(L, 2), AudioProperties::ReadStyle::checkValue(L, 3));
            break;
        }
#endif
        default: break;
    }

    if(p == NULL) return luaL_error(L, "invalid arguments");
    T::pushPtr(L, p);
    return 1;
}

#if LTAGLIB_ATLEAST(LTAGLIB_1_7) && LTAGLIB_UNDER(LTAGLIB_1_12)
static int Properties_sampleWidth(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->sampleWidth());
    return 1;
}
#endif

#if LTAGLIB_ATLEAST(LTAGLIB_1_8)
static int Properties_sampleFrames(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->sampleFrames());
    return 1;
}
#endif

#if LTAGLIB_ATLEAST(LTAGLIB_1_10)
static int Properties_bitsPerSample(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->bitsPerSample());
    return 1;
}

static int Properties_format(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->format());
    return 1;
}
#endif

static const luaL_Reg Properties__index[] = {
#if LTAGLIB_ATLEAST(LTAGLIB_1_7) && LTAGLIB_UNDER(LTAGLIB_1_12)
    { "sampleWidth", Properties_sampleWidth },
#endif
#if LTAGLIB_ATLEAST(LTAGLIB_1_8)
    { "sampleFrames", Properties_sampleFrames },
#endif
#if LTAGLIB_ATLEAST(LTAGLIB_1_10)
    { "bitsPerSample", Properties_bitsPerSample },
    { "format", Properties_format },
#endif
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_RIFF_WAV_Properties(lua_State *L) {
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
#include "../../shared/userdata.tcc"
template class DerivedUserdata<TagLib::RIFF::WAV::Properties, LuaTagLib::AudioProperties>;

#endif
