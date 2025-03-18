#include "meta.h"

namespace LuaTagLib {

    LTAGLIB_PRIVATE
    const void* getIdKey() {
        static char key;
        return &key;
    }

    LTAGLIB_PRIVATE
    const void* getParentKey() {
        static char key;
        return &key;
    }

    LTAGLIB_PRIVATE
    int getsubtable(lua_State* L, int idx, const void* key) {
        idx = lua_absindex(L, idx);
        if(lua_rawgetp(L, idx, key) == LUA_TTABLE) return 0;

        lua_pop(L, 1); /* pop the nil value */
        lua_newtable(L);
        lua_pushvalue(L, -1); /* push a copy of the table */
        lua_rawsetp(L, idx, key); /* set the table */

        return 1;
    }

    LTAGLIB_PRIVATE
    int newmetatable(lua_State* L, const void* key) {
        int created = getsubtable(L, LUA_REGISTRYINDEX, key);
        if(created) {
            lua_pushlightuserdata(L, (void*) key);
            lua_rawsetp(L,-2, getIdKey());
        }
        return created;
    }

    LTAGLIB_PRIVATE
    void* newuserdata(lua_State* L, std::size_t size) {
        void* p = lua_newuserdata(L, size);
        lua_newtable(L);
        lua_setuservalue(L, -2);
        return p;
    }

    LTAGLIB_PRIVATE
    bool hasmetatable(lua_State* L, lua_Integer idx, const void* key) {
        const void* idkey = getIdKey();
        const void* pkey = getParentKey();

        if(!lua_getmetatable(L, idx)) return false;

        if(lua_rawgetp(L, -1, idkey) == LUA_TNIL) {
            lua_pop(L, 2);
            return false;
        }

        /* stack is now:
         *   -2: the userdata's metatable
         *   -1: the metatable's ID value */

        for(;;) {
            if(lua_touserdata(L,-1) == key) {
                lua_pop(L, 2);
                return true;
            }
            lua_pop(L, 1);

            if(lua_rawgetp(L, -1, pkey) == LUA_TNIL) {
                lua_pop(L, 2);
                return false;
            }
            lua_remove(L, -2);

            if(lua_rawgetp(L, -1, idkey) == LUA_TNIL) {
                lua_pop(L, 2);
                return false;
            }
        }
        /* not reachable */
        return false;
    }

    LTAGLIB_PRIVATE
    void* testuserdata(lua_State* L, lua_Integer idx, const void* key) {
        if(hasmetatable(L, idx, key)) return lua_touserdata(L, idx);
        return NULL;
    }

    LTAGLIB_PRIVATE
    const void* getReferenceKey() {
        static char key;
        return &key;
    }

    LTAGLIB_PRIVATE
    void getreferencetable(lua_State* L, int idx) {
        lua_getuservalue(L, idx);
        if(lua_type(L, -1) != LUA_TTABLE) {
            lua_pop(L, 1);
            luaL_error(L, "error - trying to access reference on value without a uservalue");
            return;
        }
        getsubtable(L, -1, getReferenceKey());
        lua_remove(L, -2);
    }

    LTAGLIB_PRIVATE
    int addreference(lua_State* L, int idx, int ref) {
        int val;
        ref = lua_absindex(L, ref);
        getreferencetable(L, idx);
        lua_pushvalue(L, ref);
        val = luaL_ref(L, -2);
        lua_pop(L,1);
        return val;
    }

    LTAGLIB_PRIVATE
    void addkeyreference(lua_State* L, int idx, const void* key) {
        lua_getuservalue(L, idx);
        if(lua_type(L, -1) != LUA_TTABLE) {
            lua_pop(L, 1);
            luaL_error(L, "error - unable to get uservalue table");
            return;
        }
        lua_insert(L, -2);
        lua_rawsetp(L, -2, key);
        lua_pop(L, 1);
    }

    LTAGLIB_PRIVATE
    int getkeyreference(lua_State* L, int idx, const void* key) {
        int t;
        lua_getuservalue(L, idx);
        if(lua_type(L, -1) != LUA_TTABLE) {
            lua_pop(L, 1);
            return luaL_error(L, "error - unable to get uservalue table");
        }
        t = lua_rawgetp(L, -1, key);
        lua_remove(L, -2);
        return t;
    }

}
