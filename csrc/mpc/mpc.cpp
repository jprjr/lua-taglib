#include "mpc.h"

#include "mpcfile.h"
#include "mpcproperties.h"

using namespace LuaTagLib;

LTAGLIB_PUBLIC
int luaopen_TagLib_MPC(lua_State* L) {
    lua_newtable(L);

    luaL_requiref(L, "TagLib.MPC.File", luaopen_TagLib_MPC_File, 0);
    lua_setfield(L, -2, "File");

    luaL_requiref(L, "TagLib.MPC.Properties", luaopen_TagLib_MPC_Properties, 0);
    lua_setfield(L, -2, "Properties");

    return 1;
}

