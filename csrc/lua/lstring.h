#ifndef LTAGLIB_LSTRING_INCLUDE_GUARD
#define LTAGLIB_LSTRING_INCLUDE_GUARD

#include "../shared/lua.h"

namespace LuaTagLib {

/* a version of isstring that checks for:
 *   a number
 *   a string
 *   a __tostring metamethod */

LTAGLIB_PRIVATE
int isstring(lua_State* L, int idx);

/* all beblow functions push to the stack, the caller
 * needs to pop */

/* slimmed-down version of luaL_tolstring, only accepts
 * LUA_TSTRING, LUA_TNUMBER, and anything with a __tostring
 * metamethod.
 */
LTAGLIB_PRIVATE
const char* tolstring(lua_State* L, int idx, size_t* len);

/* same as tolstring(L, idx, NULL) */
LTAGLIB_PRIVATE
const char* tostring(lua_State* L, int idx);

/* calls luaL_typeerror when tolstring/tostring fail */
LTAGLIB_PRIVATE
const char* checklstring(lua_State* L, int idx, size_t* len);

LTAGLIB_PRIVATE
const char* checkstring(lua_State* L, int idx);

}

#endif

