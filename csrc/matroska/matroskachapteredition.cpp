#include "matroskachapteredition.h"
#include "matroskachapter.h"

#include "../tstring.h"
#include "../tlist.h"

using namespace LuaTagLib;

static int ChapterEdition__call(lua_State* L) {
    int args = lua_gettop(L);
    TagLib::Matroska::ChapterEdition* c = NULL;

    switch(args) {
        case 1: {
            if( Matroska::ChapterEdition::isValid(L, 1) ) {
                c = new TagLib::Matroska::ChapterEdition(Matroska::ChapterEdition::checkValue(L, 1));
                break;
            }
            break;
        }

        case 2: {
            c = new TagLib::Matroska::ChapterEdition(
              ValueList<TagLib::List<TagLib::Matroska::Chapter>,Matroska::Chapter>::checkValue(L, 1),
              (bool)lua_toboolean(L, 2)
            );
            break;
        }

        case 3: {
            c = new TagLib::Matroska::ChapterEdition(
              ValueList<TagLib::List<TagLib::Matroska::Chapter>,Matroska::Chapter>::checkValue(L, 1),
              (bool)lua_toboolean(L, 2),
              (bool)lua_toboolean(L, 3)
            );
            break;
        }

        case 4: {
            c = new TagLib::Matroska::ChapterEdition(
              ValueList<TagLib::List<TagLib::Matroska::Chapter>,Matroska::Chapter>::checkValue(L, 1),
              (bool)lua_toboolean(L, 2),
              (bool)lua_toboolean(L, 3),
              luaL_checkinteger(L, 4)
            );
            break;
        }

        default: break;
    }
    if(c == NULL) return luaL_error(L, "invalid arguments");

    Matroska::ChapterEdition::pushPtr(L, c);
    return 1;
}

static int ChapterEdition_swap(lua_State* L) {
    Matroska::ChapterEdition::checkPtr(L,1)->swap(Matroska::ChapterEdition::checkValue(L,2));
    lua_settop(L,1);
    return 1;
}

static int ChapterEdition_uid(lua_State* L) {
    lua_pushinteger(L,
      Matroska::ChapterEdition::checkPtr(L,1)->uid()
    );
    return 1;
}

static int ChapterEdition_isDefault(lua_State* L) {
    lua_pushboolean(L,
      Matroska::ChapterEdition::checkPtr(L,1)->isDefault()
    );
    return 1;
}

static int ChapterEdition_isOrdered(lua_State* L) {
    lua_pushboolean(L,
      Matroska::ChapterEdition::checkPtr(L,1)->isOrdered()
    );
    return 1;
}

static int ChapterEdition_chapterList(lua_State* L) {
    ConstValueListReference<TagLib::List<TagLib::Matroska::Chapter>,Matroska::Chapter>::pushRef(L,
      Matroska::ChapterEdition::checkPtr(L,1)->chapterList(),
      1
    );
    return 1;
}

static
const luaL_Reg ChapterEdition__index[] = {
    { "swap", ChapterEdition_swap },
    { "uid", ChapterEdition_uid },
    { "isDefault", ChapterEdition_isDefault },
    { "isOrdered", ChapterEdition_isOrdered },
    { "chapterList", ChapterEdition_chapterList },
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_Matroska_ChapterEdition(lua_State *L) {
    return Matroska::ChapterEdition::open(L);
}

template<>
const UserdataTable Matroska::ChapterEdition::base::mod = {
    ChapterEdition__call, /* call */
    NULL, /* __index */
    NULL, /* init */
};

template<>
const UserdataMetatable Matroska::ChapterEdition::base::metatable = {
    "TagLib::Matroska::ChapterEdition", /* name */
    ChapterEdition__index, /* indextable */
    NULL, /* indexfunc */
};

#include "../shared/userdata.tcc"
template class LuaTagLib::BaseUserdata<TagLib::Matroska::ChapterEdition>;

