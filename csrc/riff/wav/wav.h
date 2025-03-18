#ifndef LTAGLIB_RIFF_WAV_INCLUDE_GUARD
#define LTAGLIB_RIFF_WAV_INCLUDE_GUARD

#include "wavfile.h"
#include "wavproperties.h"

#define LTAGLIB_HAS_RIFF_WAV (LTAGLIB_HAS_RIFF_WAV_PROPERTIES || LTAGLIB_HAS_RIFF_WAV_FILE)

#if LTAGLIB_HAS_RIFF_WAV

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_RIFF_WAV(lua_State *L);

}

#endif

#endif
