#include "trueaudio.h"

#include "trueaudiofile.h"
#include "trueaudioproperties.h"

using namespace LuaTagLib;

LTAGLIB_PUBLIC
int luaopen_TagLib_TrueAudio(lua_State* L) {
    lua_newtable(L);

    luaL_requiref(L, "TagLib.TrueAudio.File", luaopen_TagLib_TrueAudio_File, 0);
    lua_setfield(L, -2, "File");

    luaL_requiref(L, "TagLib.TrueAudio.Properties", luaopen_TagLib_TrueAudio_Properties, 0);
    lua_setfield(L, -2, "Properties");

    return 1;
}

