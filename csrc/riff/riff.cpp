#include "riff.h"
#include "aiff/aiff.h"
#include "wav/wav.h"

#if LTAGLIB_HAS_RIFF_INFO
#include "info/info.h"
#endif

using namespace LuaTagLib;

LTAGLIB_PUBLIC
int luaopen_TagLib_RIFF(lua_State* L) {
    lua_newtable(L);

    luaL_requiref(L, "TagLib.RIFF.AIFF", luaopen_TagLib_RIFF_AIFF, 0);
    lua_setfield(L, -2, "AIFF");

    luaL_requiref(L, "TagLib.RIFF.WAV", luaopen_TagLib_RIFF_WAV, 0);
    lua_setfield(L, -2, "WAV");

#if LTAGLIB_HAS_RIFF_INFO
    luaL_requiref(L, "TagLib.RIFF.Info", luaopen_TagLib_RIFF_Info, 0);
    lua_setfield(L, -2, "Info");
#endif

    return 1;
}

