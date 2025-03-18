#ifndef LTAGLIB_VORBIS_INCLUDE_GUARD
#define LTAGLIB_VORBIS_INCLUDE_GUARD

#include "../shared/lua.h"

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_Vorbis(lua_State* L);

LTAGLIB_PUBLIC
int luaopen_TagLib_Vorbis_Properties(lua_State* L);

LTAGLIB_PUBLIC
int luaopen_TagLib_Vorbis_File(lua_State* L);

}

#endif
