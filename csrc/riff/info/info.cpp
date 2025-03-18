#include "info.h"

#if LTAGLIB_HAS_RIFF_INFO

using namespace LuaTagLib;

LTAGLIB_PUBLIC
int luaopen_TagLib_RIFF_Info(lua_State* L) {
    lua_newtable(L);

    luaL_requiref(L, "TagLib.RIFF.Info.Tag", luaopen_TagLib_RIFF_Info_Tag, 0);
    lua_setfield(L, -2, "Tag");

    return 1;
}

#endif
