#include "opus.h"

#if LTAGLIB_HAS_OPUS

#include "opusfile.h"
#include "opusproperties.h"

using namespace LuaTagLib;

LTAGLIB_PUBLIC
int luaopen_TagLib_Ogg_Opus(lua_State *L) {
    lua_newtable(L);

#if LTAGLIB_HAS_OPUSPROPERTIES
    luaL_requiref(L, "TagLib.Ogg.Opus.Properties", luaopen_TagLib_Ogg_Opus_Properties, 0);
    lua_setfield(L,-2,"Properties");
#endif

#if LTAGLIB_HAS_OPUSFILE
    luaL_requiref(L, "TagLib.Ogg.Opus.File", luaopen_TagLib_Ogg_Opus_File, 0);
    lua_setfield(L,-2,"File");
#endif

    return 1;
}

#endif
