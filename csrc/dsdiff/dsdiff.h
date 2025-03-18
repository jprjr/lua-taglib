#ifndef LTAGLIB_DSDIFF_INCLUDE_GUARD
#define LTAGLIB_DSDIFF_INCLUDE_GUARD

#include "dsdifffile.h"
#include "dsdiffproperties.h"
#include "diin/dsdiffdiin.h"

#define LTAGLIB_HAS_DSDIFF (LTAGLIB_HAS_DSDIFF_FILE || LTAGLIB_HAS_DSDIFF_PROPERTIES || LTAGLIB_HAS_DSDIFF_DIIN)

#if LTAGLIB_HAS_DSDIFF

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_DSDIFF(lua_State* L);

}

#endif

#endif
