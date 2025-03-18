#include "tversionnumber.h"

#include "taglib.h"

#define LTAGLIB_HAVE_VERSIONNUMBER (LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(2,0,0))

#if LTAGLIB_HAVE_VERSIONNUMBER
#include <tversionnumber.h>
#endif

using namespace LuaTagLib;

static const char LTAGLIB_VERSIONNUMBER[] = "TagLib::VersionNumber";

static int luaTagLib_VersionNumber_Metatable(lua_State* L);

static int isud(lua_State* L, int idx) {
    int ok;
    if(! (lua_type(L, idx) == LUA_TTABLE) ) return 0;
    if(!lua_getmetatable(L, idx)) return 0;
    luaTagLib_VersionNumber_Metatable(L);
    ok = lua_rawequal(L, -1, -2);
    lua_pop(L, 2);
    return ok;
}

static void check(lua_State* L, int idx) {
    if(!isud(L, idx)) {
        luaL_typeerror(L, idx, LTAGLIB_VERSIONNUMBER);
    }
}

static int __tostring(lua_State* L) {
    unsigned int version;
    check(L, 1);
    lua_getfield(L, 1, "version");
    version = luaL_checkinteger(L, -1);
    lua_pop(L, 1);

    lua_pushfstring(L, "%d.%d.%d",
      ( (version >> 16) & 0xFF),
      ( (version >> 8) & 0xFF),
      ( version & 0xFF));
    return 1;
}

static int __lt(lua_State* L) {
    unsigned int v1;
    unsigned int v2;

    check(L, 1);
    check(L, 2);

    lua_getfield(L, 1, "version");
    v1 = luaL_checkinteger(L, -1);
    lua_getfield(L, 2, "version");
    v2 = luaL_checkinteger(L, -1);
    lua_pop(L, 2);

    lua_pushboolean(L, v1 < v2);
    return 1;
}

static int __le(lua_State* L) {
    unsigned int v1;
    unsigned int v2;

    check(L, 1);
    check(L, 2);

    lua_getfield(L, 1, "version");
    v1 = luaL_checkinteger(L, -1);
    lua_getfield(L, 2, "version");
    v2 = luaL_checkinteger(L, -1);
    lua_pop(L, 2);

    lua_pushboolean(L, v1 <= v2);
    return 1;
}

static int __eq(lua_State* L) {
    unsigned int v1;
    unsigned int v2;

    if(!( isud(L,1) && isud(L,2))) {
        lua_pushboolean(L, 0);
        return 1;
    }

    lua_getfield(L, 1, "version");
    v1 = luaL_checkinteger(L, -1);
    lua_getfield(L, 2, "version");
    v2 = luaL_checkinteger(L, -1);
    lua_pop(L, 2);

    lua_pushboolean(L, v1 == v2);
    return 1;
}

static const luaL_Reg meta_methods[] = {
    { "__tostring", __tostring },
    { "__lt", __lt },
    { "__le", __le },
    { "__eq", __eq },
    { NULL, NULL }
};

static int majorVersion(lua_State* L) {
    unsigned int version;
    check(L, 1);
    lua_getfield(L, 1, "version");
    version = luaL_checkinteger(L, -1);
    lua_pop(L, 1);
    lua_pushinteger(L, (version >> 16 ) & 0xFF);
    return 1;
}

static int minorVersion(lua_State* L) {
    unsigned int version;
    check(L, 1);
    lua_getfield(L, 1, "version");
    version = luaL_checkinteger(L, -1);
    lua_pop(L, 1);
    lua_pushinteger(L, (version >> 8 ) & 0xFF);
    return 1;
}

static int patchVersion(lua_State* L) {
    unsigned int version;
    check(L, 1);
    lua_getfield(L, 1, "version");
    version = luaL_checkinteger(L, -1);
    lua_pop(L, 1);
    lua_pushinteger(L, version & 0xFF);
    return 1;
}

static const luaL_Reg index_methods[] = {
    { "majorVersion", majorVersion },
    { "minorVersion", minorVersion },
    { "patchVersion", patchVersion },
    { NULL, NULL}
};

static int luaTagLib_VersionNumber_Metatable(lua_State* L) {
    if(luaL_newmetatable(L, LTAGLIB_VERSIONNUMBER)) {
        lua_pushstring(L, LTAGLIB_VERSIONNUMBER);
        lua_setfield(L, -2, "__name");

        luaL_setfuncs(L, meta_methods, 0);

        lua_newtable(L);
        luaL_setfuncs(L, index_methods, 0);
        lua_setfield(L, -2, "__index");
    }

    return 1;
}

static int luaTagLib_VersionNumber__call(lua_State* L) {
    unsigned int major = luaL_checkinteger(L, 1);
    unsigned int minor = luaL_checkinteger(L, 2);
    unsigned int patch = luaL_optinteger(L, 3, 0);

    lua_newtable(L);
    lua_pushinteger(L, ((major << 16) & 0xFF0000) | ((minor << 8) & 0xFF00) | (patch & 0xFF));
    lua_setfield(L, -2, "version");

    luaTagLib_VersionNumber_Metatable(L);
    lua_setmetatable(L, -2);
    return 1;
}

static int callWrap(lua_State* L) {
    int args = lua_gettop(L) - 1;
    lua_pushvalue(L, lua_upvalueindex(1));
    lua_replace(L, 1);
    lua_call(L, args, LUA_MULTRET);
    return lua_gettop(L);
}

LTAGLIB_PUBLIC
int luaopen_TagLib_VersionNumber(lua_State* L) {
    lua_newtable(L);
    lua_newtable(L);
    lua_pushcclosure(L, luaTagLib_VersionNumber__call, 0);
    lua_pushcclosure(L, callWrap, 1);
    lua_setfield(L, -2, "__call");
    lua_setmetatable(L, -2);
    return 1;
}

static int
luaTagLib_compiletimeVersion(lua_State *L) {
    lua_newtable(L);
    lua_pushinteger(L, LTAGLIB_VERSION);
    lua_setfield(L, -2, "version");

    luaTagLib_VersionNumber_Metatable(L);
    lua_setmetatable(L, -2);
    return 1;
}

LTAGLIB_PUBLIC
int luaopen_TagLib_compiletimeVersion(lua_State* L) {
    lua_pushcclosure(L, luaTagLib_compiletimeVersion, 0);
    return 1;
}

static int
luaTagLib_runtimeVersion(lua_State *L) {
#if LTAGLIB_HAVE_VERSIONNUMBER
    TagLib::VersionNumber v = TagLib::runtimeVersion();
    lua_newtable(L);
    lua_pushinteger(L, v.combinedVersion());
    lua_setfield(L, -2, "version");

    luaTagLib_VersionNumber_Metatable(L);
    lua_setmetatable(L, -2);
#else
    lua_pushnil(L);
#endif
    return 1;
}

LTAGLIB_PUBLIC
int luaopen_TagLib_runtimeVersion(lua_State* L) {
    lua_pushcclosure(L, luaTagLib_runtimeVersion, 0);
    return 1;
}

