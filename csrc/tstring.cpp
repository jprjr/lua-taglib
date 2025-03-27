#include "tstring.h"

using namespace LuaTagLib;

#define E(x) { #x, sizeof(#x) - 1, TagLib::String::x }

static const String::Type::enum_type enumValues[] = {
    E(Latin1),
    E(UTF16),
    E(UTF16BE),
    E(UTF8),
#if LTAGLIB_ATLEAST(LTAGLIB_1_4)
    E(UTF16LE),
#endif
};

LTAGLIB_PUBLIC int
luaopen_TagLib_String_Type(lua_State* L) {
    return String::Type::open(L);
}

LTAGLIB_PUBLIC int
luaopen_TagLib_String(lua_State* L) {
    lua_newtable(L);

    luaL_requiref(L, "TagLib.String.Type", luaopen_TagLib_String_Type, 0);
    lua_setfield(L, -2, "Type");

    return 1;
}

template<>
const String::Type::enum_type* String::Type::m_values = enumValues;

template<>
const size_t String::Type::m_len = sizeof(enumValues) / sizeof(enumValues[0]);

#include "shared/enum.tcc"
template class LuaTagLib::Enum<TagLib::String::Type>;
