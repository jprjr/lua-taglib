#include "riff.h"

#if LTAGLIB_HAS_RIFF

using namespace LuaTagLib;

LTAGLIB_PUBLIC
int luaopen_TagLib_RIFF(lua_State* L) {
    lua_newtable(L);

#if LTAGLIB_HAS_RIFF_AIFF
    luaL_requiref(L, "TagLib.RIFF.AIFF", luaopen_TagLib_RIFF_AIFF, 0);
    lua_setfield(L, -2, "AIFF");
#endif

#if LTAGLIB_HAS_RIFF_WAV
    luaL_requiref(L, "TagLib.RIFF.WAV", luaopen_TagLib_RIFF_WAV, 0);
    lua_setfield(L, -2, "WAV");
#endif

#if LTAGLIB_HAS_RIFF_INFO
    luaL_requiref(L, "TagLib.RIFF.Info", luaopen_TagLib_RIFF_Info, 0);
    lua_setfield(L, -2, "Info");
#endif

    return 1;
}

#endif
