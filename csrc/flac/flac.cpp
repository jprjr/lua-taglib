#include "flac.h"

#include "flacmetadatablock.h"
#include "flacproperties.h"
#include "flacfile.h"
#include "flacpicture.h"

using namespace LuaTagLib;

LTAGLIB_PUBLIC
int luaopen_TagLib_FLAC(lua_State *L) {
    lua_newtable(L); /* the module (FLAC) */

    luaL_requiref(L, "TagLib.FLAC.File", luaopen_TagLib_FLAC_File, 0);
    lua_setfield(L, -2, "File");

    luaL_requiref(L, "TagLib.FLAC.Properties", luaopen_TagLib_FLAC_Properties, 0);
    lua_setfield(L, -2, "Properties");

#if LTAGLIB_HAS_FLAC_METADATABLOCK
    luaL_requiref(L, "TagLib.FLAC.MetadataBlock", luaopen_TagLib_FLAC_MetadataBlock, 0);
    lua_setfield(L, -2, "MetadataBlock");
#endif

#if LTAGLIB_HAS_FLAC_PICTURE
    luaL_requiref(L, "TagLib.FLAC.Picture", luaopen_TagLib_FLAC_Picture, 0);
    lua_setfield(L, -2, "Picture");
#endif

    return 1;
}

