#ifndef LTAGLIB_DSF_INCLUDE_GUARD
#define LTAGLIB_DSF_INCLUDE_GUARD

#include "dsffile.h"
#include "dsfproperties.h"

#define LTAGLIB_HAS_DSF (LTAGLIB_HAS_DSF_FILE || LTAGLIB_HAS_DSF_PROPERTIES)

#if LTAGLIB_HAS_DSF

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_DSF(lua_State* L);

}

#endif

#endif
