#include "vorbis.h"

#include "vorbisfile.h"
#include "vorbisproperties.h"

using namespace LuaTagLib;

LTAGLIB_PUBLIC
int luaopen_TagLib_Ogg_Vorbis(lua_State *L) {
    lua_newtable(L);

    luaL_requiref(L, "TagLib.Ogg.Vorbis.Properties", luaopen_TagLib_Ogg_Vorbis_Properties, 0);
    lua_setfield(L,-2,"Properties");

    luaL_requiref(L, "TagLib.Ogg.Vorbis.File", luaopen_TagLib_Ogg_Vorbis_File, 0);
    lua_setfield(L,-2,"File");

    return 1;
}


