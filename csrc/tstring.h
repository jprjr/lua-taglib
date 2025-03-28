#ifndef LTAGLIB_STRING_INCLUDE_GUARD
#define LTAGLIB_STRING_INCLUDE_GUARD

#include "taglib.h"
#include "shared/enum.h"

#include <tstring.h>
#include <cstddef>
#include <string>

/* Since Lua strings don't have to be null-terminated,
 * readable/printable C strings in any particular encoding.
 * They're really just arrays of bytes with a size field.
 *
 * This isn't going to be set up like a user data, just
 * a simple class that converts TagLib::String into a Lua
 * string and back.
 *
 * We're just going to assume all Lua strings are UTF-8,
 * if it's $CURRENT_YEAR and your Lua environment expects
 * some other encoding, you could probably make your own
 * wrapper around the string module that uses iconv?
 */


extern "C" {

LTAGLIB_PUBLIC int
luaopen_TagLib_String(lua_State* L);

LTAGLIB_PUBLIC int
luaopen_TagLib_String_Type(lua_State* L);

}

namespace LuaTagLib {

    class LTAGLIB_PRIVATE String {
        public:
            typedef Enum<TagLib::String::Type> Type;

            typedef TagLib::String taglib_type;

            static void pushValue(lua_State* L, const TagLib::String& str);

            /* returns true if the value at index is a Lua string */
            static bool isValid(lua_State* L, int idx);

            static TagLib::String checkValue(lua_State* L, int idx);

            /* return the taglib null string if the index is not a string */
            static TagLib::String optValue(lua_State* L, int idx);

    };

    template<>
    const String::Type::enum_type* String::Type::m_values;
}

#endif
