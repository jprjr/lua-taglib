#include "trueaudio.h"

#if LTAGLIB_HAS_TRUEAUDIO

using namespace LuaTagLib;

LTAGLIB_PUBLIC
int luaopen_TagLib_TrueAudio(lua_State* L) {
    lua_newtable(L);

#if LTAGLIB_HAS_TRUEAUDIO_FILE
    luaL_requiref(L, "TagLib.TrueAudio.File", luaopen_TagLib_TrueAudio_File, 0);
    lua_setfield(L, -2, "File");
#endif

#if LTAGLIB_HAS_TRUEAUDIO_PROPERTIES
    luaL_requiref(L, "TagLib.TrueAudio.Properties", luaopen_TagLib_TrueAudio_Properties, 0);
    lua_setfield(L, -2, "Properties");
#endif

    return 1;
}

#endif
