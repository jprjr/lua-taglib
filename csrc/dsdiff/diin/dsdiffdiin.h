#ifndef LTAGLIB_DSDIFF_DIIN_INCLUDE_GUARD
#define LTAGLIB_DSDIFF_DIIN_INCLUDE_GUARD

#include "dsdiffdiintag.h"

#define LTAGLIB_HAS_DSDIFF_DIIN (LTAGLIB_HAS_DSDIFF_DIIN_TAG)

#if LTAGLIB_HAS_DSDIFF_DIIN

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_DSDIFF_DIIN(lua_State* L);

}

#endif

#endif
