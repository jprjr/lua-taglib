#include "tvariant.h"

#if LTAGLIB_HAS_VARIANT

#include "tbytevector.h"
#include "tbytevectorlist.h"
#include "tstring.h"
#include "tstringlist.h"

using namespace LuaTagLib;

TagLib::Variant Variant::checkValue(lua_State* L, int idx) {
    TagLib::Variant v;
    TagLib::Variant::Type t;

    lua_getfield(L, idx, "type");
    t = Variant::Type::checkValue(L, -1);
    lua_pop(L,1);

    lua_getfield(L, idx, "value");

    switch(t) {
        case TagLib::Variant::Type::Void: {
            v = TagLib::Variant();
            break;
        }
        case TagLib::Variant::Type::Bool: {
            v = TagLib::Variant( (bool) lua_toboolean(L, lua_gettop(L)));
            break;
        }
        case TagLib::Variant::Type::Int: {
            v = TagLib::Variant( (int) luaL_checkinteger(L, lua_gettop(L)) );
            break;
        }
        case TagLib::Variant::Type::UInt: {
            v = TagLib::Variant( (unsigned int) luaL_checkinteger(L, lua_gettop(L)) );
            break;
        }
        case TagLib::Variant::Type::LongLong: {
            v = TagLib::Variant( (long long) luaL_checkinteger(L, lua_gettop(L)) );
            break;
        }
        case TagLib::Variant::Type::ULongLong: {
            v = TagLib::Variant( (unsigned long long) luaL_checkinteger(L, lua_gettop(L)) );
            break;
        }
        case TagLib::Variant::Type::Double: {
            v = TagLib::Variant( (double) luaL_checknumber(L, lua_gettop(L)) );
            break;
        }
        case TagLib::Variant::Type::String: {
            v = TagLib::Variant( String::checkValue(L, lua_gettop(L)) );
            break;
        }
        case TagLib::Variant::Type::StringList: {
            v = TagLib::Variant( StringList::checkValue(L, lua_gettop(L)) );
            break;
        }
        case TagLib::Variant::Type::ByteVector: {
            v = TagLib::Variant( ByteVector::looseValue(L, lua_gettop(L)) );
            break;
        }
        case TagLib::Variant::Type::ByteVectorList: {
            v = TagLib::Variant( ByteVectorList::looseValue(L, lua_gettop(L)) );
            break;
        }
        case TagLib::Variant::Type::VariantList: {
            v = TagLib::Variant( VariantList::checkValue(L, lua_gettop(L)) );
            break;
        }
        case TagLib::Variant::Type::VariantMap: {
            v = TagLib::Variant( VariantMap::checkValue(L, lua_gettop(L)) );
            break;
        }
    }
    lua_pop(L, 1);

    return v;
}

void Variant::pushValue(lua_State* L, const TagLib::Variant& v) {
    lua_newtable(L);
    Variant::Type::pushValue(L, v.type());
    lua_setfield(L, -2, "type");

    switch(v.type()) {
        case TagLib::Variant::Type::Void: {
            lua_pushnil(L);
            break;
        }
        case TagLib::Variant::Type::Bool: {
            lua_pushboolean(L, v.toBool());
            break;
        }
        case TagLib::Variant::Type::Int: {
            lua_pushinteger(L, v.toInt());
            break;
        }
        case TagLib::Variant::Type::UInt: {
            lua_pushinteger(L, v.toUInt());
            break;
        }
        case TagLib::Variant::Type::LongLong: {
            lua_pushinteger(L, v.toLongLong());
            break;
        }
        case TagLib::Variant::Type::ULongLong: {
            lua_pushinteger(L, v.toULongLong());
            break;
        }
        case TagLib::Variant::Type::Double: {
            lua_pushnumber(L, v.toDouble());
            break;
        }
        case TagLib::Variant::Type::String: {
            String::pushValue(L, v.toString());
            break;
        }
        case TagLib::Variant::Type::StringList: {
            StringList::pushValue(L, v.toStringList());
            break;
        }
        case TagLib::Variant::Type::ByteVector: {
            ByteVector::pushValue(L, v.toByteVector());
            break;
        }
        case TagLib::Variant::Type::ByteVectorList: {
            ByteVectorList::pushValue(L, v.toByteVectorList());
            break;
        }
        case TagLib::Variant::Type::VariantList: {
            VariantList::pushValue(L, v.toList());
            break;
        }
        case TagLib::Variant::Type::VariantMap: {
            VariantMap::pushValue(L, v.toMap());
            break;
        }
    }
    lua_setfield(L, -2, "value");
    return;
}

LTAGLIB_PUBLIC
int luaopen_TagLib_Variant_Type(lua_State* L) {
    return Variant::Type::open(L);
}

LTAGLIB_PUBLIC
int luaopen_TagLib_Variant(lua_State* L) {
    lua_newtable(L);

    luaL_requiref(L, "TagLib.Variant.Type", luaopen_TagLib_Variant_Type, 0);
    lua_setfield(L, -2, "Type");
    return 1;
}


#define E(x) { #x, sizeof(#x) - 1, TagLib::Variant::x }

static const Variant::Type::enum_type variantType[] = {
    E(Void), E(Bool), E(Int), E(UInt),
    E(LongLong), E(ULongLong), E(Double),
    E(String), E(StringList), E(ByteVector), E(ByteVectorList),
    E(VariantList), E(VariantMap)
};

template<>
const Variant::Type::enum_type* Variant::Type::m_values = variantType;

template<>
const size_t Variant::Type::m_len = sizeof(variantType) / sizeof(variantType[0]);

template<>
const char* VariantList::base::__name = "TagLib::VariantList";

template<>
const char* VariantMap::base::__name = "TagLib::VariantMap";

template<>
const char* VariantMapList::base::__name = "TagLib::List<TagLib::VariantMap>";

#include "shared/enum.tcc"
template class Enum<TagLib::Variant::Type>;

#endif
