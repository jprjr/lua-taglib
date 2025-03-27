#include "mp4tag.h"

#if LTAGLIB_HAS_MP4

#include "../tmap.h"
#include "../tstring.h"
#include "mp4item.h"

using namespace LuaTagLib;

static int Tag__call(lua_State* L) {
    int args = lua_gettop(L);
    TagLib::MP4::Tag* t = NULL;

    switch(args) {
#if LTAGLIB_ATLEAST(LTAGLIB_1_8)
        case 0: {
            t = new TagLib::MP4::Tag();
            break;
        }
#endif
        default: break;
    }

    if(t == NULL) return luaL_error(L, "invalid arguments");
    MP4::Tag::pushPtr(L, t);
    return 1;
}

static int Tag_save(lua_State* L) {
    lua_pushboolean(L, MP4::Tag::checkPtr(L, 1)->save() );
    return 1;
}

#if LTAGLIB_UNDER(LTAGLIB_1_12)
typedef ValueMapReference<TagLib::MP4::ItemListMap, String, MP4::Item> ItemListMap;

static int Tag_itemListMap(lua_State* L) {
    TagLib::MP4::Tag* tag = MP4::Tag::checkPtr(L, 1);

    ItemListMap::pushRef(L, tag->itemListMap(), 1);
    return 1;
}
#endif

#if LTAGLIB_ATLEAST(LTAGLIB_1_10)
typedef ConstValueMapReference<TagLib::MP4::ItemMap, String, MP4::Item> ItemMap;

static int Tag_itemMap(lua_State* L) {
    ItemMap::pushRef(L, MP4::Tag::checkPtr(L,1)->itemMap(), 1);
    return 1;
}

static int Tag_item(lua_State* L) {
    MP4::Item::pushValue(L, MP4::Tag::checkPtr(L,1)->item(String::checkValue(L,2)));
    return 1;
}

static int Tag_setItem(lua_State* L) {
    MP4::Tag::checkPtr(L,1)->setItem(String::checkValue(L,2), MP4::Item::checkValue(L,3));
    lua_settop(L,1);
    return 1;
}

static int Tag_removeItem(lua_State* L) {
    MP4::Tag::checkPtr(L,1)->removeItem(String::checkValue(L,2));
    lua_settop(L,1);
    return 1;
}

static int Tag_contains(lua_State* L) {
    lua_pushboolean(L, MP4::Tag::checkPtr(L,1)->contains(String::checkValue(L,2)));
    return 1;
}
#endif

#if LTAGLIB_ATLEAST(LTAGLIB_1_13)
static int Tag_strip(lua_State* L) {
    lua_pushboolean(L, MP4::Tag::checkPtr(L,1)->strip());
    return 1;
}
#endif

static const luaL_Reg Tag__index[] = {
    { "save", Tag_save },
#if LTAGLIB_UNDER(LTAGLIB_1_12)
    { "itemListMap", Tag_itemListMap },
#endif
#if LTAGLIB_ATLEAST(LTAGLIB_1_10)
    { "itemMap", Tag_itemMap },
    { "item", Tag_item },
    { "setItem", Tag_setItem },
    { "removeItem", Tag_removeItem },
    { "contains", Tag_contains },
#endif
#if LTAGLIB_ATLEAST(LTAGLIB_1_13)
    { "strip", Tag_strip },
#endif
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_MP4_Tag(lua_State* L) {
    return MP4::Tag::open(L);
}

template<>
const UserdataTable MP4::Tag::base::mod = {
    Tag__call,
    NULL,
    NULL,
};

template<>
const UserdataMetatable MP4::Tag::base::metatable = {
    "TagLib::MP4::Tag", /* name */
    Tag__index, /* indextable */
    NULL, /* indexfunc */
};

#if LTAGLIB_UNDER(LTAGLIB_1_12)
template<>
const char* ItemListMap::base::__name = "TagLib::MP4::ItemListMap";
#else
template<>
const char* ItemMap::base::__name = "TagLib::MP4::ItemMap";
#endif

#include "../shared/userdata.tcc"
template class LuaTagLib::DerivedUserdata<TagLib::MP4::Tag, LuaTagLib::Tag>;

#endif
