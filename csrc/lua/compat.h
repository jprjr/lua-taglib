#ifndef LTAGLIB_LUA_COMPAT_INCLUDE_GUARD
#define LTAGLIB_LUA_COMPAT_INCLUDE_GUARD

#include "../shared/attrs.h"

extern "C" {

#include <lua.h>
#include <lauxlib.h>

}

#if LUA_VERSION_NUM < 502
#define lua_getuservalue(L, i) \
  (lua_getfenv((L), (i)), lua_type((L), -1))

#define lua_setuservalue(L, i) \
  (luaL_checktype((L), -1, LUA_TTABLE), lua_setfenv((L), (i)))
#endif

#if LUA_VERSION_NUM == 502
#define lua_rawgetp(L, idx, key) (lua_rawgetp( (L), (idx), (key)), lua_type(L, -1))
#endif

#if LUA_VERSION_NUM < 503

#define lua_getfield(L, idx, key) (lua_getfield( (L), (idx), (key)), lua_type(L, -1))
#define lua_gettable(L, idx) (lua_gettable( (L), (idx)), lua_type(L, -1))

#endif

namespace LuaTagLib {

#if LUA_VERSION_NUM < 502

#if !defined(luaL_newlibtable)
LTAGLIB_PRIVATE
void luaL_setfuncs(lua_State* L, const luaL_Reg* l, int nup);
#endif

LTAGLIB_PRIVATE
void* luaL_testudata(lua_State* L, int idx, const char* tname);

LTAGLIB_PRIVATE
int lua_absindex(lua_State* L, int idx);

LTAGLIB_PRIVATE
int luaL_getsubtable(lua_State* L, int idx, const char* field);

LTAGLIB_PRIVATE
void luaL_requiref(lua_State* L, const char* modname, lua_CFunction openf, int glb);

LTAGLIB_PRIVATE
int lua_rawgetp(lua_State* L, int idx, const void* key);

LTAGLIB_PRIVATE
void lua_rawsetp(lua_State* L, int idx, const void* key);
#endif

#if LUA_VERSION_NUM < 503

LTAGLIB_PRIVATE
int lua_isinteger(lua_State* L, int idx);

LTAGLIB_PRIVATE
int lua_geti(lua_State* L, int idx, lua_Integer i);

#endif

#if LUA_VERSION_NUM < 504
LTAGLIB_PRIVATE
int luaL_typeerror(lua_State* L, int arg, const char* tname);
#endif

}

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_pairs(lua_State* L);

LTAGLIB_PUBLIC
int luaopen_TagLib_ipairs(lua_State* L);

}

#endif

