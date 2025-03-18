#include "dsdiff.h"

#if LTAGLIB_HAS_DSDIFF

using namespace LuaTagLib;

LTAGLIB_PUBLIC
int luaopen_TagLib_DSDIFF(lua_State* L) {
    lua_newtable(L);

#if LTAGLIB_HAS_DSDIFF_DIIN
    luaL_requiref(L, "TagLib.DSDIFF.DIIN", luaopen_TagLib_DSDIFF_DIIN, 0);
    lua_setfield(L, -2, "DIIN");
#endif

#if LTAGLIB_HAS_DSDIFF_FILE
    luaL_requiref(L, "TagLib.DSDIFF.File", luaopen_TagLib_DSDIFF_File, 0);
    lua_setfield(L, -2, "File");
#endif

#if LTAGLIB_HAS_DSDIFF_PROPERTIES
    luaL_requiref(L, "TagLib.DSDIFF.Properties", luaopen_TagLib_DSDIFF_Properties, 0);
    lua_setfield(L, -2, "Properties");
#endif

    return 1;
}

#endif
