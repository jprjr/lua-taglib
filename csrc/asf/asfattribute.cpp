#include "asfattribute.h"

#if LTAGLIB_HAS_ASF

#include "../tstring.h"
#include "../tbytevector.h"
#include "asfpicture.h"

using namespace LuaTagLib;

static int Attribute__call(lua_State* L) {
    TagLib::ASF::Attribute* a = NULL;
    int args = lua_gettop(L);

    switch(args) {
        case 0: {
            a = new TagLib::ASF::Attribute();
            break;
        }
        case 1: {
            /* isValid for a bytevector only returns true for a true bytevalue */
            if(ByteVector::isValid(L, 1)) {
                a = new TagLib::ASF::Attribute(ByteVector::strictValue(L, 1));
                break;
            }

            if(String::isValid(L,1)) {
                a = new TagLib::ASF::Attribute(String::checkValue(L,1));
                break;
            }

            /* not sure how to distinguish
             * between ulonglong, short, etc, we'll default to
             * unsigned int */
            if(lua_isinteger(L, 1)) {
                a = new TagLib::ASF::Attribute( (unsigned int) lua_tointeger(L, 1));
                break;
            }
            if(lua_isboolean(L, 1)) {
                a = new TagLib::ASF::Attribute( (bool) lua_toboolean(L, 1));
                break;
            }
            if(ASF::Attribute::isValid(L, 1)) {
                a = new TagLib::ASF::Attribute(ASF::Attribute::checkValue(L, 1));
                break;
            }

            break;
        }

        /* this doesn't exactly follow my usual guidelines but this way,
         * a library user can pass a specific attributetype parameter */
        case 2: {
            switch(ASF::Attribute::AttributeTypes::checkValue(L, 2)) {
                case TagLib::ASF::Attribute::UnicodeType: {
                    a = new TagLib::ASF::Attribute(String::checkValue(L,1));
                    break;
                }
                case TagLib::ASF::Attribute::BytesType: {
                    a = new TagLib::ASF::Attribute(ByteVector::looseValue(L,1));
                    break;
                }
                case TagLib::ASF::Attribute::BoolType: {
                    a = new TagLib::ASF::Attribute((bool)lua_toboolean(L,1));
                    break;
                }
                case TagLib::ASF::Attribute::DWordType: {
                    a = new TagLib::ASF::Attribute((unsigned int)luaL_checkinteger(L,1));
                    break;
                }
                case TagLib::ASF::Attribute::QWordType: {
                    a = new TagLib::ASF::Attribute((unsigned long long)luaL_checkinteger(L,1));
                    break;
                }
                case TagLib::ASF::Attribute::WordType: {
                    a = new TagLib::ASF::Attribute((unsigned short)luaL_checkinteger(L,1));
                    break;
                }
                default: break;
            }
        }
        default: break;
    }

    if(a == NULL) return luaL_error(L, "invalid arguments");
    ASF::Attribute::pushPtr(L, a);
    return 1;
}

static int Attribute_type(lua_State* L) {
    TagLib::ASF::Attribute* a = ASF::Attribute::checkPtr(L, 1);
    ASF::Attribute::AttributeTypes::pushValue(L, a->type());
    return 1;
}

static int Attribute_toBool(lua_State* L) {
    TagLib::ASF::Attribute* a = ASF::Attribute::checkPtr(L, 1);
    lua_pushboolean(L, a->toBool());
    return 1;
}

static int Attribute_toUShort(lua_State* L) {
    TagLib::ASF::Attribute* a = ASF::Attribute::checkPtr(L, 1);
    lua_pushinteger(L, a->toUShort());
    return 1;
}

static int Attribute_toUInt(lua_State* L) {
    TagLib::ASF::Attribute* a = ASF::Attribute::checkPtr(L, 1);
    lua_pushinteger(L, a->toUInt());
    return 1;
}

static int Attribute_toULongLong(lua_State* L) {
    TagLib::ASF::Attribute* a = ASF::Attribute::checkPtr(L, 1);
    lua_pushinteger(L, a->toULongLong());
    return 1;
}

static int Attribute_toString(lua_State* L) {
    TagLib::ASF::Attribute* a = ASF::Attribute::checkPtr(L, 1);
    String::pushValue(L, a->toString());
    return 1;
}

static int Attribute_toByteVector(lua_State* L) {
    TagLib::ASF::Attribute* a = ASF::Attribute::checkPtr(L, 1);
    ByteVector::pushValue(L, a->toByteVector());
    return 1;
}

static int Attribute_language(lua_State* L) {
    TagLib::ASF::Attribute* a = ASF::Attribute::checkPtr(L, 1);
    lua_pushinteger(L, a->language());
    return 1;
}

static int Attribute_setLanguage(lua_State* L) {
    TagLib::ASF::Attribute* a = ASF::Attribute::checkPtr(L, 1);
    a->setLanguage(luaL_checkinteger(L, 2));

    lua_settop(L,1);
    return 1;
}

static int Attribute_stream(lua_State* L) {
    TagLib::ASF::Attribute* a = ASF::Attribute::checkPtr(L, 1);
    lua_pushinteger(L, a->stream());
    return 1;
}

static int Attribute_setStream(lua_State* L) {
    TagLib::ASF::Attribute* a = ASF::Attribute::checkPtr(L, 1);
    a->setStream(luaL_checkinteger(L, 2));

    lua_settop(L,1);
    return 1;
}

#if LTAGLIB_ATLEAST(LTAGLIB_1_7)
static int Attribute_dataSize(lua_State* L) {
    TagLib::ASF::Attribute* a = ASF::Attribute::checkPtr(L, 1);
    lua_pushinteger(L, a->dataSize());
    return 0;
}
#endif

#if LTAGLIB_HAS_ASF_PICTURE
static int Attribute_toPicture(lua_State* L) {
    TagLib::ASF::Attribute* a = ASF::Attribute::checkPtr(L, 1);
    ASF::Picture::pushValue(L, a->toPicture());
    return 1;
}
#endif

#if LTAGLIB_ATLEAST(LTAGLIB_1_11)
static int Attribute_swap(lua_State* L) {
    ASF::Attribute::checkPtr(L,1)->swap(ASF::Attribute::checkValue(L,2));
    lua_settop(L,1);
    return 1;
}
#endif

static const luaL_Reg Attribute__index[] = {
    { "type", Attribute_type },
    { "toBool", Attribute_toBool },
    { "toUShort", Attribute_toUShort },
    { "toUInt", Attribute_toUInt },
    { "toULongLong", Attribute_toULongLong },
    { "toString", Attribute_toString },
    { "toByteVector", Attribute_toByteVector },
    { "language", Attribute_language },
    { "setLanguage", Attribute_setLanguage },
    { "stream", Attribute_stream },
    { "setStream", Attribute_setStream },
#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,7,0)
    { "dataSize", Attribute_dataSize },
#endif
#if LTAGLIB_HAS_ASF_PICTURE
    { "toPicture", Attribute_toPicture },
#endif
#if LTAGLIB_ATLEAST(LTAGLIB_1_11)
    { "swap", Attribute_swap },
#endif
    { NULL, NULL }
};

static int Attribute__submodules(lua_State* L) {
    luaL_requiref(L, "TagLib.ASF.Attribute.AttributeTypes", luaopen_TagLib_ASF_Attribute_AttributeTypes, 0);
    lua_setfield(L, -2, "AttributeTypes");
    return 0;
}

static const UserdataTable mod = {
    Attribute__call,
    NULL,
    Attribute__submodules
};

LTAGLIB_PUBLIC int
luaopen_TagLib_ASF_Attribute(lua_State* L) {
    return ASF::Attribute::open(L);
}

#define E(x) { #x, sizeof(#x) - 1, TagLib::ASF::Attribute::x }
static const ASF::Attribute::AttributeTypes::enum_type asfAttributeTypes[] = {
    E(UnicodeType), E(BytesType), E(BoolType), E(DWordType),
    E(QWordType), E(WordType), E(GuidType)
};

LTAGLIB_PUBLIC int
luaopen_TagLib_ASF_Attribute_AttributeTypes(lua_State* L) {
    return ASF::Attribute::AttributeTypes::open(L);
}

template<>
const ASF::Attribute::AttributeTypes::enum_type*
ASF::Attribute::AttributeTypes::m_values = asfAttributeTypes;

template<>
const size_t ASF::Attribute::AttributeTypes::m_len = sizeof(asfAttributeTypes) / sizeof(asfAttributeTypes[0]);

template<>
const UserdataTable ASF::Attribute::base::mod = {
    Attribute__call,
    NULL,
    Attribute__submodules,
};

template<>
const UserdataMetatable ASF::Attribute::base::metatable = {
    "TagLib::ASF::Attribute", /* name */
    Attribute__index, /* indextable */
    NULL, /* indexfunc */
};

#include "../shared/enum.tcc"
template class Enum<TagLib::ASF::Attribute::AttributeTypes>;

#include "../shared/userdata.tcc"
template class BaseUserdata<TagLib::ASF::Attribute>;

#endif
