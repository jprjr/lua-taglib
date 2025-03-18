#include "ogg.h"

#include "xiphcomment.h"
#include "oggfile.h"
#include "oggpage.h"
#include "oggpageheader.h"
#include "flac/oggflac.h"
#include "opus/opus.h"
#include "vorbis/vorbis.h"
#include "speex/speex.h"

using namespace LuaTagLib;

LTAGLIB_PUBLIC
int luaopen_TagLib_Ogg(lua_State *L) {
    lua_newtable(L);

    luaL_requiref(L, "TagLib.Ogg.File", luaopen_TagLib_Ogg_File, 0);
    lua_setfield(L, -2, "File");

#if LTAGLIB_HAS_OGGFLAC
    luaL_requiref(L, "TagLib.Ogg.FLAC", luaopen_TagLib_Ogg_FLAC, 0);
    lua_setfield(L, -2, "FLAC");
#endif

#if LTAGLIB_HAS_OPUS
    luaL_requiref(L, "TagLib.Ogg.Opus", luaopen_TagLib_Ogg_Opus, 0);
    lua_setfield(L, -2, "Opus");
#endif

#if LTAGLIB_HAS_SPEEX
    luaL_requiref(L, "TagLib.Ogg.Speex", luaopen_TagLib_Ogg_Speex, 0);
    lua_setfield(L, -2, "Speex");
#endif

    luaL_requiref(L, "TagLib.Ogg.XiphComment", luaopen_TagLib_Ogg_XiphComment, 0);
    lua_setfield(L, -2, "XiphComment");

    luaL_requiref(L, "TagLib.Ogg.Vorbis", luaopen_TagLib_Ogg_Vorbis, 0);
    lua_setfield(L, -2, "Vorbis");

    luaL_requiref(L, "TagLib.Ogg.Page", luaopen_TagLib_Ogg_Page, 0);
    lua_setfield(L, -2, "Page");

    luaL_requiref(L, "TagLib.Ogg.PageHeader", luaopen_TagLib_Ogg_PageHeader, 0);
    lua_setfield(L, -2, "PageHeader");

    return 1;
}
