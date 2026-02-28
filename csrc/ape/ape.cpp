#include "ape.h"

#include "apeitem.h"
#include "apetag.h"
#include "apefooter.h"

#if LTAGLIB_HAS_APE_FILE
#include "apefile.h"
#include "apeproperties.h"
#endif

using namespace LuaTagLib;

LTAGLIB_PUBLIC
int luaopen_TagLib_APE(lua_State* L) {
    lua_newtable(L);

    luaL_requiref(L, "TagLib.APE.Tag", luaopen_TagLib_APE_Tag, 0);
    lua_setfield(L, -2, "Tag");
    luaL_requiref(L, "TagLib.APE.Item", luaopen_TagLib_APE_Item, 0);
    lua_setfield(L, -2, "Item");
    luaL_requiref(L, "TagLib.APE.Footer", luaopen_TagLib_APE_Footer, 0);
    lua_setfield(L, -2, "Footer");

#if LTAGLIB_HAS_APE_FILE
    luaL_requiref(L, "TagLib.APE.File", luaopen_TagLib_APE_File, 0);
    lua_setfield(L, -2, "File");
    luaL_requiref(L, "TagLib.APE.Properties", luaopen_TagLib_APE_Properties, 0);
    lua_setfield(L, -2, "Properties");
#endif

    return 1;
}

