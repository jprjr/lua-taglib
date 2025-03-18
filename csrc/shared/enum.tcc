#ifndef LTAGLIB_ENUM_IMPL_INCLUDE_GUARD
#define LTAGLIB_ENUM_IMPL_INCLUDE_GUARD

#include "enum.h"
#include <cstring>

namespace LuaTagLib {

    template<typename T>
    int Enum<T>::open(lua_State* L) {
        lua_newtable(L);
        for(size_t i = 0; i < m_len; ++i) {
            lua_pushlstring(L, m_values[i].name, m_values[i].name_len);
            lua_pushlstring(L, m_values[i].name, m_values[i].name_len);
            lua_settable(L, -3);
        }
        return 1;
    }

    template<typename T>
    void Enum<T>::pushValue(lua_State* L, T value) {
        size_t i;
        for(i = 0; i < m_len; ++i) {
            if(m_values[i].value == value) {
                lua_pushlstring(L, m_values[i].name, m_values[i].name_len);
                break;
            }
        }
        if(i == m_len) luaL_error(L,"invalid value");
    }

    template<typename T>
    bool Enum<T>::isValid(lua_State* L, int idx) {
        size_t i;
        bool found = false;
        size_t str_len;
        const char* str_data = checklstring(L, idx, &str_len);
        for(i = 0; i < m_len; ++i) {
            if(m_values[i].name_len == m_len && 
               memcmp(m_values[i].name,str_data,str_len) == 0) {
                found = true;
                break;
            }
        }
        lua_pop(L,1);
        return found;
    }

    template<typename T>
    T Enum<T>::checkValue(lua_State* L, int idx) {
        size_t i;
        size_t str_len;
        T val = (T)-1;
        const char* str_data = checklstring(L, idx, &str_len);
        for(i = 0; i < m_len; ++i) {
            if(m_values[i].name_len == str_len &&
               memcmp(m_values[i].name,str_data,str_len) == 0) {
                val = m_values[i].value;
                break;
            }
        }
        lua_pop(L,1);
        if(i == m_len) luaL_error(L, "invalid value");
        return val;
    }

}

#endif
