#include "vorbis.h"

#include "../ogg/vorbis/vorbisproperties.h"
#include "../ogg/vorbis/vorbisfile.h"
#include "../ogg/vorbis/vorbis.h"

using namespace LuaTagLib;

LTAGLIB_PUBLIC
int luaopen_TagLib_Vorbis_Properties(lua_State* L) {
    luaL_requiref(L, "TagLib.Ogg.Vorbis.Properties",
      luaopen_TagLib_Ogg_Vorbis_Properties, 0);
    return 1;
}

LTAGLIB_PUBLIC
int luaopen_TagLib_Vorbis_File(lua_State* L) {
    luaL_requiref(L, "TagLib.Ogg.Vorbis.File",
      luaopen_TagLib_Ogg_Vorbis_File, 0);
    return 1;
}

LTAGLIB_PUBLIC
int luaopen_TagLib_Vorbis(lua_State* L) {
    luaL_requiref(L, "TagLib.Ogg.Vorbis",
      luaopen_TagLib_Ogg_Vorbis, 0);
    return 1;
}
