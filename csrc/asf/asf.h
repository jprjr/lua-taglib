#ifndef LTAGLIB_ASF_INCLUDE_GUARD
#define LTAGLIB_ASF_INCLUDE_GUARD

#include "../taglib.h"

/* see comments in mp4.h about version checking */

#if LTAGLIB_UNDER(LTAGLIB_1_6)
#define LTAGLIB_HAS_ASF 0
#elif LTAGLIB_UNDER(LTAGLIB_1_10)

#include "taglib_config.h"

#ifdef TAGLIB_WITH_ASF
#define LTAGLIB_HAS_ASF 1
#else
#define LTAGLIB_HAS_ASF 0
#endif

#else
#define LTAGLIB_HAS_ASF 1
#endif

#if LTAGLIB_HAS_ASF

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_ASF(lua_State *L);

}

#endif
#endif
