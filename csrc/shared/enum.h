#ifndef LTAGLIB_ENUM_INCLUDE_GUARD
#define LTAGLIB_ENUM_INCLUDE_GUARD

#include "lua.h"

#include <cstddef>

namespace LuaTagLib {

    template<typename T>
    class LTAGLIB_PRIVATE Enum {
        public:
            typedef T taglib_type;
            typedef struct { const char* name; size_t name_len; T value; } enum_type;

            static int open(lua_State* L);

            static void pushValue(lua_State* L, T value);

            static bool isValid(lua_State* L, int idx);

            static T checkValue(lua_State* L, int idx);

        private:
            static const enum_type* m_values;
            static const size_t m_len;
    };
}

#endif
