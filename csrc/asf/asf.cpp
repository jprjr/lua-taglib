#include "asf.h"

#if LTAGLIB_HAS_ASF

#include "asfattribute.h"
#include "asfproperties.h"
#include "asffile.h"
#include "asftag.h"
#include "asfpicture.h"

using namespace LuaTagLib;

#define load(m) \
luaL_requiref(L, "TagLib.ASF." #m, luaopen_TagLib_ASF_ ## m, 0); \
lua_setfield(L, -2, #m);

LTAGLIB_PUBLIC int luaopen_TagLib_ASF(lua_State* L) {
    lua_newtable(L);

    load(Attribute)
    load(Properties)
    load(File)
    load(Tag)

#if LTAGLIB_HAS_ASF_PICTURE
    load(Picture)
#endif

    return 1;
}

#endif
