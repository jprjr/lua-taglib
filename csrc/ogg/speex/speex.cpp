#include "speex.h"

#if LTAGLIB_HAS_SPEEX

#include "speexfile.h"
#include "speexproperties.h"

using namespace LuaTagLib;

LTAGLIB_PUBLIC
int luaopen_TagLib_Ogg_Speex(lua_State *L) {
    lua_newtable(L);

    luaL_requiref(L, "TagLib.Ogg.Speex.Properties", luaopen_TagLib_Ogg_Speex_Properties, 0);
    lua_setfield(L,-2,"Properties");

    luaL_requiref(L, "TagLib.Ogg.Speex.File", luaopen_TagLib_Ogg_Speex_File, 0);
    lua_setfield(L,-2,"File");

    return 1;
}

#endif
