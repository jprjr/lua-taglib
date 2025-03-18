#include "userdata.h"

namespace LuaTagLib {

    int UserdataStatic::getMetatableWrapper(lua_State* L) {
        int (*getMeta)(lua_State* L) =
          reinterpret_cast<int(*)(lua_State*)>(
            lua_touserdata(L, lua_upvalueindex(1))
          );
        getMeta(L);
        return 1;
    }

    bool UserdataInstance::isManaged() const {
        return m_managed;
    }

    void UserdataInstance::unmanage() {
        m_managed = false;
    }

    void UserdataInstance::manage() {
        m_managed = true;
    }

    void* UserdataInstance::getPtr() const {
        return m_ptr;
    }

#if LUA_VERSION_NUM > 501
#if LUA_VERSION_NUM == 502
    static int callWrapperCont(lua_State* L) {
#else
    static int callWrapperCont(lua_State* L, int status, lua_KContext ctx) {
        (void)status;
        (void)ctx;
#endif
        return lua_gettop(L);
    }
#endif

    int UserdataStatic::callWrapper(lua_State* L) {
        int args = lua_gettop(L) - 1;
        lua_pushvalue(L, lua_upvalueindex(1));
        lua_replace(L, 1);

#if LUA_VERSION_NUM > 501
        lua_callk(L, args, LUA_MULTRET, 0, callWrapperCont);
        return callWrapperCont(L, LUA_OK, 0);
#else
        lua_call(L, args, LUA_MULTRET);
        return lua_gettop(L);
#endif
    }

}
