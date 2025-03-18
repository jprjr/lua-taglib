#ifndef LTAGLIB_IT_INCLUDE_GUARD
#define LTAGLIB_IT_INCLUDE_GUARD

#include "itfile.h"
#include "itproperties.h"

#define LTAGLIB_HAS_IT (LTAGLIB_HAS_IT_FILE || LTAGLIB_HAS_IT_PROPERTIES)

#if LTAGLIB_HAS_IT

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_IT(lua_State* L);

}

#endif
#endif
