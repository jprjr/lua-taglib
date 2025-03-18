#include "ape.h"

#if LTAGLIB_HAS_APE

#include "apeitem.h"
#include "apefile.h"
#include "apetag.h"
#include "apefooter.h"
#include "apeproperties.h"

using namespace LuaTagLib;

LTAGLIB_PUBLIC
int luaopen_TagLib_APE(lua_State* L) {
    lua_newtable(L);

#if LTAGLIB_HAS_APE_FILE
    luaL_requiref(L, "TagLib.APE.File", luaopen_TagLib_APE_File, 0);
    lua_setfield(L, -2, "File");
#endif

#if LTAGLIB_HAS_APE_TAG
    luaL_requiref(L, "TagLib.APE.Tag", luaopen_TagLib_APE_Tag, 0);
    lua_setfield(L, -2, "Tag");
#endif

#if LTAGLIB_HAS_APE_ITEM
    luaL_requiref(L, "TagLib.APE.Item", luaopen_TagLib_APE_Item, 0);
    lua_setfield(L, -2, "Item");
#endif

#if LTAGLIB_HAS_APE_FOOTER
    luaL_requiref(L, "TagLib.APE.Footer", luaopen_TagLib_APE_Footer, 0);
    lua_setfield(L, -2, "Footer");
#endif

#if LTAGLIB_HAS_APE_PROPERTIES
    luaL_requiref(L, "TagLib.APE.Properties", luaopen_TagLib_APE_Properties, 0);
    lua_setfield(L, -2, "Properties");
#endif

    return 1;
}

#endif
