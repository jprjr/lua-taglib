#include "aiffproperties.h"

#if LTAGLIB_HAS_RIFF_AIFF_PROPERTIES

#include "../../tbytevector.h"

#if LTAGLIB_ATLEAST(LTAGLIB_1_10)
#include "../../tstring.h"
#include "aifffile.h"
#endif

#define T RIFF::AIFF::Properties
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
            if(RIFF::AIFF::File::isValid(L,1)) {
                p = new TT(RIFF::AIFF::File::checkPtr(L,1), AudioProperties::ReadStyle::checkValue(L, 2));
                break;
            }
#endif
#if LTAGLIB_UNDER(LTAGLIB_1_12)
            p = new TT(ByteVector::looseValue(L, 1), AudioProperties::ReadStyle::checkValue(L, 2));
#endif
            break;
        }
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

static int Properties_isAiffC(lua_State* L) {
    lua_pushboolean(L, T::checkPtr(L,1)->isAiffC());
    return 1;
}

static int Properties_compressionType(lua_State* L) {
    ByteVector::pushValue(L, T::checkPtr(L,1)->compressionType());
    return 1;
}

static int Properties_compressionName(lua_State* L) {
    String::pushValue(L, T::checkPtr(L,1)->compressionName());
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
    { "isAiffC", Properties_isAiffC },
    { "compressionType", Properties_compressionType },
    { "compressionName", Properties_compressionName },
#endif
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_RIFF_AIFF_Properties(lua_State *L) {
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
template class LuaTagLib::DerivedUserdata<TagLib::RIFF::AIFF::Properties, LuaTagLib::AudioProperties>;

#endif
