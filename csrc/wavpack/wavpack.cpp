#include "wavpack.h"

#include "wavpackfile.h"
#include "wavpackproperties.h"

using namespace LuaTagLib;

LTAGLIB_PUBLIC
int luaopen_TagLib_WavPack(lua_State* L) {
    lua_newtable(L);

    luaL_requiref(L, "TagLib.WavPack.File", luaopen_TagLib_WavPack_File, 0);
    lua_setfield(L, -2, "File");

    luaL_requiref(L, "TagLib.WavPack.Properties", luaopen_TagLib_WavPack_Properties, 0);
    lua_setfield(L, -2, "Properties");

    return 1;
}
