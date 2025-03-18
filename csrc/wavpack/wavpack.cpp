#include "wavpack.h"

#if LTAGLIB_HAS_WAVPACK

using namespace LuaTagLib;

LTAGLIB_PUBLIC
int luaopen_TagLib_WavPack(lua_State* L) {
    lua_newtable(L);

#if LTAGLIB_HAS_WAVPACK_FILE
    luaL_requiref(L, "TagLib.WavPack.File", luaopen_TagLib_WavPack_File, 0);
    lua_setfield(L, -2, "File");
#endif

#if LTAGLIB_HAS_WAVPACK_PROPERTIES
    luaL_requiref(L, "TagLib.WavPack.Properties", luaopen_TagLib_WavPack_Properties, 0);
    lua_setfield(L, -2, "Properties");
#endif

    return 1;
}

#endif
