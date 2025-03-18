#include "aiff.h"

#if LTAGLIB_HAS_RIFF_AIFF

using namespace LuaTagLib;

LTAGLIB_PUBLIC
int luaopen_TagLib_RIFF_AIFF(lua_State* L) {
    lua_newtable(L);

#if LTAGLIB_HAS_RIFF_AIFF_FILE
    luaL_requiref(L, "TagLib.RIFF.AIFF.File", luaopen_TagLib_RIFF_AIFF_File, 0);
    lua_setfield(L, -2, "File");
#endif

#if LTAGLIB_HAS_RIFF_AIFF_PROPERTIES
    luaL_requiref(L, "TagLib.RIFF.AIFF.Properties", luaopen_TagLib_RIFF_AIFF_Properties, 0);
    lua_setfield(L, -2, "Properties");
#endif

    return 1;
}

#endif
