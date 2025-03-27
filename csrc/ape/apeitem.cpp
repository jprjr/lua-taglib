#include "apeitem.h"

#if LTAGLIB_HAS_APE_ITEM

#include "../tstring.h"
#include "../tstringlist.h"
#include "../tbytevector.h"

using namespace LuaTagLib;

static int Item__call(lua_State* L) {
    int args = lua_gettop(L);
    TagLib::APE::Item* i = NULL;

    switch(args) {
        case 0: {
            i = new TagLib::APE::Item();
            break;
        }
        case 1: {
            i = new TagLib::APE::Item(APE::Item::checkValue(L, 1));
            break;
        }
        case 2: {
            if(String::isValid(L, 2)) {
                i = new TagLib::APE::Item(String::checkValue(L, 1), String::checkValue(L, 2));
                break;
            }
#if LTAGLIB_ATLEAST(LTAGLIB_1_4)
            if(lua_istable(L, 2)) {
                i = new TagLib::APE::Item(String::checkValue(L, 1), StringList::checkValue(L, 2));
                break;
            }
#endif
            break;
        }
#if LTAGLIB_ATLEAST(LTAGLIB_1_8)
        case 3: {
            i = new TagLib::APE::Item(String::checkValue(L, 1), ByteVector::looseValue(L, 2), lua_toboolean(L, 3));
            break;
        }
#endif
        default: break;
    }
    if(i == NULL) return luaL_error(L, "invalid arguments");
    APE::Item::pushPtr(L, i);
    return 1;
}

static int Item_key(lua_State* L) {
    TagLib::APE::Item* item = APE::Item::checkPtr(L, 1);
    String::pushValue(L, item->key());
    return 1;
}

#if LTAGLIB_ATLEAST(LTAGLIB_1_8)
static int Item_binaryData(lua_State* L) {
    TagLib::APE::Item* item = APE::Item::checkPtr(L, 1);
    ByteVector::pushValue(L, item->binaryData());
    return 1;
}

static int Item_setBinaryData(lua_State* L) {
    TagLib::APE::Item* item = APE::Item::checkPtr(L, 1);
    item->setBinaryData(ByteVector::looseValue(L, 2));

    lua_settop(L,1);
    return 1;
}
#endif

#if LTAGLIB_ATLEAST(LTAGLIB_1_5)
static int Item_setKey(lua_State* L) {
    TagLib::APE::Item* item = APE::Item::checkPtr(L, 1);
    item->setKey(String::checkValue(L, 2));

    lua_settop(L,1);
    return 1;
}

static int Item_setValue(lua_State* L) {
    TagLib::APE::Item* item = APE::Item::checkPtr(L, 1);
    item->setValue(String::checkValue(L, 2));

    lua_settop(L,1);
    return 1;
}

static int Item_setValues(lua_State* L) {
    TagLib::APE::Item* item = APE::Item::checkPtr(L, 1);
    item->setValues(StringList::checkValue(L, 2));

    lua_settop(L,1);
    return 1;
}

static int Item_appendValue(lua_State* L) {
    TagLib::APE::Item* item = APE::Item::checkPtr(L, 1);
    item->appendValue(String::checkValue(L, 2));

    lua_settop(L,1);
    return 1;
}

static int Item_appendValues(lua_State* L) {
    TagLib::APE::Item* item = APE::Item::checkPtr(L, 1);
    item->appendValues(StringList::checkValue(L, 2));

    lua_settop(L,1);
    return 1;
}

static int Item_values(lua_State* L) {
    TagLib::APE::Item* item = APE::Item::checkPtr(L, 1);
    StringList::pushValue(L, item->values());
    return 1;
}
#endif

static int Item_size(lua_State* L) {
    TagLib::APE::Item* item = APE::Item::checkPtr(L, 1);
    lua_pushinteger(L, item->size());
    return 1;
}

#if LTAGLIB_UNDER(LTAGLIB_2_0)
static int Item_value(lua_State* L) {
    TagLib::APE::Item* item = APE::Item::checkPtr(L, 1);
    ByteVector::pushValue(L, item->value());
    return 1;
}
#endif

static int Item_toString(lua_State* L) {
    TagLib::APE::Item* item = APE::Item::checkPtr(L, 1);
    String::pushValue(L, item->toString());
    return 1;
}

#if LTAGLIB_UNDER(LTAGLIB_2_0)
static int Item_toStringList(lua_State* L) {
    TagLib::APE::Item* item = APE::Item::checkPtr(L, 1);
    StringList::pushValue(L, item->toStringList());
    return 1;
}
#endif

static int Item_render(lua_State* L) {
    TagLib::APE::Item* item = APE::Item::checkPtr(L, 1);
    ByteVector::pushValue(L, item->render());
    return 1;
}

static int Item_parse(lua_State* L) {
    TagLib::APE::Item* item = APE::Item::checkPtr(L, 1);
    item->parse(ByteVector::looseValue(L, 2));
    return 0;
}

static int Item_isReadOnly(lua_State* L) {
    TagLib::APE::Item* item = APE::Item::checkPtr(L, 1);
    lua_pushboolean(L, item->isReadOnly());
    return 1;
}

static int Item_setReadOnly(lua_State* L) {
    TagLib::APE::Item* item = APE::Item::checkPtr(L, 1);
    item->setReadOnly(lua_toboolean(L, 2));

    lua_settop(L,1);
    return 1;
}

static int Item_setType(lua_State* L) {
    TagLib::APE::Item* item = APE::Item::checkPtr(L, 1);
    item->setType(APE::Item::ItemTypes::checkValue(L, 2));

    lua_settop(L,1);
    return 1;
}

static int Item_type(lua_State* L) {
    TagLib::APE::Item* item = APE::Item::checkPtr(L, 1);
    APE::Item::ItemTypes::pushValue(L, item->type());
    return 1;
}

static int Item_isEmpty(lua_State* L) {
    TagLib::APE::Item* item = APE::Item::checkPtr(L, 1);
    lua_pushboolean(L, item->isEmpty());
    return 1;
}

#if LTAGLIB_ATLEAST(LTAGLIB_1_11)
static int Item_swap(lua_State* L) {
    APE::Item::checkPtr(L,1)->swap(APE::Item::checkValue(L,2));

    lua_settop(L,1);
    return 1;
}
#endif

static
const luaL_Reg Item__index[] = {
#if LTAGLIB_ATLEAST(LTAGLIB_1_8)
    { "binaryData", Item_binaryData },
    { "setBinaryData", Item_setBinaryData },
#endif
#if LTAGLIB_ATLEAST(LTAGLIB_1_5)
    { "setKey", Item_setKey },
    { "setValue", Item_setValue },
    { "setValues", Item_setValues },
    { "appendValue", Item_appendValue },
    { "appendValues", Item_appendValues },
    { "values", Item_values },
#endif
    { "key", Item_key },
    { "size", Item_size },
#if LTAGLIB_UNDER(LTAGLIB_2_0)
    { "value", Item_value },
#endif
    { "toString", Item_toString },
#if LTAGLIB_UNDER(LTAGLIB_2_0)
    { "toStringList", Item_toStringList },
#endif
    { "render", Item_render },
    { "parse", Item_parse },
    { "isReadOnly", Item_isReadOnly },
    { "setReadOnly", Item_setReadOnly },
    { "setType", Item_setType },
    { "type", Item_type },
    { "isEmpty", Item_isEmpty },
#if LTAGLIB_ATLEAST(LTAGLIB_1_11)
    { "swap", Item_swap },
#endif
    { NULL, NULL }
};

#define E(x) { #x, sizeof(#x) - 1, TagLib::APE::Item::x }

static const
APE::Item::ItemTypes::enum_type apeItemTypes[] = {
    E(Text), E(Binary), E(Locator)
};

static int Item__submodules(lua_State* L) {
    luaL_requiref(L, "TagLib.APE.Item.ItemTypes", luaopen_TagLib_APE_Item_ItemTypes, 0);
    lua_setfield(L, -2, "ItemTypes");
    return 0;
}


LTAGLIB_PUBLIC
int luaopen_TagLib_APE_Item(lua_State *L) {
    return APE::Item::open(L);
}

LTAGLIB_PUBLIC
int luaopen_TagLib_APE_Item_ItemTypes(lua_State *L) {
    return APE::Item::ItemTypes::open(L);
}

template<>
const UserdataTable APE::Item::base::mod = {
    Item__call,
    NULL,
    Item__submodules,
};

template<>
const UserdataMetatable APE::Item::base::metatable = {
    "TagLib::APE::Item", /* name */
    Item__index, /* indextable */
    NULL, /* indexfunc */
};

template<>
const APE::Item::ItemTypes::enum_type*
APE::Item::ItemTypes::m_values = apeItemTypes;

template<>
const size_t APE::Item::ItemTypes::m_len = sizeof(apeItemTypes) / sizeof(apeItemTypes[0]);

#include "../shared/enum.tcc"
template class LuaTagLib::Enum<TagLib::APE::Item::ItemTypes>;

#include "../shared/userdata.tcc"
template class LuaTagLib::BaseUserdata<TagLib::APE::Item>;

#endif
