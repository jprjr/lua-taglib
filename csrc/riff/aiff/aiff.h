#ifndef LTAGLIB_RIFF_AIFF_INCLUDE_GUARD
#define LTAGLIB_RIFF_AIFF_INCLUDE_GUARD

#include "aifffile.h"
#include "aiffproperties.h"

#define LTAGLIB_HAS_RIFF_AIFF (LTAGLIB_HAS_RIFF_AIFF_PROPERTIES || LTAGLIB_HAS_RIFF_AIFF_FILE)

#if LTAGLIB_HAS_RIFF_AIFF

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_RIFF_AIFF(lua_State *L);

}

#endif

#endif
