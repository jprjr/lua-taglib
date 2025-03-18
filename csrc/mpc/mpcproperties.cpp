#include "mpcproperties.h"

#if LTAGLIB_HAS_MPC_PROPERTIES

#include "../tbytevector.h"
#if LTAGLIB_ATLEAST(LTAGLIB_1_8)
#include "mpcfile.h"
#endif

#define T MPC::Properties
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
#if LTAGLIB_ATLEAST(LTAGLIB_1_8)
            if(MPC::File::isValid(L,1)) {
                p = new TT(MPC::File::checkPtr(L,1), luaL_checkinteger(L, 2));
                break;
            }
#endif
#if LTAGLIB_UNDER(LTAGLIB_2_0)
            p = new TT(ByteVector::looseValue(L, 1), luaL_checkinteger(L, 2));
#endif
            break;
        }
        case 3: {
#if LTAGLIB_ATLEAST(LTAGLIB_1_8)
            if(MPC::File::isValid(L,1)) {
                p = new TT(MPC::File::checkPtr(L,1), luaL_checkinteger(L, 2), AudioProperties::ReadStyle::checkValue(L, 3));
                break;
            }
#endif
#if LTAGLIB_UNDER(LTAGLIB_2_0)
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

static int Properties_mpcVersion(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->mpcVersion());
    return 1;
}

#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,8,0)
static int Properties_sampleFrames(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->sampleFrames());
    return 1;
}

static int Properties_totalFrames(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->totalFrames());
    return 1;
}

static int Properties_trackGain(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->trackGain());
    return 1;
}

static int Properties_trackPeak(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->trackPeak());
    return 1;
}

static int Properties_albumGain(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->albumGain());
    return 1;
}

static int Properties_albumPeak(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->albumPeak());
    return 1;
}
#endif

static
const luaL_Reg Properties__index[] = {
    { "mpcVersion", Properties_mpcVersion },
#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,8,0)
    { "sampleFrames", Properties_sampleFrames },
    { "totalFrames", Properties_totalFrames },
    { "trackGain", Properties_trackGain },
    { "trackPeak", Properties_trackPeak },
    { "albumGain", Properties_albumGain },
    { "albumPeak", Properties_albumPeak },
#endif
    { NULL, NULL },
};

LTAGLIB_PUBLIC
int luaopen_TagLib_MPC_Properties(lua_State *L) {
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
template class DerivedUserdata<TagLib::MPC::Properties, LuaTagLib::AudioProperties>;

#endif
