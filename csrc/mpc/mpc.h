#ifndef LTAGLIB_MPC_INCLUDE_GUARD
#define LTAGLIB_MPC_INCLUDE_GUARD

#include "mpcfile.h"
#include "mpcproperties.h"

#define LTAGLIB_HAS_MPC (LTAGLIB_HAS_MPC_PROPERTIES || LTAGLIB_HAS_MPC_FILE)

#if LTAGLIB_HAS_MPC

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_MPC(lua_State *L);

}

#endif

#endif
