#ifndef LTAGLIB_USERDATA_TEMPLATE_IMPL_INCLUDE_GUARD
#define LTAGLIB_USERDATA_TEMPLATE_IMPL_INCLUDE_GUARD

#include "userdata.h"
#include <new>

namespace LuaTagLib {

    template<typename T>
    int UserdataPointer<T>::__gc(lua_State* L) {
        UserdataPointer* u = reinterpret_cast<UserdataPointer*>(
          lua_touserdata(L, 1));
        u->~UserdataPointer();
        return 0;
    }

    template<typename T>
    T* UserdataPointer<T>::getPtr() const {
        return static_cast<T*>(m_ptr);
    }

    template<typename T>
    T* UserdataPointer<T>::push(lua_State* L, T* val, bool managed) {
        return (new (newuserdata(L,sizeof(UserdataPointer)))
          UserdataPointer(val,managed))->getPtr();
    }

    template<typename T>
    LTAGLIB_CONSTEXPR UserdataPointer<T>::UserdataPointer(T* ptr, bool managed) :
      UserdataInstance(ptr, managed) {
    }

    template<typename T>
    UserdataPointer<T>::~UserdataPointer() {
        if(m_managed) delete getPtr();
    }

    template<typename T>
    const void* UserdataCommon<T>::getKey() {
        static char key;
        return &key;
    }

    template<typename T>
    UserdataPointer<T>* UserdataCommon<T>::optInstance(lua_State* L, int idx) {
        return static_cast<UserdataPointer<T>*>(testuserdata(L, idx, getKey()));
    }

    template<typename T>
    T* UserdataCommon<T>::optPtr(lua_State* L, int idx) {
        T* ptr = NULL;
        UserdataPointer<T>* p = optInstance(L, idx);
        if(p != NULL) ptr = p->getPtr();
        return ptr;
    }

    template<typename T>
    UserdataPointer<T>* UserdataCommon<T>::checkInstance(lua_State* L, int idx) {
        UserdataPointer<T>* p = optInstance(L, idx);
        if(p == NULL) return UserdataTypeError(L, idx);
        return p;
    }

    template<typename T>
    T* UserdataCommon<T>::checkPtr(lua_State* L, int idx) {
        return checkInstance(L,idx)->getPtr();
    }

    template<typename T>
    T& UserdataCommon<T>::checkValue(lua_State* L, int idx) {
        return *(checkPtr(L, idx));
    }

    template<typename T>
    bool UserdataCommon<T>::isValid(lua_State* L, int idx) {
        return optInstance(L, idx) != NULL;
    }

    template<typename T>
    int UserdataCommon<T>::open(lua_State* L) {
        lua_newtable(L);
        if(mod.__call != NULL) {
            lua_newtable(L);
            lua_pushcclosure(L, mod.__call, 0);
            lua_pushcclosure(L, UserdataStatic::callWrapper, 1);
            lua_setfield(L, -2, "__call");
            lua_setmetatable(L, -2);
        }
        if(mod.__index != NULL) luaL_setfuncs(L, mod.__index, 0);
        if(mod.init != NULL) {
            lua_pushcclosure(L, mod.init, 0);
            lua_pushvalue(L, -2);
            lua_call(L, 1, 0);
        }
        return 1;
    }

    template<typename T>
    UserdataPointer<T>* UserdataCommon<T>::UserdataTypeError(lua_State* L, int idx) {
        luaL_typeerror(L, idx, UserdataCommon<T>::metatable.__name);
        return NULL;
    }

    template<typename T>
    int UserdataCommon<T>::getMetatable(lua_State* L) {
        int created = newmetatable(L, getKey());

        if(created) {
            lua_pushcclosure(L, UserdataPointer<T>::__gc, 0);
            lua_setfield(L, -2, "__gc");

            if(UserdataCommon<T>::metatable.__name != NULL) {
                lua_pushstring(L, metatable.__name);
                lua_setfield(L, -2, "__name");
            }

            if(UserdataCommon<T>::metatable.__index != NULL) {
                lua_newtable(L);
                luaL_setfuncs(L, metatable.__index, 0);
                lua_setfield(L, -2, "__index");
            }

            if(UserdataCommon<T>::metatable.init != NULL) {
                lua_pushcclosure(L, metatable.init, 0);
                lua_pushvalue(L, -2);
                lua_call(L, 1, 0);
            }
        }
        return created;
    }

    template<typename T,typename P>
    T* Userdata<T,P>::pushPtr(lua_State* L, T* val, int parent, bool managed) {
        T* t = NULL;

        if(val == NULL) {
            lua_pushnil(L);
            return t;
        }

        t = UserdataPointer<T>::push(L,val,managed);
        getMetatable(L);
        lua_setmetatable(L, -2);
        /* it is possible for parent to be 0,
         * for things like static methods that
         * allocate a pointer we
         * need to delete */
        if(parent) {
            addreference(L, -1, parent);
        }

        return t;
    }

    template<typename T, typename P>
    T* Userdata<T,P>::pushPtr(lua_State* L, T* val) {
        return pushPtr(L, val, 0, true);
    }

    template<typename T, typename P>
    T* Userdata<T,P>::pushValue(lua_State* L, const T& val) {
        return pushPtr(L, new T(val));
    }


    template<typename T, typename P>
    T* Userdata<T,P>::castPtr(lua_State* L, int idx) {
        return P::castPtrImpl(L, idx);
    }

    template<typename T, typename P>
    int Userdata<T,P>::cast(lua_State* L) {
        pushPtr(L, castPtr(L, 1), 1);
        return 1;
    }

    template<typename T, typename P>
    int Userdata<T,P>::getMetatable(lua_State* L) {
        int created = UserdataCommon<T>::getMetatable(L);
        if(created) {
            P::onMetatable(L);
        }
        return created;
    }

    template<typename T, typename P>
    int Userdata<T,P>::open(lua_State* L) {
        UserdataCommon<T>::open(L);

        lua_pushlightuserdata(L, (void*) getMetatable);
        lua_pushcclosure(L, UserdataStatic::getMetatableWrapper, 1);
        lua_setfield(L, -2, "getMetatable");

        lua_pushcclosure(L, cast, 0);
        lua_setfield(L, -2, "cast");
        return 1;
    }

    template<typename T>
    void BaseUserdata<T>::onMetatable(lua_State* L) {
        (void)L;
    }

    template<typename T>
    T* BaseUserdata<T>::castPtrImpl(lua_State* L, int idx) {
        return Userdata<T, BaseUserdata<T> >::checkPtr(L, idx);
    }

    template<typename T, typename P>
    void DerivedUserdata<T,P>::onMetatable(lua_State* L) {
        int t;
        P::getMetatable(L);
        t = lua_getfield(L, -2, "__index");
        if(lua_getfield(L, -2, "__index") != LUA_TNIL) {
            if(t == LUA_TNIL) { /* stack is nil, __index */
                lua_newtable(L); /* nil, __index, newtable */
                lua_insert(L, -2); /* nil, newtable, __index */
            }
            lua_newtable(L); /* (maybenil), index, __index, newtable */
            lua_insert(L, -2); /* (maybenil), index, newtable, index */
            lua_setfield(L, -2, "__index"); /* (maybenil), index, newtable */
            lua_setmetatable(L, -2); /* (maybenil, index) */
            if(t == LUA_TNIL) {
                lua_setfield(L, -4, "__index");
            }
            lua_pop(L, 1);
        }
        else {
            lua_pop(L, 2);
        }
        lua_rawsetp(L, -2, getParentKey());
    }

    template<typename T, typename P>
    T* DerivedUserdata<T, P>::castPtrImpl(lua_State* L, int idx) {
        return dynamic_cast<T*>(P::castPtr(L, idx));
    }

}

#endif
