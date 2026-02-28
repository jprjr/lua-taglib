#include "dsdiff.h"

using namespace LuaTagLib;

LTAGLIB_PUBLIC
int luaopen_TagLib_DSDIFF(lua_State* L) {
    lua_newtable(L);

    luaL_requiref(L, "TagLib.DSDIFF.DIIN", luaopen_TagLib_DSDIFF_DIIN, 0);
    lua_setfield(L, -2, "DIIN");

    luaL_requiref(L, "TagLib.DSDIFF.File", luaopen_TagLib_DSDIFF_File, 0);
    lua_setfield(L, -2, "File");

    luaL_requiref(L, "TagLib.DSDIFF.Properties", luaopen_TagLib_DSDIFF_Properties, 0);
    lua_setfield(L, -2, "Properties");

    return 1;
}
