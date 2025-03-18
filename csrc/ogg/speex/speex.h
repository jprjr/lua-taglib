#ifndef LTAGLIB_OGG_SPEEX_INCLUDE_GUARD
#define LTAGLIB_OGG_SPEEX_INCLUDE_GUARD

#include "../../taglib.h"

#define LTAGLIB_HAS_SPEEX (LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,5,0))

#if LTAGLIB_HAS_SPEEX

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_Ogg_Speex(lua_State *L);

}

#endif

#endif

