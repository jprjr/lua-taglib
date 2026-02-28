#include "matroskachapter.h"

#include "../tstring.h"
#include "../tlist.h"

using namespace LuaTagLib;

static int Display__call(lua_State* L) {
    int args = lua_gettop(L);
    TagLib::Matroska::Chapter::Display* d = NULL;

    switch(args) {
        case 1: {
            if(Matroska::Chapter::Display::isValid(L, 1)) {
                d = new TagLib::Matroska::Chapter::Display(
                  Matroska::Chapter::Display::checkValue(L, 1)
                );
            }
            break;
        }
        case 2: {
            d = new TagLib::Matroska::Chapter::Display(
              String::checkValue(L, 1),
              String::checkValue(L, 2)
            );
            break;
        }
        default: break;
    }
    if(d == NULL) return luaL_error(L, "invalid arguments");

    Matroska::Chapter::Display::pushPtr(L, d);
    return 1;
}

static int Display_swap(lua_State* L) {
    Matroska::Chapter::Display::checkPtr(L,1)->swap(Matroska::Chapter::Display::checkValue(L,2));
    lua_settop(L,1);
    return 1;
}

static int Display_string(lua_State* L) {
    String::pushValue(L,
      Matroska::Chapter::Display::checkPtr(L,1)->string()
    );
    return 1;
}

static int Display_language(lua_State* L) {
    String::pushValue(L,
      Matroska::Chapter::Display::checkPtr(L,1)->language()
    );
    return 1;
}

static
const luaL_Reg Display__index[] = {
    { "swap", Display_swap },
    { "string", Display_string },
    { "language", Display_language },
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_Matroska_Chapter_Display(lua_State *L) {
    return Matroska::Chapter::Display::open(L);
}

template<>
const UserdataTable Matroska::Chapter::Display::base::mod = {
    Display__call, /* call */
    NULL, /* __index */
    NULL, /* init */
};

template<>
const UserdataMetatable Matroska::Chapter::Display::base::metatable = {
    "TagLib::Matroska::Chapter::Display", /* name */
    Display__index, /* indextable */
    NULL, /* indexfunc */
};

static int Chapter__call(lua_State* L) {
    int args = lua_gettop(L);
    TagLib::Matroska::Chapter* c = NULL;

    switch(args) {
        case 1: {
            if( Matroska::Chapter::isValid(L, 1) ) {
                c = new TagLib::Matroska::Chapter(Matroska::Chapter::checkValue(L, 1));
                break;
            }
            break;
        }

        case 4: {
            c = new TagLib::Matroska::Chapter(
              luaL_checkinteger(L, 1),
              luaL_checkinteger(L, 2),
              ValueList<TagLib::List<TagLib::Matroska::Chapter::Display>,Matroska::Chapter::Display>::checkValue(L,3),
              luaL_checkinteger(L, 4)
            );
            break;
        }

        default: break;
    }
    if(c == NULL) return luaL_error(L, "invalid arguments");

    Matroska::Chapter::pushPtr(L, c);
    return 1;
}

static int Chapter_uid(lua_State* L) {
    lua_pushinteger(L,
      Matroska::Chapter::checkPtr(L,1)->uid()
    );
    return 1;
}

static int Chapter_timeStart(lua_State* L) {
    lua_pushinteger(L,
      Matroska::Chapter::checkPtr(L,1)->timeStart()
    );
    return 1;
}

static int Chapter_timeEnd(lua_State* L) {
    lua_pushinteger(L,
      Matroska::Chapter::checkPtr(L,1)->timeEnd()
    );
    return 1;
}

static int Chapter_isHidden(lua_State* L) {
    lua_pushboolean(L,
      Matroska::Chapter::checkPtr(L,1)->isHidden()
    );
    return 1;
}

static int Chapter_swap(lua_State* L) {
    Matroska::Chapter::checkPtr(L,1)->swap(Matroska::Chapter::checkValue(L,2));
    lua_settop(L,1);
    return 1;
}

static int Chapter_displayList(lua_State* L) {
    ConstValueListReference<TagLib::List<TagLib::Matroska::Chapter::Display>,Matroska::Chapter::Display>::pushRef(L,
      Matroska::Chapter::checkPtr(L,1)->displayList(),
      1
    );
    return 1;
}

static
const luaL_Reg Chapter__index[] = {
    { "swap", Chapter_swap },
    { "uid", Chapter_uid },
    { "timeStart", Chapter_timeStart },
    { "timeEnd", Chapter_timeEnd },
    { "isHidden", Chapter_isHidden },
    { "displayList", Chapter_displayList },
    { NULL, NULL }
};

static int Chapter__submodules(lua_State* L) {
    luaL_requiref(L, "TagLib.Matroska.Chapter.Display",
      luaopen_TagLib_Matroska_Chapter_Display, 0);
    lua_setfield(L, -2, "Display");
    return 0;
}

LTAGLIB_PUBLIC
int luaopen_TagLib_Matroska_Chapter(lua_State *L) {
    return Matroska::Chapter::open(L);
}

template<>
const UserdataTable Matroska::Chapter::base::mod = {
    Chapter__call, /* call */
    NULL, /* __index */
    Chapter__submodules, /* init */
};

template<>
const UserdataMetatable Matroska::Chapter::base::metatable = {
    "TagLib::Matroska::Chapter", /* name */
    Chapter__index, /* indextable */
    NULL, /* indexfunc */
};

#include "../shared/userdata.tcc"
template class LuaTagLib::BaseUserdata<TagLib::Matroska::Chapter>;
template class LuaTagLib::BaseUserdata<TagLib::Matroska::Chapter::Display>;

template<>
const char* ConstValueListReference<TagLib::List<TagLib::Matroska::Chapter::Display>,Matroska::Chapter::Display>::base::__name = "TagLib::List<TagLib::Matroska::Chapter::Display>";

template<>
const char* ConstValueListReference<TagLib::List<TagLib::Matroska::Chapter>,Matroska::Chapter>::base::__name = "TagLib::List<TagLib::Matroska::Chapter>";

