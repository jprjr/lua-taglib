#include "matroskatag.h"
#include "matroskasimpletag.h"

#include "../tstring.h"
#include "../tlist.h"

using namespace LuaTagLib;

static int Tag__call(lua_State* L) {
    int args = lua_gettop(L);
    TagLib::Matroska::Tag* t = NULL;

    switch(args) {
        case 0: {
            t = new TagLib::Matroska::Tag();
            break;
        }
        default: break;
    }

    if(t == NULL) return luaL_error(L, "invalid arguments");
    Matroska::Tag::pushPtr(L, t);
    return 1;
}

static int Tag_addSimpleTag(lua_State* L) {
    Matroska::Tag::checkPtr(L, 1)->addSimpleTag(
      Matroska::SimpleTag::checkValue(L, 2)
    );
    lua_settop(L, 1);
    return 1;
}

static int Tag_addSimpleTags(lua_State* L) {
    Matroska::Tag::checkPtr(L, 1)->addSimpleTags(
      ValueList<TagLib::Matroska::SimpleTagsList,Matroska::SimpleTag>::checkValue(L,2) 
    );
    lua_settop(L, 1);
    return 1;
}

static int Tag_insertSimpleTag(lua_State* L) {
    Matroska::Tag::checkPtr(L, 1)->insertSimpleTag(
      luaL_checkinteger(L, 2),
      Matroska::SimpleTag::checkValue(L, 3)
    );
    lua_settop(L, 1);
    return 1;
}

static int Tag_removeSimpleTag(lua_State* L) {
    int args = lua_gettop(L);

    switch(args) {
        case 3: {
            Matroska::Tag::checkPtr(L, 1)->removeSimpleTag(
              String::checkValue(L, 2),
              Matroska::SimpleTag::TargetTypeValue::checkValue(L, 3)
            );
            break;
        }
        case 4: {
            Matroska::Tag::checkPtr(L, 1)->removeSimpleTag(
              String::checkValue(L, 2),
              Matroska::SimpleTag::TargetTypeValue::checkValue(L, 3),
              luaL_checkinteger(L, 4)
            );
            break;
        }
        default: return luaL_error(L, "invalid arguments");
    }

    lua_settop(L, 1);
    return 1;
}

static int Tag_clearSimpleTags(lua_State* L) {
    Matroska::Tag::checkPtr(L, 1)->clearSimpleTags();
    lua_settop(L, 1);
    return 1;
}

static int Tag_simpleTagsList(lua_State* L) {
    ConstValueListReference<TagLib::Matroska::SimpleTagsList,Matroska::SimpleTag>::pushRef(L,
      Matroska::Tag::checkPtr(L,1)->simpleTagsList(),
      1
    );
    return 1;
}

static const luaL_Reg Tag__index[] = {
    { "addSimpleTag", Tag_addSimpleTag },
    { "addSimpleTags", Tag_addSimpleTags },
    { "insertSimpleTag", Tag_insertSimpleTag },
    { "removeSimpleTag", Tag_removeSimpleTag },
    { "clearSimpleTags", Tag_clearSimpleTags },
    { "simpleTagsList", Tag_simpleTagsList },
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_Matroska_Tag(lua_State* L) {
    return Matroska::Tag::open(L);
}

template<>
const UserdataTable Matroska::Tag::base::mod = {
    Tag__call,
    NULL,
    NULL,
};

template<>
const UserdataMetatable Matroska::Tag::base::metatable = {
    "TagLib::Matroska::Tag", /* name */
    Tag__index, /* indextable */
    NULL, /* indexfunc */
};

#include "../shared/userdata.tcc"
template class LuaTagLib::DerivedUserdata<TagLib::Matroska::Tag, LuaTagLib::Tag>;


template<>
const char* ConstValueListReference<TagLib::Matroska::SimpleTagsList,Matroska::SimpleTag>::base::__name = "TagLib::Matroska::SimpleTagsList";
