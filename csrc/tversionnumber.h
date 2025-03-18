#ifndef LTAGLIB_VERSIONNUMBER_INCLUDE_GUARD
#define LTAGLIB_VERSIONNUMBER_INCLUDE_GUARD

#include "taglib.h"

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_VersionNumber(lua_State* L);

LTAGLIB_PUBLIC
int luaopen_TagLib_compiletimeVersion(lua_State* L);

LTAGLIB_PUBLIC
int luaopen_TagLib_runtimeVersion(lua_State* L);

}

#endif


