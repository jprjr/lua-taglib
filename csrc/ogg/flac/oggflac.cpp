#include "oggflac.h"

#if LTAGLIB_HAS_OGGFLAC

#include "oggflacfile.h"

using namespace LuaTagLib;

LTAGLIB_PUBLIC
int luaopen_TagLib_Ogg_FLAC(lua_State *L) {
    lua_newtable(L);

    luaL_requiref(L, "TagLib.Ogg.FLAC.File", luaopen_TagLib_Ogg_FLAC_File, 0);
    lua_setfield(L,-2,"File");

    return 1;
}

#endif
