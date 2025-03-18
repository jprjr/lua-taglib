#include "xm.h"

#if LTAGLIB_HAS_XM

using namespace LuaTagLib;

#define load(mod) \
luaL_requiref(L, "TagLib.XM." #mod, luaopen_TagLib_XM_ ## mod, 0); \
lua_setfield(L, -2, #mod);

LTAGLIB_PUBLIC
int luaopen_TagLib_XM(lua_State* L) {
    lua_newtable(L);

    load(File);
    load(Properties);

    return 1;
}

#endif

