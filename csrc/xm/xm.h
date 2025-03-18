#ifndef LTAGLIB_XM_INCLUDE_GUARD
#define LTAGLIB_XM_INCLUDE_GUARD

#include "xmfile.h"
#include "xmproperties.h"

#define LTAGLIB_HAS_XM (LTAGLIB_HAS_XM_FILE || LTAGLIB_HAS_XM_PROPERTIES)

#if LTAGLIB_HAS_XM

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_XM(lua_State* L);

}

#endif
#endif
