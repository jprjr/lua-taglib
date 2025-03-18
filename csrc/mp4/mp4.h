#ifndef LTAGLIB_MP4_INCLUDE_GUARD
#define LTAGLIB_MP4_INCLUDE_GUARD

#include "../taglib.h"

/* between versions 1.6.0 and 1.9.0 you have to check
 * the taglib_config.h file (I'm not 100% clear if 1.8 and 1.9
 * actually let you disble MP4 support or not). Starting in
 * 1.10 it's always enabled. */

#if LTAGLIB_UNDER(LTAGLIB_1_6)
#define LTAGLIB_HAS_MP4 0
#elif LTAGLIB_UNDER(LTAGLIB_1_10)

#include "taglib_config.h"

#ifdef TAGLIB_WITH_MP4
#define LTAGLIB_HAS_MP4 1
#else
#define LTAGLIB_HAS_MP4 0
#endif

#else
#define LTAGLIB_HAS_MP4 1
#endif

#if LTAGLIB_HAS_MP4

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_MP4(lua_State *L);

}

#endif
#endif

