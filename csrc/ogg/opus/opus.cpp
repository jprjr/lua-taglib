#include "opus.h"

#include "opusfile.h"
#include "opusproperties.h"

using namespace LuaTagLib;

LTAGLIB_PUBLIC
int luaopen_TagLib_Ogg_Opus(lua_State *L) {
    lua_newtable(L);

    luaL_requiref(L, "TagLib.Ogg.Opus.Properties", luaopen_TagLib_Ogg_Opus_Properties, 0);
    lua_setfield(L,-2,"Properties");

    luaL_requiref(L, "TagLib.Ogg.Opus.File", luaopen_TagLib_Ogg_Opus_File, 0);
    lua_setfield(L,-2,"File");

    return 1;
}
