#include "matroskachapters.h"
#include "matroskachapteredition.h"

#include "../tlist.h"

using namespace LuaTagLib;

static int Chapters__call(lua_State* L) {
    int args = lua_gettop(L);
    TagLib::Matroska::Chapters* c = NULL;

    switch(args) {
        case 0: {
            c = new TagLib::Matroska::Chapters();
            break;
        }
        default: break;
    }
    if(c == NULL) return luaL_error(L, "invalid arguments");

    Matroska::Chapters::pushPtr(L, c);
    return 1;
}

static int Chapters_addChapterEdition(lua_State* L) {
    Matroska::Chapters::checkPtr(L,1)->addChapterEdition(
      Matroska::ChapterEdition::checkValue(L,2)
    );
    lua_settop(L,1);
    return 1;
}

static int Chapters_removeChapterEdition(lua_State* L) {
    Matroska::Chapters::checkPtr(L,1)->removeChapterEdition(
      luaL_checkinteger(L, 2)
    );
    lua_settop(L,1);
    return 1;
}

static int Chapters_clear(lua_State* L) {
    Matroska::Chapters::checkPtr(L,1)->clear();
    lua_settop(L,1);
    return 1;
}

static int Chapters_chapterEditionList(lua_State* L) {
    ConstValueListReference<TagLib::Matroska::Chapters::ChapterEditionList,Matroska::ChapterEdition>::pushRef(L,
      Matroska::Chapters::checkPtr(L,1)->chapterEditionList(),
      1
    );
    return 1;
}

static
const luaL_Reg Chapters__index[] = {
    { "clear", Chapters_clear },
    { "addChapterEdition", Chapters_addChapterEdition },
    { "removeChapterEdition", Chapters_removeChapterEdition },
    { "chapterEditionList", Chapters_chapterEditionList },
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_Matroska_Chapters(lua_State *L) {
    return Matroska::Chapters::open(L);
}

template<>
const UserdataTable Matroska::Chapters::base::mod = {
    Chapters__call, /* call */
    NULL, /* __index */
    NULL, /* init */
};

template<>
const UserdataMetatable Matroska::Chapters::base::metatable = {
    "TagLib::Matroska::Chapters", /* name */
    Chapters__index, /* indextable */
    NULL, /* indexfunc */
};

#include "../shared/userdata.tcc"
template class LuaTagLib::BaseUserdata<TagLib::Matroska::Chapters>;

template<>
const char* ConstValueListReference<TagLib::Matroska::Chapters::ChapterEditionList,Matroska::ChapterEdition>::base::__name = "TagLib::Matroska::ChapterEditionList";
