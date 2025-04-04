#ifndef LTAGLIB_VERSION_INCLUDE_GUARD
#define LTAGLIB_VERSION_INCLUDE_GUARD

#include "shared/attrs.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <lua.h>
#include <lauxlib.h>

#define LTAGLIB_LIBRARY_VERSION "1.1.2"

LTAGLIB_PUBLIC
int luaopen_TagLib__VERSION(lua_State* L);

#ifdef __cplusplus
}
#endif

#endif
