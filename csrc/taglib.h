#ifndef LTAGLIB_TAGLIB_INCLUDE_GUARD
#define LTAGLIB_TAGLIB_INCLUDE_GUARD

#include <taglib.h>

/* first some housekeeping.
 * Version 1.8.0 didn't set a new TAGLIB_MINOR_VERSION so if
 * we see version 7, we'll try to override it */

#if TAGLIB_MAJOR_VERSION == 1 && TAGLIB_MINOR_VERSION == 7
#if defined(__has_include)
#if __has_include(<tpropertymap.h>)
#undef TAGLIB_MINOR_VERSION
#define TAGLIB_MINOR_VERSION 8
#endif
#endif
#endif

#define LTAGLIB_VERSION_NUM(MAJOR, MINOR, PATCH) ( (MAJOR << 16) | (MINOR << 8) | PATCH )
#if defined TAGLIB_PATCH_VERSION
#define LTAGLIB_VERSION (LTAGLIB_VERSION_NUM(TAGLIB_MAJOR_VERSION, TAGLIB_MINOR_VERSION, TAGLIB_PATCH_VERSION))
#else
#define LTAGLIB_VERSION (LTAGLIB_VERSION_NUM(TAGLIB_MAJOR_VERSION, TAGLIB_MINOR_VERSION, 0))
#endif

/* convenience macros */
#define LTAGLIB_1_2   (LTAGLIB_VERSION_NUM(1,2,0))
#define LTAGLIB_1_3   (LTAGLIB_VERSION_NUM(1,3,0))
#define LTAGLIB_1_4   (LTAGLIB_VERSION_NUM(1,4,0))
#define LTAGLIB_1_5   (LTAGLIB_VERSION_NUM(1,5,0))
#define LTAGLIB_1_6   (LTAGLIB_VERSION_NUM(1,6,0))
#define LTAGLIB_1_7   (LTAGLIB_VERSION_NUM(1,7,0))
#define LTAGLIB_1_8   (LTAGLIB_VERSION_NUM(1,8,0))
#define LTAGLIB_1_9   (LTAGLIB_VERSION_NUM(1,9,0))
#define LTAGLIB_1_10 (LTAGLIB_VERSION_NUM(1,10,0))
#define LTAGLIB_1_11 (LTAGLIB_VERSION_NUM(1,11,0))
#define LTAGLIB_1_12 (LTAGLIB_VERSION_NUM(1,12,0))
#define LTAGLIB_1_13 (LTAGLIB_VERSION_NUM(1,13,0))
#define LTAGLIB_2_0   (LTAGLIB_VERSION_NUM(2,0,0))

#define LTAGLIB_ATLEAST(v)  (LTAGLIB_VERSION >= v)
#define LTAGLIB_UNDER(v) (LTAGLIB_VERSION < v)

#include "shared/lua.h"

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib(lua_State *L);

}

#endif

