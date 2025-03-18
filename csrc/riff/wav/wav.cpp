#include "wav.h"

#if LTAGLIB_HAS_RIFF_WAV

using namespace LuaTagLib;

LTAGLIB_PUBLIC
int luaopen_TagLib_RIFF_WAV(lua_State* L) {
    lua_newtable(L);

#if LTAGLIB_HAS_RIFF_WAV_FILE
    luaL_requiref(L, "TagLib.RIFF.WAV.File", luaopen_TagLib_RIFF_WAV_File, 0);
    lua_setfield(L, -2, "File");
#endif

#if LTAGLIB_HAS_RIFF_WAV_PROPERTIES
    luaL_requiref(L, "TagLib.RIFF.WAV.Properties", luaopen_TagLib_RIFF_WAV_Properties, 0);
    lua_setfield(L, -2, "Properties");
#endif

    return 1;
}

#endif
