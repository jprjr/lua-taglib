#ifndef LTAGLIB_OGG_FLAC_INCLUDE_GUARD
#define LTAGLIB_OGG_FLAC_INCLUDE_GUARD

#include "../../taglib.h"

#define LTAGLIB_HAS_OGGFLAC (LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,2,0))

#if LTAGLIB_HAS_OGGFLAC

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_Ogg_FLAC(lua_State *L);

}

#endif

#endif
