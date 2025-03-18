#include "mp4.h"

#if LTAGLIB_HAS_MP4

#include "mp4file.h"
#include "mp4item.h"
#include "mp4properties.h"
#include "mp4tag.h"
#include "mp4coverart.h"

using namespace LuaTagLib;

#define load(mod) \
luaL_requiref(L, "TagLib.MP4." #mod, luaopen_TagLib_MP4_ ## mod, 0); \
lua_setfield(L, -2, #mod);

LTAGLIB_PUBLIC
int luaopen_TagLib_MP4(lua_State* L) {
    lua_newtable(L);

    load(File)
    load(Item)
    load(Properties)
    load(Tag)
#if LTAGLIB_HAS_MP4_COVERART
    load(CoverArt)
#endif

    return 1;
}

#endif
