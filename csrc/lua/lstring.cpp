#include "lstring.h"

namespace LuaTagLib {

LTAGLIB_PRIVATE
int isstring(lua_State* L, int idx) {
    if(luaL_getmetafield(L, idx, "__tostring") != LUA_TNIL) {
        lua_pop(L, 1);
        return 1;
    }

    switch(lua_type(L, idx)) {
        case LUA_TSTRING: /* fall-through */
        case LUA_TNUMBER: {
            return 1;
        }
        default: break;
    }

    return 0;
}

LTAGLIB_PRIVATE
const char* tolstring(lua_State* L, int idx, size_t* len) {
    if(luaL_callmeta(L, idx, "__tostring")) {
        if(lua_type(L, -1) != LUA_TSTRING) {
            if(len != NULL) *len = 0;
            return NULL;
        }
        return lua_tolstring(L, -1, len);
    }

    lua_pushvalue(L, idx);
    switch(lua_type(L, -1)) {
        case LUA_TSTRING: /* fall-through */
        case LUA_TNUMBER: {
            return lua_tolstring(L, -1, len);
        }
        default: break;
    }

    if(len != NULL) *len = 0;
    return NULL;
}

LTAGLIB_PRIVATE
const char* tostring(lua_State* L, int idx) {
    return tolstring(L, idx, NULL);
}

LTAGLIB_PRIVATE
const char* checklstring(lua_State* L, int idx, size_t* len) {
    const char* str = tolstring(L, idx, len);
    if(str == NULL) luaL_typeerror(L, idx, "string");
    return str;
}

LTAGLIB_PRIVATE
const char* checkstring(lua_State* L, int idx) {
    return checklstring(L, idx, NULL);
}

}
