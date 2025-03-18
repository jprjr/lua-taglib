#ifndef LTAGLIB_RIFF_INCLUDE_GUARD
#define LTAGLIB_RIFF_INCLUDE_GUARD

#include "wav/wav.h"
#include "aiff/aiff.h"
#include "info/info.h"

#define LTAGLIB_HAS_RIFF (LTAGLIB_HAS_RIFF_WAV || LTAGLIB_HAS_RIFF_AIFF || LTAGLIB_HAS_RIFF_INFO)

#if LTAGLIB_HAS_RIFF

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_RIFF(lua_State *L);

}

#endif

#endif

