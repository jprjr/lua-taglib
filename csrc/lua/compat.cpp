#include "compat.h"

namespace LuaTagLib {

#if LUA_VERSION_NUM < 502

#if !defined(luaL_newlibtable)
LTAGLIB_PRIVATE
void luaL_setfuncs(lua_State* L, const luaL_Reg* l, int upvals) {
    int i;
    while(l->name != NULL) {
        lua_pushstring(L, l->name);
        for(i = 0; i < upvals; ++i) {
            lua_pushvalue(L, -(upvals + 1));
        }
        lua_pushcclosure(L, l->func, upvals);
        lua_settable(L, -(upvals + 3));
        l++;
    }
    lua_pop(L, upvals);
}
#endif

LTAGLIB_PRIVATE
void* luaL_testudata(lua_State* L, int idx, const char* tname) {
    int res = 0;
    void* p = lua_touserdata(L, idx);

    if(p == NULL || !lua_getmetatable(L, idx)) return NULL;

    luaL_getmetatable(L, tname);
    res = lua_rawequal(L, -1, -2);
    lua_pop(L, 2);
    return res ? p : NULL;
}

LTAGLIB_PRIVATE
int lua_absindex(lua_State* L, int idx) {
    if(idx < 0 && idx > LUA_REGISTRYINDEX) {
        idx += lua_gettop(L) + 1;
    }
    return idx;
}

LTAGLIB_PRIVATE
int luaL_getsubtable(lua_State* L, int idx, const char* field) {
    int abs_idx = lua_absindex(L, idx);
    lua_pushstring(L, field);
    lua_gettable(L, abs_idx);
    if(lua_istable(L, -1)) return 1;
    lua_pop(L, 1);
    lua_newtable(L);
    lua_pushstring(L, field);
    lua_pushvalue(L, -2);
    lua_settable(L, abs_idx);
    return 0;
}

LTAGLIB_PRIVATE
void luaL_requiref(lua_State* L, const char* modname, lua_CFunction openf, int glb) {
    luaL_getsubtable(L, LUA_REGISTRYINDEX, "_LOADED");
    if(lua_getfield(L, -1, modname) == LUA_TNIL) {
        lua_pop(L, 1);
        lua_pushcfunction(L, openf);
        lua_pushstring(L, modname);
        lua_call(L, 1, 1);
        lua_pushvalue(L, -1);
        lua_setfield(L, -3, modname);
    }
    if(glb) {
        lua_pushvalue(L, -1);
        lua_setglobal(L, modname);
    }
    lua_replace(L, -2);
}

LTAGLIB_PRIVATE
int lua_rawgetp(lua_State* L, int idx, const void* key) {
    idx = lua_absindex(L, idx);
    lua_pushlightuserdata(L, (void*) key);
    lua_rawget(L, idx);
    return lua_type(L, -1);
}

LTAGLIB_PRIVATE
void lua_rawsetp(lua_State* L, int idx, const void* key) {
    idx = lua_absindex(L, idx);
    lua_pushlightuserdata(L, (void*) key);
    lua_insert(L, -2);
    lua_rawset(L, idx);
}

#endif


#if LUA_VERSION_NUM < 503
LTAGLIB_PRIVATE
int lua_isinteger(lua_State* L, int idx) {
    if(lua_type(L, idx) == LUA_TNUMBER) {
        lua_Number n = lua_tonumber(L, idx);
        lua_Integer i = lua_tointeger(L, idx);
        return n == i;
    }
    return 0;
}

LTAGLIB_PRIVATE
int lua_geti(lua_State* L, int idx, lua_Integer i) {
    idx = lua_absindex(L, idx);
    lua_pushinteger(L, i);
    lua_gettable(L, idx);
    return lua_type(L, -1);
}
#endif

#if LUA_VERSION_NUM < 504
LTAGLIB_PRIVATE int
luaL_typeerror(lua_State* L, int idx, const char* tname) {
    const char* msg;
    const char* type;

    if(luaL_getmetafield(L, idx, "__name")) {
        type = lua_tostring(L, -1);
    } else {
        switch(lua_type(L, idx)) {
            case LUA_TLIGHTUSERDATA: {
                type = "light userdata"; break;
            }
            default: type = luaL_typename(L, idx);
        }
    }
    msg = lua_pushfstring(L, "%s expected, got %s", tname, type);
    return luaL_argerror(L, idx, msg);
}
#endif

}

#if LUA_VERSION_NUM < 502
static int pairs_wrapper(lua_State* L) {
    lua_settop(L,1);
    if(!luaL_getmetafield(L, 1, "__pairs")) {
        lua_pushvalue(L, lua_upvalueindex(1));
    }
    lua_insert(L,-2);
    lua_call(L,1,LUA_MULTRET);
    return lua_gettop(L);
}

static int ipairs_wrapper(lua_State* L) {
    lua_settop(L,1);
    if(!luaL_getmetafield(L, 1, "__ipairs")) {
        lua_pushvalue(L, lua_upvalueindex(1));
    }
    lua_insert(L,-2);
    lua_call(L,1,LUA_MULTRET);
    return lua_gettop(L);
}
#endif

LTAGLIB_PUBLIC
int luaopen_TagLib_pairs(lua_State* L) {
    lua_getglobal(L, "pairs");
#if LUA_VERSION_NUM < 502
    lua_pushcclosure(L, pairs_wrapper, 1);
#endif
    return 1;
}

LTAGLIB_PUBLIC
int luaopen_TagLib_ipairs(lua_State* L) {
    lua_getglobal(L, "ipairs");
#if LUA_VERSION_NUM < 502
    lua_pushcclosure(L, ipairs_wrapper, 1);
#endif
    return 1;
}
