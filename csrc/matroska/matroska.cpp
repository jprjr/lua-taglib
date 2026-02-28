#include "matroska.h"

#include "matroskaattachedfile.h"
#include "matroskaattachments.h"
#include "matroskachapter.h"
#include "matroskachapteredition.h"
#include "matroskachapters.h"
#include "matroskafile.h"
#include "matroskaproperties.h"
#include "matroskasimpletag.h"
#include "matroskatag.h"

using namespace LuaTagLib;

#define load(mod) \
luaL_requiref(L, "TagLib.Matroska." #mod, luaopen_TagLib_Matroska_ ## mod, 0); \
lua_setfield(L, -2, #mod);

LTAGLIB_PUBLIC
int luaopen_TagLib_Matroska(lua_State* L) {
    lua_newtable(L);

    load(AttachedFile)
    load(Attachments)
    load(Chapter)
    load(ChapterEdition)
    load(Chapters)
    load(File)
    load(Properties)
    load(SimpleTag)
    load(Tag)

    return 1;
}


