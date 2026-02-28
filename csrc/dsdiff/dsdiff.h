#ifndef LTAGLIB_DSDIFF_INCLUDE_GUARD
#define LTAGLIB_DSDIFF_INCLUDE_GUARD

#include "dsdifffile.h"
#include "dsdiffproperties.h"
#include "diin/dsdiffdiin.h"

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_DSDIFF(lua_State* L);

}

#endif
