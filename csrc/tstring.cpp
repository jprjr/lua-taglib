#include "tstring.h"

#include <string>

using namespace LuaTagLib;

namespace LuaTagLib {

void String::pushValue(lua_State* L, const TagLib::String& str) {
    std::string s = str.to8Bit(true);
    lua_pushlstring(L, s.data(), s.size());
}

bool String::isValid(lua_State* L, int idx) {
    return isstring(L, idx);
}

/* TODO is there a benefit to go to a ByteVector first?
 *
 * The idea is if I use an intermediate bytevector, I can
 * use checklstring to get the length and avoid a strlen-type
 * call, but I think that results in two copies of the data
 * being done - once into the bytevector, again into the string.
 *
 * The two things I try to avoid are calls to strlen, and copies,
 * and I'm forced to choose one here.
 */
TagLib::String String::checkValue(lua_State* L, int idx) {
    const char* str_data;
    std::size_t str_len;
    TagLib::String str;

    str_data = checklstring(L, idx, &str_len);
    str = TagLib::String(TagLib::ByteVector(str_data, str_len), TagLib::String::UTF8);
    lua_pop(L, 1);
    return str;
}

/* return the taglib null string if the index is not a string */
TagLib::String String::optValue(lua_State* L, int idx) {
    if(lua_isnoneornil(L, idx)) return TagLib::String();

    return checkValue(L, idx);
}

}

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
