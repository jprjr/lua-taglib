#include "shorten.h"

#include "shortenfile.h"
#include "shortenproperties.h"
#include "shortentag.h"

using namespace LuaTagLib;

LTAGLIB_PUBLIC
int luaopen_TagLib_Shorten(lua_State* L) {
    lua_newtable(L);

    luaL_requiref(L, "TagLib.Shorten.File", luaopen_TagLib_Shorten_File, 0);
    lua_setfield(L,-2,"File");

    luaL_requiref(L, "TagLib.Shorten.Properties", luaopen_TagLib_Shorten_Properties, 0);
    lua_setfield(L,-2,"Properties");

    luaL_requiref(L, "TagLib.Shorten.Tag", luaopen_TagLib_Shorten_Tag, 0);
    lua_setfield(L,-2,"Tag");

    return 1;
}
