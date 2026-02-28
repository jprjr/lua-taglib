#include "matroskasimpletag.h"

#include "../tstring.h"
#include "../tbytevector.h"

using namespace LuaTagLib;

static int SimpleTag__call(lua_State* L) {
    int args = lua_gettop(L);
    TagLib::Matroska::SimpleTag* t = NULL;

    switch(args) {
        case 1: {
            if(Matroska::SimpleTag::isValid(L, 1)) {
                t = new TagLib::Matroska::SimpleTag(Matroska::SimpleTag::checkValue(L, 1));
                break;
            }
            break;
        }
        case 2: {
            if(ByteVector::isValid(L, 2)) {
                t = new TagLib::Matroska::SimpleTag(String::checkValue(L, 1), ByteVector::checkValue(L, 2));
            } else {
                t = new TagLib::Matroska::SimpleTag(String::checkValue(L, 1), String::checkValue(L, 2));
            }
            break;
        }
        case 3: {
            if(ByteVector::isValid(L, 2)) {
                t = new TagLib::Matroska::SimpleTag(
                    String::checkValue(L, 1),
                    ByteVector::checkValue(L, 2),
                    Matroska::SimpleTag::TargetTypeValue::checkValue(L, 3)
                );
            } else {
                t = new TagLib::Matroska::SimpleTag(
                    String::checkValue(L, 1),
                    String::checkValue(L, 2),
                    Matroska::SimpleTag::TargetTypeValue::checkValue(L, 3)
                );
            }
            break;
        }
        case 4: {
            if(ByteVector::isValid(L, 2)) {
                t = new TagLib::Matroska::SimpleTag(
                    String::checkValue(L, 1),
                    ByteVector::checkValue(L, 2),
                    Matroska::SimpleTag::TargetTypeValue::checkValue(L, 3),
                    String::checkValue(L, 4)
                );
            } else {
                t = new TagLib::Matroska::SimpleTag(
                    String::checkValue(L, 1),
                    String::checkValue(L, 2),
                    Matroska::SimpleTag::TargetTypeValue::checkValue(L, 3),
                    String::checkValue(L, 4)
                );
            }
            break;
        }
        case 5: {
            if(ByteVector::isValid(L, 2)) {
                t = new TagLib::Matroska::SimpleTag(
                    String::checkValue(L, 1),
                    ByteVector::checkValue(L, 2),
                    Matroska::SimpleTag::TargetTypeValue::checkValue(L, 3),
                    String::checkValue(L, 4),
                    lua_toboolean(L, 5)
                );
            } else {
                t = new TagLib::Matroska::SimpleTag(
                    String::checkValue(L, 1),
                    String::checkValue(L, 2),
                    Matroska::SimpleTag::TargetTypeValue::checkValue(L, 3),
                    String::checkValue(L, 4),
                    lua_toboolean(L, 5)
                );
            }
            break;
        }
        case 6: {
            if(ByteVector::isValid(L, 2)) {
                t = new TagLib::Matroska::SimpleTag(
                    String::checkValue(L, 1),
                    ByteVector::checkValue(L, 2),
                    Matroska::SimpleTag::TargetTypeValue::checkValue(L, 3),
                    String::checkValue(L, 4),
                    lua_toboolean(L, 5),
                    luaL_checkinteger(L, 6)
                );
            } else {
                t = new TagLib::Matroska::SimpleTag(
                    String::checkValue(L, 1),
                    String::checkValue(L, 2),
                    Matroska::SimpleTag::TargetTypeValue::checkValue(L, 3),
                    String::checkValue(L, 4),
                    lua_toboolean(L, 5),
                    luaL_checkinteger(L, 6)
                );
            }
            break;
        }

        default: break;
    }
    if(t == NULL) return luaL_error(L, "invalid arguments");
    Matroska::SimpleTag::pushPtr(L, t);
    return 1;
}

static int SimpleTag_swap(lua_State* L) {
    Matroska::SimpleTag::checkPtr(L, 1)->swap(Matroska::SimpleTag::checkValue(L, 2));
    lua_settop(L, 1);
    return 1;
}

static int SimpleTag_name(lua_State* L) {
    String::pushValue(L, Matroska::SimpleTag::checkPtr(L, 1)->name());
    return 1;
}

static int SimpleTag_targetTypeValue(lua_State* L) {
    Matroska::SimpleTag::TargetTypeValue::pushValue(
      L, Matroska::SimpleTag::checkPtr(L,1)->targetTypeValue()
    );
    return 1;
}

static int SimpleTag_language(lua_State* L) {
    String::pushValue(L, Matroska::SimpleTag::checkPtr(L, 1)->language());
    return 1;
}

static int SimpleTag_defaultLanguageFlag(lua_State* L) {
    lua_pushboolean(L, Matroska::SimpleTag::checkPtr(L, 1)->defaultLanguageFlag());
    return 1;
}

static int SimpleTag_trackUid(lua_State* L) {
    lua_pushinteger(L, Matroska::SimpleTag::checkPtr(L, 1)->trackUid());
    return 1;
}

static int SimpleTag_type(lua_State* L) {
    Matroska::SimpleTag::ValueType::pushValue(
      L, Matroska::SimpleTag::checkPtr(L,1)->type()
    );
    return 1;
}

static int SimpleTag_toString(lua_State* L) {
    String::pushValue(L, Matroska::SimpleTag::checkPtr(L, 1)->toString());
    return 1;
}

static int SimpleTag_toByteVector(lua_State* L) {
    ByteVector::pushValue(L, Matroska::SimpleTag::checkPtr(L, 1)->toByteVector());
    return 1;
}

static
const luaL_Reg SimpleTag__index[] = {
    { "swap", SimpleTag_swap },
    { "name", SimpleTag_name },
    { "targetTypeValue", SimpleTag_targetTypeValue },
    { "language", SimpleTag_language },
    { "defaultLanguageFlag", SimpleTag_defaultLanguageFlag },
    { "trackUid", SimpleTag_trackUid },
    { "type", SimpleTag_type },
    { "toString", SimpleTag_toString },
    { "toByteVector", SimpleTag_toByteVector },
    { NULL, NULL }
};

static int SimpleTag__submodules(lua_State* L) {
    luaL_requiref(L, "TagLib.Matroska.SimpleTag.ValueType",
      luaopen_TagLib_Matroska_SimpleTag_ValueType, 0);
    lua_setfield(L, -2, "ValueType");

    luaL_requiref(L, "TagLib.Matroska.SimpleTag.TargetTypeValue",
      luaopen_TagLib_Matroska_SimpleTag_TargetTypeValue, 0);
    lua_setfield(L, -2, "TargetTypeValue");

    return 0;
}

LTAGLIB_PUBLIC
int luaopen_TagLib_Matroska_SimpleTag(lua_State *L) {
    return Matroska::SimpleTag::open(L);
}

template<>
const UserdataTable Matroska::SimpleTag::base::mod = {
    SimpleTag__call, /* call */
    NULL, /* __index */
    SimpleTag__submodules, /* init */
};

template<>
const UserdataMetatable Matroska::SimpleTag::base::metatable = {
    "TagLib::Matroska::SimpleTag", /* name */
    SimpleTag__index, /* indextable */
    NULL, /* indexfunc */
};

#define E(x) { #x, sizeof(#x) - 1, TagLib::Matroska::SimpleTag::ValueType::x }
static const Matroska::SimpleTag::ValueType::enum_type matroskaValueTypes[] = {
    E(StringType), E(BinaryType)
};

LTAGLIB_PUBLIC
int luaopen_TagLib_Matroska_SimpleTag_ValueType(lua_State* L) {
    return Matroska::SimpleTag::ValueType::open(L);
}

#undef E
#define E(x) { #x, sizeof(#x) - 1, TagLib::Matroska::SimpleTag::TargetTypeValue::x }
static const Matroska::SimpleTag::TargetTypeValue::enum_type matroskaTargetTypeValues[] = {
    E(None), E(Shot), E(Subtrack), E(Track),
    E(Part), E(Album), E(Edition), E(Collection)
};

LTAGLIB_PUBLIC
int luaopen_TagLib_Matroska_SimpleTag_TargetTypeValue(lua_State* L) {
    return Matroska::SimpleTag::TargetTypeValue::open(L);
}
#undef E

template<>
const Matroska::SimpleTag::ValueType::enum_type*
Matroska::SimpleTag::ValueType::m_values = matroskaValueTypes;

template<>
const size_t Matroska::SimpleTag::ValueType::m_len = sizeof(matroskaValueTypes) / sizeof(matroskaValueTypes[0]);

template<>
const Matroska::SimpleTag::TargetTypeValue::enum_type*
Matroska::SimpleTag::TargetTypeValue::m_values = matroskaTargetTypeValues;

template<>
const size_t Matroska::SimpleTag::TargetTypeValue::m_len = sizeof(matroskaTargetTypeValues) / sizeof(matroskaTargetTypeValues[0]);

#include "../shared/enum.tcc"
template class LuaTagLib::Enum<TagLib::Matroska::SimpleTag::ValueType>;
template class LuaTagLib::Enum<TagLib::Matroska::SimpleTag::TargetTypeValue>;

#include "../shared/userdata.tcc"
template class LuaTagLib::BaseUserdata<TagLib::Matroska::SimpleTag>;
