#include "dsdiffdiin.h"

#if LTAGLIB_HAS_DSDIFF_DIIN

using namespace LuaTagLib;

LTAGLIB_PUBLIC
int luaopen_TagLib_DSDIFF_DIIN(lua_State* L) {
    lua_newtable(L);

#if LTAGLIB_HAS_DSDIFF_DIIN_TAG
    luaL_requiref(L, "TagLib.DSDIFF.DIIN.Tag", luaopen_TagLib_DSDIFF_DIIN_Tag, 0);
    lua_setfield(L, -2, "Tag");
#endif

    return 1;
}

#endif
