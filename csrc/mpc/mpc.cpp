#include "mpc.h"

#if LTAGLIB_HAS_MPC

using namespace LuaTagLib;

LTAGLIB_PUBLIC
int luaopen_TagLib_MPC(lua_State* L) {
    lua_newtable(L);

#if LTAGLIB_HAS_MPC_FILE
    luaL_requiref(L, "TagLib.MPC.File", luaopen_TagLib_MPC_File, 0);
    lua_setfield(L, -2, "File");
#endif

#if LTAGLIB_HAS_MPC_PROPERTIES
    luaL_requiref(L, "TagLib.MPC.Properties", luaopen_TagLib_MPC_Properties, 0);
    lua_setfield(L, -2, "Properties");
#endif

    return 1;
}

#endif
