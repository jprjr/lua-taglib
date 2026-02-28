#include "mod.h"

#include "modfilebase.h"
#include "modfile.h"
#include "modproperties.h"
#include "modtag.h"

using namespace LuaTagLib;

#define load(mod) \
luaL_requiref(L, "TagLib.Mod." #mod, luaopen_TagLib_Mod_ ## mod, 0); \
lua_setfield(L, -2, #mod);

LTAGLIB_PUBLIC
int luaopen_TagLib_Mod(lua_State* L) {
    lua_newtable(L);

    load(FileBase);
    load(File);
    load(Properties);
    load(Tag);

    return 1;
}
