#include "modproperties.h"

#if LTAGLIB_HAS_MOD_PROPERTIES

#include "../tbytevector.h"

#define T Mod::Properties
#define TT TagLib::T
#define XSTR(s) STR(s)
#define STR(s) #s
#define NAME XSTR(TT)

using namespace LuaTagLib;

static int Properties__call(lua_State* L) {
    int args = lua_gettop(L);
    TT* p = NULL;

    switch(args) {
        case 1: {
            p = new TT(AudioProperties::ReadStyle::checkValue(L, 1));
            break;
        }
        default: break;
    }

    if(p == NULL) return luaL_error(L, "invalid arguments");
    T::pushPtr(L,p);
    return 1;
}

static int Properties_instrumentCount(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->instrumentCount());
    return 1;
}

static int Properties_lengthInPatterns(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->lengthInPatterns());
    return 1;
}

static int Properties_setChannels(lua_State* L) {
    T::checkPtr(L,1)->setChannels(luaL_checkinteger(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Properties_setInstrumentCount(lua_State* L) {
    T::checkPtr(L,1)->setInstrumentCount(luaL_checkinteger(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Properties_setLengthInPatterns(lua_State* L) {
    T::checkPtr(L,1)->setLengthInPatterns(luaL_checkinteger(L, 2));
    lua_settop(L,1);
    return 1;
}

static
const luaL_Reg Properties__index[] = {
    { "instrumentCount", Properties_instrumentCount },
    { "lengthInPatterns", Properties_lengthInPatterns },
    { "setInstrumentCount", Properties_setInstrumentCount },
    { "setChannels", Properties_setChannels },
    { "setLengthInPatterns", Properties_setLengthInPatterns },
    { NULL, NULL },
};


LTAGLIB_PUBLIC
int luaopen_TagLib_Mod_Properties(lua_State *L) {
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
template class DerivedUserdata<TagLib::Mod::Properties, LuaTagLib::AudioProperties>;

#endif
