#ifndef LTAGLIB_MOD_INCLUDE_GUARD
#define LTAGLIB_MOD_INCLUDE_GUARD

#include "modfilebase.h"
#include "modfile.h"
#include "modproperties.h"
#include "modtag.h"

#define LTAGLIB_HAS_MOD (LTAGLIB_HAS_MOD_FILE || LTAGLIB_HAS_MOD_FILEBASE || LTAGLIB_HAS_MOD_PROPERTIES || LTAGLIB_HAS_MOD_TAG)

#if LTAGLIB_HAS_MOD

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_Mod(lua_State* L);

}

#endif

#endif
