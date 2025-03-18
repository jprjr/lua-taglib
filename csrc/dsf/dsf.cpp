#include "dsf.h"

#if LTAGLIB_HAS_DSF

using namespace LuaTagLib;

LTAGLIB_PUBLIC
int luaopen_TagLib_DSF(lua_State* L) {
    lua_newtable(L);

#if LTAGLIB_HAS_DSF_FILE
    luaL_requiref(L, "TagLib.DSF.File", luaopen_TagLib_DSF_File, 0);
    lua_setfield(L, -2, "File");
#endif

#if LTAGLIB_HAS_DSF_PROPERTIES
    luaL_requiref(L, "TagLib.DSF.Properties", luaopen_TagLib_DSF_Properties, 0);
    lua_setfield(L, -2, "Properties");
#endif

    return 1;
}

#endif
