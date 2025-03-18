#ifndef LTAGLIB_WAVPACK_INCLUDE_GUARD
#define LTAGLIB_WAVPACK_INCLUDE_GUARD

#include "wavpackfile.h"
#include "wavpackproperties.h"

#define LTAGLIB_HAS_WAVPACK (LTAGLIB_HAS_WAVPACK_PROPERTIES || LTAGLIB_HAS_WAVPACK_FILE)

#if LTAGLIB_HAS_WAVPACK

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_WavPack(lua_State *L);

}

#endif

#endif
