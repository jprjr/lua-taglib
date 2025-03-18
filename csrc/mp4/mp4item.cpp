#include "mp4item.h"

#if LTAGLIB_HAS_MP4

#include "../tstringlist.h"
#include "mp4coverart.h"

#if LTAGLIB_ATLEAST(LTAGLIB_1_8)
#include "../tbytevectorlist.h"
#endif

using namespace LuaTagLib;


static int Item__call(lua_State* L) {
    int args = lua_gettop(L);
    TagLib::MP4::Item* i = NULL;

    switch(args) {
        case 0: {
            i = new TagLib::MP4::Item();
            break;
        }
        case 1: {
            if( MP4::Item::isValid(L, 1) ) {
                i = new TagLib::MP4::Item(MP4::Item::checkValue(L, 1));
                break;
            }

#if LTAGLIB_ATLEAST(LTAGLIB_1_7)
            if( (MP4::CoverArtList::isValid(L, 1))) {
                i = new TagLib::MP4::Item(MP4::CoverArtList::checkValue(L, 1));
                break;
            }
#endif

#if LTAGLIB_ATLEAST(LTAGLIB_1_8)
            /* this returns true if, and only if, the list is true-blue bytevectors (not strings) */
            if( (ByteVectorList::isValid(L, 1))) {
                i = new TagLib::MP4::Item(ByteVectorList::checkValue(L, 1));
                break;
            }
#endif
            switch(lua_type(L, 1)) {
                case LUA_TNUMBER: {
                    i = new TagLib::MP4::Item((int) lua_tointeger(L, 1));
                    break;
                }
                case LUA_TBOOLEAN: {
                    i = new TagLib::MP4::Item((bool) lua_toboolean(L, 1));
                    break;
                }
                case LUA_TTABLE: {
                    i = new TagLib::MP4::Item(StringList::checkValue(L, 1) );
                    break;
                }
                default: break;
            }
            break;

        }
        case 2: {
            i = new TagLib::MP4::Item((int)luaL_checkinteger(L, 1), (int) luaL_checkinteger(L, 2));
            break;
        }
        default: break;
    }
    if(i == NULL) return luaL_error(L, "invalid arguments");

    MP4::Item::pushPtr(L, i);
    return 1;
}

static int Item_toInt(lua_State* L) {
    TagLib::MP4::Item* item = MP4::Item::checkPtr(L, 1);
    lua_pushinteger(L, item->toInt());
    return 1;
}

static int Item_toBool(lua_State* L) {
    TagLib::MP4::Item* item = MP4::Item::checkPtr(L, 1);
    lua_pushboolean(L, item->toBool());
    return 1;
}

static int Item_toIntPair(lua_State* L) {
    TagLib::MP4::Item* item = MP4::Item::checkPtr(L, 1);
    TagLib::MP4::Item::IntPair p = item->toIntPair();
    lua_newtable(L);
    lua_pushinteger(L, p.first);
    lua_rawseti(L, -2, 1);
    lua_pushinteger(L, p.second);
    lua_rawseti(L, -2, 2);
    return 1;
}

static int Item_toStringList(lua_State* L) {
    TagLib::MP4::Item* item = MP4::Item::checkPtr(L, 1);
    StringList::pushValue(L, item->toStringList());
    return 1;
}

static int Item_isValid(lua_State* L) {
    TagLib::MP4::Item* item = MP4::Item::checkPtr(L, 1);
    lua_pushboolean(L, item->isValid());
    return 1;
}

#if LTAGLIB_ATLEAST(LTAGLIB_1_7)
static int Item_toCoverArtList(lua_State* L) {
    TagLib::MP4::Item* item = MP4::Item::checkPtr(L, 1);

    ValueList<TagLib::MP4::CoverArtList, MP4::CoverArt>::pushValue(L,
      item->toCoverArtList());
    return 1;
}
#endif

#if LTAGLIB_ATLEAST(LTAGLIB_1_8)
static int Item_toByte(lua_State* L) {
    lua_pushinteger(L, MP4::Item::checkPtr(L, 1)->toByte());
    return 1;
}

static int Item_toUInt(lua_State* L) {
    lua_pushinteger(L, MP4::Item::checkPtr(L, 1)->toUInt());
    return 1;
}

static int Item_toLongLong(lua_State* L) {
    lua_pushinteger(L, MP4::Item::checkPtr(L, 1)->toLongLong());
    return 1;
}

static int Item_toByteVectorList(lua_State* L) {
    ByteVectorList::pushValue(L, MP4::Item::checkPtr(L, 1)->toByteVectorList());
    return 1;
}
#endif

#if LTAGLIB_ATLEAST(LTAGLIB_1_11)
static int Item_swap(lua_State* L) {
    MP4::Item::checkPtr(L,1)->swap(MP4::Item::checkValue(L,2));
    lua_settop(L,1);
    return 1;
}
#endif

#if LTAGLIB_ATLEAST(LTAGLIB_2_0)
static int Item_type(lua_State* L) {
    MP4::Item::Type::pushValue(L, MP4::Item::checkPtr(L,1)->type());
    return 1;
}
#endif

static
const luaL_Reg Item__index[] = {
    { "toInt", Item_toInt },
    { "toBool", Item_toBool },
    { "toIntPair", Item_toIntPair },
    { "toStringList", Item_toStringList },
    { "isValid", Item_isValid },
#if LTAGLIB_ATLEAST(LTAGLIB_1_7)
    { "toCoverArtList", Item_toCoverArtList },
#endif
#if LTAGLIB_ATLEAST(LTAGLIB_1_8)
    { "toByte", Item_toByte },
    { "toUInt", Item_toUInt },
    { "toLongLong", Item_toLongLong },
    { "toByteVectorList", Item_toByteVectorList },
#endif
#if LTAGLIB_ATLEAST(LTAGLIB_1_11)
    { "swap", Item_swap },
#endif
#if LTAGLIB_ATLEAST(LTAGLIB_2_0)
    { "type", Item_type },
#endif
    { NULL, NULL }
};

static int Item__submodules(lua_State* L) {
#if LTAGLIB_ATLEAST(LTAGLIB_2_0)
    luaL_requiref(L, "TagLib.MP4.Item.Type",
      luaopen_TagLib_MP4_Item_Type, 0);
    lua_setfield(L, -2, "Type");
#else
    (void)L;
#endif
    return 0;
}

LTAGLIB_PUBLIC
int luaopen_TagLib_MP4_Item(lua_State *L) {
    return MP4::Item::open(L);
}

#if LTAGLIB_ATLEAST(LTAGLIB_2_0)
#define E(x) { #x, sizeof(#x) - 1, TagLib::MP4::Item::Type::x }
static const MP4::Item::Type::enum_type mp4Types[] = {
    E(Void), E(Bool), E(Int), E(IntPair),
    E(Byte), E(UInt), E(LongLong), E(StringList),
    E(ByteVectorList), E(CoverArtList)
};

LTAGLIB_PUBLIC
int luaopen_TagLib_MP4_Item_Type(lua_State* L) {
    return MP4::Item::Type::open(L);
}

#endif

template<>
const UserdataTable MP4::Item::base::mod = {
    Item__call, /* call */
    NULL, /* __index */
    Item__submodules, /* init */
};

template<>
const UserdataMetatable MP4::Item::base::metatable = {
    "TagLib::MP4::Item", /* name */
    Item__index, /* indextable */
    NULL, /* indexfunc */
};

#if LTAGLIB_ATLEAST(LTAGLIB_1_7)
template<>
const char *ValueList<TagLib::MP4::CoverArtList, MP4::CoverArt>::base::__name =
  "TagLib::MP4::CoverArtList";
#endif

#if LTAGLIB_ATLEAST(LTAGLIB_2_0)

template<>
const MP4::Item::Type::enum_type*
MP4::Item::Type::m_values = mp4Types;

template<>
const size_t MP4::Item::Type::m_len = sizeof(mp4Types) / sizeof(mp4Types[0]);

#include "../shared/enum.tcc"
template class Enum<TagLib::MP4::Item::Type>;

#endif

#include "../shared/userdata.tcc"
template class BaseUserdata<TagLib::MP4::Item>;

#endif
