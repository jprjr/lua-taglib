#ifndef LTAGLIB_RIFF_INFO_INCLUDE_GUARD
#define LTAGLIB_RIFF_INFO_INCLUDE_GUARD

#include "infotag.h"

#define LTAGLIB_HAS_RIFF_INFO (LTAGLIB_HAS_RIFF_INFO_TAG)

#if LTAGLIB_HAS_RIFF_INFO

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_RIFF_Info(lua_State* L);

}

#endif

#endif
