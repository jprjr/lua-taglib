#ifndef LTAGLIB_OGG_OPUS_INCLUDE_GUARD
#define LTAGLIB_OGG_OPUS_INCLUDE_GUARD

#include "../../taglib.h"

#define LTAGLIB_HAS_OPUS (LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,9,0))

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_Ogg_Opus(lua_State *L);

}

#endif
