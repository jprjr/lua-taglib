#include "mpeg.h"

#include "mpegfile.h"
#include "mpegheader.h"
#include "mpegproperties.h"
#include "xingheader.h"

using namespace LuaTagLib;

LTAGLIB_PUBLIC
int luaopen_TagLib_MPEG(lua_State* L) {
    lua_newtable(L);

    luaL_requiref(L, "TagLib.MPEG.File", luaopen_TagLib_MPEG_File, 0);
    lua_setfield(L,-2,"File");

    luaL_requiref(L, "TagLib.MPEG.Header", luaopen_TagLib_MPEG_Header, 0);
    lua_setfield(L,-2,"Header");

    luaL_requiref(L, "TagLib.MPEG.Properties", luaopen_TagLib_MPEG_Properties, 0);
    lua_setfield(L,-2,"Properties");

    luaL_requiref(L, "TagLib.MPEG.XingHeader", luaopen_TagLib_MPEG_XingHeader, 0);
    lua_setfield(L,-2,"XingHeader");

    return 1;
}
