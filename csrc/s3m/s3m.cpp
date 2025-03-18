#include "s3m.h"

#if LTAGLIB_HAS_S3M

using namespace LuaTagLib;

#define load(mod) \
luaL_requiref(L, "TagLib.S3M." #mod, luaopen_TagLib_S3M_ ## mod, 0); \
lua_setfield(L, -2, #mod);

LTAGLIB_PUBLIC
int luaopen_TagLib_S3M(lua_State* L) {
    lua_newtable(L);

    load(File);
    load(Properties);

    return 1;
}

#endif

