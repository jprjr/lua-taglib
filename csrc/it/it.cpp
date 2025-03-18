#include "it.h"

#if LTAGLIB_HAS_IT

using namespace LuaTagLib;

#define load(mod) \
luaL_requiref(L, "TagLib.IT." #mod, luaopen_TagLib_IT_ ## mod, 0); \
lua_setfield(L, -2, #mod);

LTAGLIB_PUBLIC
int luaopen_TagLib_IT(lua_State* L) {
    lua_newtable(L);

    load(File);
    load(Properties);

    return 1;
}

#endif

