#include "apetag.h"

#if LTAGLIB_HAS_APE_TAG

#include "apeitem.h"
#include "apefooter.h"
#include "../tstring.h"
#include "../tbytevector.h"
#include "../tfile.h"
#include "../tmap.h"

#define T APE::Tag
#define TT TagLib::T
#define XSTR(s) STR(s)
#define STR(s) #s
#define NAME XSTR(TT)

using namespace LuaTagLib;

static int Tag__call(lua_State* L) {
    int args = lua_gettop(L);
    TT* t = NULL;

    switch(args) {
        case 0: {
            t = new TT();
            break;
        }
        case 2: {
            t = new TT(LuaTagLib::File::checkPtr(L, 1), luaL_checkinteger(L, 2));
            break;
        }
        default: break;
    }

    if(t == NULL) return luaL_error(L, "invalid arguments");
    T::pushPtr(L, t);
    return 1;
}

static int Tag_footer(lua_State* L) {
    TT* tag = T::checkPtr(L, 1);
    APE::Footer::pushPtr(L, tag->footer(), 1);
    return 1;
}

typedef ConstValueMapReference<TagLib::APE::ItemListMap, String, APE::Item> ItemListMap;
static int Tag_itemListMap(lua_State* L) {
    ItemListMap::pushRef(L, T::checkPtr(L, 1)->itemListMap(), 1);
    return 1;
}

static int Tag_removeItem(lua_State* L) {
    TT* tag = T::checkPtr(L, 1);
    tag->removeItem(String::checkValue(L, 2));

    lua_settop(L,1);
    return 1;
}

static int Tag_addValue(lua_State* L) {
    int args = lua_gettop(L);
    TT* tag = T::checkPtr(L, 1);

    switch(args) {
        case 3: {
            tag->addValue(String::checkValue(L,2), String::checkValue(L,3));
            break;
        }
        case 4: {
            tag->addValue(String::checkValue(L,2), String::checkValue(L,3), lua_toboolean(L, 4));
            break;
        }
        default: return luaL_error(L, "invalid arguments");
    }

    lua_settop(L,1);
    return 1;
}

#if LTAGLIB_ATLEAST(LTAGLIB_1_8)
static int Tag_setData(lua_State* L) {
    TT* tag = T::checkPtr(L, 1);
    tag->setData(String::checkValue(L,2), ByteVector::looseValue(L,3));

    lua_settop(L,1);
    return 1;
}
#endif

static int Tag_setItem(lua_State* L) {
    TT* tag = T::checkPtr(L, 1);
    tag->setItem(String::checkValue(L,2), APE::Item::checkValue(L, 3));

    lua_settop(L,1);
    return 1;
}

static int Tag_isEmpty(lua_State* L) {
    TT* tag = T::checkPtr(L, 1);
    lua_pushboolean(L, tag->isEmpty());
    return 1;
}

static int Tag_render(lua_State* L) {
    TT* tag = T::checkPtr(L, 1);
    ByteVector::pushValue(L, tag->render());
    return 1;
}

static const luaL_Reg Tag__index[] = {
    { "footer", Tag_footer },
    { "itemListMap", Tag_itemListMap },
    { "removeItem", Tag_removeItem },
    { "addValue", Tag_addValue },
#if LTAGLIB_ATLEAST(LTAGLIB_1_8)
    { "setData", Tag_setData },
#endif
    { "setItem", Tag_setItem },
    { "isEmpty", Tag_isEmpty },
    { "render", Tag_render },
    { NULL, NULL }
};

static int Tag_static_fileIdentifier(lua_State* L) {
    ByteVector::pushValue(L, TT::fileIdentifier());
    return 1;
}

#if LTAGLIB_ATLEAST(LTAGLIB_1_8)
static int Tag_static_checkKey(lua_State* L) {
    lua_pushboolean(L, TT::checkKey(String::checkValue(L, 1)));
    return 1;
}
#endif

static const luaL_Reg Tag_static_methods[] = {
    { "fileIdentifier", Tag_static_fileIdentifier },
#if LTAGLIB_ATLEAST(LTAGLIB_1_8)
    { "checkKey", Tag_static_checkKey },
#endif
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_APE_Tag(lua_State* L) {
    return T::open(L);
}

template<>
const UserdataTable APE::Tag::base::mod = {
    Tag__call,
    Tag_static_methods,
    NULL,
};

template<>
const UserdataMetatable APE::Tag::base::metatable = {
    NAME, /* name */
    Tag__index, /* indextable */
    NULL, /* indexfunc */
};

template<>
const char* ItemListMap::base::__name = "TagLib::APE::ItemListMap";

#undef T
#include "../shared/userdata.tcc"
template class LuaTagLib::DerivedUserdata<TagLib::APE::Tag, LuaTagLib::Tag>;

#endif
