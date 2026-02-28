#include "wav.h"

using namespace LuaTagLib;

LTAGLIB_PUBLIC
int luaopen_TagLib_RIFF_WAV(lua_State* L) {
    lua_newtable(L);

    luaL_requiref(L, "TagLib.RIFF.WAV.File", luaopen_TagLib_RIFF_WAV_File, 0);
    lua_setfield(L, -2, "File");

    luaL_requiref(L, "TagLib.RIFF.WAV.Properties", luaopen_TagLib_RIFF_WAV_Properties, 0);
    lua_setfield(L, -2, "Properties");

    return 1;
}
