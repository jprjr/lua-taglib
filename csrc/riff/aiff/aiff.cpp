#include "aiff.h"

using namespace LuaTagLib;

LTAGLIB_PUBLIC
int luaopen_TagLib_RIFF_AIFF(lua_State* L) {
    lua_newtable(L);

    luaL_requiref(L, "TagLib.RIFF.AIFF.File", luaopen_TagLib_RIFF_AIFF_File, 0);
    lua_setfield(L, -2, "File");
    luaL_requiref(L, "TagLib.RIFF.AIFF.Properties", luaopen_TagLib_RIFF_AIFF_Properties, 0);
    lua_setfield(L, -2, "Properties");

    return 1;
}

