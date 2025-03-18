#ifndef LTAGLIB_LUA_META_INCLUDE_GUARD
#define LTAGLIB_LUA_META_INCLUDE_GUARD

#include "compat.h"
#include <cstddef>

namespace LuaTagLib {
    LTAGLIB_PRIVATE
    const void* getIdKey();

    LTAGLIB_PRIVATE
    const void* getParentKey();

    LTAGLIB_PRIVATE
    int getsubtable(lua_State* L, int idx, const void* key);

    LTAGLIB_PRIVATE
    int newmetatable(lua_State* L, const void* key);

    /* convience function to ensure all userdata has a table
     * as a uservalue */
    LTAGLIB_PRIVATE
    void* newuserdata(lua_State* L, std::size_t size);

    LTAGLIB_PRIVATE
    bool hasmetatable(lua_State* L, lua_Integer idx, const void* key);

    LTAGLIB_PRIVATE
    void* testuserdata(lua_State* L, lua_Integer idx, const void* key);

    LTAGLIB_PRIVATE
    const void* getReferenceKey();

    /* gets a uservalues table of tracked references, leaves it
     * on top of the stack */
    LTAGLIB_PRIVATE
    void getreferencetable(lua_State* L, int idx);

    LTAGLIB_PRIVATE
    int addreference(lua_State* L, int idx, int ref);

    LTAGLIB_PRIVATE
    void addkeyreference(lua_State* L, int idx, const void* key);

    LTAGLIB_PRIVATE
    int getkeyreference(lua_State* L, int idx, const void* key);
}

#endif
