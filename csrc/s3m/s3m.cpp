#include "s3m.h"

#include "s3mfile.h"
#include "s3mproperties.h"

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
