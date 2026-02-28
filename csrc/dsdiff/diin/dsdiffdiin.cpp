#include "dsdiffdiin.h"

using namespace LuaTagLib;

LTAGLIB_PUBLIC
int luaopen_TagLib_DSDIFF_DIIN(lua_State* L) {
    lua_newtable(L);

    luaL_requiref(L, "TagLib.DSDIFF.DIIN.Tag", luaopen_TagLib_DSDIFF_DIIN_Tag, 0);
    lua_setfield(L, -2, "Tag");

    return 1;
}
