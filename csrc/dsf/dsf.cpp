#include "dsf.h"

using namespace LuaTagLib;

LTAGLIB_PUBLIC
int luaopen_TagLib_DSF(lua_State* L) {
    lua_newtable(L);

    luaL_requiref(L, "TagLib.DSF.File", luaopen_TagLib_DSF_File, 0);
    lua_setfield(L, -2, "File");

    luaL_requiref(L, "TagLib.DSF.Properties", luaopen_TagLib_DSF_Properties, 0);
    lua_setfield(L, -2, "Properties");

    return 1;
}

