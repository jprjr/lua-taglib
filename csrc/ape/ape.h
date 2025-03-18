#ifndef LTAGLIB_APE_INCLUDE_GUARD
#define LTAGLIB_APE_INCLUDE_GUARD

#include "../taglib.h"

#define LTAGLIB_HAS_APE (LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,3,0))

#if LTAGLIB_HAS_APE

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_APE(lua_State* L);

}

#endif

#endif


