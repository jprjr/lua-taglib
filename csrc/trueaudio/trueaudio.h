#ifndef LTAGLIB_TRUEAUDIO_INCLUDE_GUARD
#define LTAGLIB_TRUEAUDIO_INCLUDE_GUARD

#include "trueaudiofile.h"
#include "trueaudioproperties.h"

#define LTAGLIB_HAS_TRUEAUDIO (LTAGLIB_HAS_TRUEAUDIO_PROPERTIES || LTAGLIB_HAS_TRUEAUDIO_FILE)

#if LTAGLIB_HAS_TRUEAUDIO

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_TrueAudio(lua_State *L);

}

#endif

#endif
