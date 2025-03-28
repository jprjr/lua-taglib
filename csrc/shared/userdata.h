#ifndef LTAGLIB_USERDATA_TEMPLATE_INCLUDE_GUARD
#define LTAGLIB_USERDATA_TEMPLATE_INCLUDE_GUARD

#include "../taglib.h"
#include <cstddef>

namespace LuaTagLib {
    typedef struct {
        const char*        __name;
        const luaL_Reg*   __index;
        lua_CFunction        init; /* for 99% of cases an __index table is sufficient,
                                      for more advanced cases init will be called with
                                      the metatable as the first argument.
                                      It will be responsible for setting any additional
                                      metafields like __len, __newindex, and so on */
    } UserdataMetatable;

    typedef struct {
        lua_CFunction      __call;
        const luaL_Reg*   __index;
        lua_CFunction        init;
    } UserdataTable;

    class LTAGLIB_PRIVATE UserdataStatic {
        public:
            /* each class gets a table with a "getMetatable" method in Lua */
            static int getMetatableWrapper(lua_State* L);
            static int callWrapper(lua_State* L);
    };

    class LTAGLIB_PRIVATE UserdataInstance {
        public:
            bool isManaged() const;
            void unmanage();
            void manage();

        protected:
            LTAGLIB_CONSTEXPR UserdataInstance(void* const ptr = NULL, bool managed = false)
              : m_managed(managed), m_ptr(ptr) { }

            void* getPtr() const;

            /* we specifically want m_ptr last, this should ensure
             * alignment in the eventual UserdataValue sub-class */
            bool m_managed;
            void* m_ptr;
    };

    template<typename T>
    class LTAGLIB_PRIVATE UserdataPointer: public UserdataInstance {
        public:
            static int __gc(lua_State* L);
            T* getPtr() const;
            static T* push(lua_State* L, T* val, bool managed = false);

        protected:
            LTAGLIB_CONSTEXPR UserdataPointer(T* ptr, bool managed = false);
            ~UserdataPointer();
    };

    template<typename T>
    class LTAGLIB_PRIVATE UserdataCommon {
        public:
            typedef UserdataCommon<T> base;
            typedef T taglib_type;

            static UserdataPointer<T>* optInstance(lua_State* L, int idx);

            static T* optPtr(lua_State* L, int idx);

            static UserdataPointer<T>* checkInstance(lua_State* L, int idx);

            static T* checkPtr(lua_State* L, int idx);

            static T& checkValue(lua_State* L, int idx);

            static bool isValid(lua_State* L, int idx);
            static int open(lua_State* L);

        protected:
            static UserdataPointer<T>* UserdataTypeError(lua_State* L, int idx);
            static const void* getKey();
            static const UserdataMetatable metatable;
            static int getMetatable(lua_State* L);
        private:
            static const UserdataTable mod;
    };

    template<typename T, typename P>
    class LTAGLIB_PRIVATE Userdata: public UserdataCommon<T> {
        public:
            static int open(lua_State* L);
            static int getMetatable(lua_State* L);
            static int cast(lua_State* L);
            static T* castPtr(lua_State* L, int idx);
            static T* pushPtr(lua_State* L, T* val, int parent, bool managed = false);
            static T* pushPtr(lua_State* L, T* val);
    };

    template<typename T>
    class LTAGLIB_PRIVATE BaseUserdata: public Userdata<T, BaseUserdata<T> > {
        public:
            static void onMetatable(lua_State* L);
            static T* castPtrImpl(lua_State* L, int idx);
    };

    template<typename T, typename P>
    class LTAGLIB_PRIVATE DerivedUserdata: public Userdata<T, DerivedUserdata<T,P> > {
        public:
            static void onMetatable(lua_State* L);
            static T* castPtrImpl(lua_State* L, int idx);
    };

    class LTAGLIB_PRIVATE UserdataExtra {
        public:
            template<typename T>
            static typename T::taglib_type* pushValue(lua_State* L, const typename T::taglib_type& value) {
                return T::pushPtr(L, new typename T::taglib_type(value));
            }

    };
}

#endif
