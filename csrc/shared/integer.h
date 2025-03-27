#ifndef LTAGLIB_LUA_INTEGER_INCLUDE_GUARD
#define LTAGLIB_LUA_INTEGER_INCLUDE_GUARD

#include "lua.h"

/* so we can have a list of integers with tlist.h */

namespace LuaTagLib {
    class LTAGLIB_PRIVATE Integer {
        public:
            typedef lua_Integer taglib_type;
            static inline void pushValue(lua_State* L, lua_Integer i) {
                lua_pushinteger(L, i);
            }

            static inline lua_Integer checkValue(lua_State* L, int idx) {
                return luaL_checkinteger(L, idx);
            }
    };
}

#endif
