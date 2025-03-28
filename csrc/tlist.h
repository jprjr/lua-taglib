#ifndef LTAGLIB_TLIST_INCLUDE_GUARD
#define LTAGLIB_TLIST_INCLUDE_GUARD

#include "taglib.h"
#include <tlist.h>

namespace LuaTagLib {

    class LTAGLIB_PRIVATE ListCommon {
        protected:
            static int __ipairs(lua_State* L) {
                lua_pushvalue(L, lua_upvalueindex(1));
                lua_pushvalue(L, 1);
                lua_pushinteger(L, 0);
                return 3;

            }

            static int __next(lua_State* L) {
                lua_Integer i;

                if(!lua_isinteger(L, 2)) return 0;
                i = lua_tointeger(L, 2);
                lua_pushinteger(L, ++i);
                if(lua_geti(L, 1, i) == LUA_TNIL) {
                    lua_pop(L, 2);
                    return 0;
                }
                return 2;
            }
    };


    template<typename T>
    class LTAGLIB_PRIVATE ListBase: public ListCommon {
        public:
            typedef T taglib_type;
            typedef ListBase<T> base;
            static const char* __name;
    };

    template<typename T, typename Impl>
    class LTAGLIB_PRIVATE List: public ListBase<T> {
        public:
            static bool isValid(lua_State* L, int idx);

        protected:
            static T checkList(lua_State* L, int idx);
            static void pushList(lua_State* L, const T& list, int idx);
    };


    template<typename T, typename Impl>
    bool List<T, Impl>::isValid(lua_State* L, int idx) {
        int tidx = lua_gettop(L) + 1;
        lua_Integer i;
        bool valid = true;

        if(lua_type(L,idx) != LUA_TTABLE) return false;

        for(i=1; ;++i) {
            lua_geti(L, idx, i);
            if(lua_isnil(L, tidx)) break;
            if(!(Impl::Value::isValid(L, tidx))) {
                valid = false;
                break;
            }
            lua_pop(L, 1);
        }
        lua_pop(L, 1);
        return valid;
    };

    template<typename T, typename Impl>
    T List<T, Impl>::checkList(lua_State* L, int idx) {
        int tidx = lua_gettop(L) + 1;
        lua_Integer i;
#if LTAGLIB_ATLEAST(LTAGLIB_2_0)
        T list = {};
#else
        T list = T();
#endif

        luaL_checktype(L, idx, LUA_TTABLE);

        for(i=1; ;++i) {
            lua_geti(L, idx, i);
            if(lua_isnil(L, tidx)) break;
            list.append(Impl::Value::check(L, tidx));
            lua_pop(L, 1);
        }
        lua_pop(L, 1);
        return list;
    }

    template<typename T, typename Impl>
    void List<T, Impl>::pushList(lua_State* L, const T& list, int idx) {
        lua_Integer i = 0;

        lua_newtable(L);
#if LTAGLIB_ATLEAST(LTAGLIB_2_0)
        for(typename T::ConstIterator it = list.cbegin(); it != list.cend() ;
#else
        for(typename T::ConstIterator it = list.begin(); it != list.end() ;
#endif
            ++it) {

            Impl::Value::push(L, *it, idx);
            lua_rawseti(L, -2, ++i);
        }
    }

    template<typename T, typename LT>
    class LTAGLIB_PRIVATE ValueList: public List<T, ValueList<T, LT> > {
        public:
            class LTAGLIB_PRIVATE Value {
                public:
                    typedef typename LT::taglib_type taglib_type;

                    static void push(lua_State* L, const taglib_type& val, int parent) {
                        (void) parent;
                        LT::pushValue(L, val);
                    }

                    static taglib_type check(lua_State* L, int idx) {
                        return LT::checkValue(L, idx);
                    }

                    static bool isValid(lua_State* L, int idx) {
                        return LT::isValid(L, idx);
                    }
            };

            static void pushValue(lua_State* L, const T& list) {
                List<T, ValueList<T, LT> >::pushList(L, list, 0);
            }

            static T checkValue(lua_State* L, int idx) {
                return List<T, ValueList<T, LT> >::checkList(L, idx);
            }
    };

    template<typename T, typename LT>
    class LTAGLIB_PRIVATE PtrList: public List<T, PtrList<T, LT> > {
        public:
            class LTAGLIB_PRIVATE Value {
                public:
                    typedef typename LT::taglib_type taglib_type;

                    static void push(lua_State* L, taglib_type* val, int parent) {
                        LT::pushPtr(L, val, parent);
                    }

                    static taglib_type* check(lua_State* L, int idx) {
                        return LT::checkPtr(L, idx);
                    }

                    static bool isValid(lua_State* L, int idx) {
                        return LT::isValid(L, idx);
                    }
            };

            static void pushPtr(lua_State* L, const T& list, int parent) {
                List<T, PtrList<T, LT> >::pushList(L, list, parent);
            }

            static T checkPtr(lua_State* L, int idx) {
                return List<T, PtrList<T, LT> >::checkList(L, idx);
            }
    };


    template<typename T>
    class LTAGLIB_PRIVATE ConstListReference: public ListBase<T> {
        protected:
            LTAGLIB_CONSTEXPR ConstListReference(const T& list)
              : m_list(list) { }

            static void pushRef(lua_State* L, const T& list, int parent);
            static int getMetatable(lua_State* L);
            static const T& checkRef(lua_State* L, int idx);
        private:
            const T& m_list;

            static int __len(lua_State* L);
            static ConstListReference<T>* checkRefPtr(lua_State* L, int idx);
            static const void* getKey();
            static int __gc(lua_State* L);

    };

    template<typename T>
    const void* ConstListReference<T>::getKey() {
        static char key;
        return &key;
    }

    template<typename T>
    int ConstListReference<T>::__gc(lua_State* L) {
        ConstListReference<T>* p = checkRefPtr(L, 1);
        p->~ConstListReference<T>();
        return 0;
    }

    template<typename T>
    int ConstListReference<T>::getMetatable(lua_State* L) {
        int created = newmetatable(L, getKey());
        if(created) {
            lua_pushstring(L, ListBase<T>::__name);
            lua_setfield(L, -2, "__name");

            lua_pushcclosure(L, __gc, 0);
            lua_setfield(L, -2, "__gc");

            lua_pushcclosure(L, __len, 0);
            lua_setfield(L, -2, "__len");

            lua_pushcclosure(L, ListCommon::__next, 0);
            lua_pushcclosure(L, ListCommon::__ipairs, 1);
            lua_setfield(L, -2, "__ipairs");
            lua_getfield(L, -1, "__ipairs");
            lua_setfield(L, -2, "__pairs");
        }
        return created;
    }

    template<typename T>
    void ConstListReference<T>::pushRef(lua_State* L, const T& list, int parent) {
        new
          (newuserdata(L, sizeof(ConstListReference<T>)))
          ConstListReference<T>(list);
        addreference(L, -1, parent);
        /* we do NOT call and set the metatable yet, that's handled higher up */
    }

    template<typename T>
    ConstListReference<T>* ConstListReference<T>::checkRefPtr(lua_State* L, int idx) {
        void* p = testuserdata(L, idx, getKey());
        if(p == NULL) luaL_typeerror(L, idx, ListBase<T>::__name);
        return static_cast<ConstListReference<T>*>(p);
    }

    template<typename T>
    const T& ConstListReference<T>::checkRef(lua_State* L, int idx) {
        return checkRefPtr(L,idx)->m_list;
    }

    template<typename T>
    int ConstListReference<T>::__len(lua_State* L) {
        lua_pushinteger(L, checkRef(L,1).size());
        return 1;
    }

    template<typename T, typename Impl>
    class LTAGLIB_PRIVATE ConstImplListReference: public ConstListReference<T> {
        public:
            static int getMetatable(lua_State* L);
            static void pushRef(lua_State* L, const T& list, int parent);
            static int __index(lua_State* L);
    };

    template<typename T, typename Impl>
    int ConstImplListReference<T, Impl>::getMetatable(lua_State* L) {
        int created = ConstListReference<T>::getMetatable(L);
        if(created) {
            lua_pushcclosure(L, __index, 0);
            lua_setfield(L, -2, "__index");
        }

        return created;
    }

    template<typename T, typename Impl>
    void ConstImplListReference<T, Impl>::pushRef(lua_State *L, const T& list, int parent) {
        ConstListReference<T>::pushRef(L, list, parent);
        getMetatable(L);
        lua_setmetatable(L, -2);
    }


    template<typename T, typename Impl>
    int ConstImplListReference<T, Impl>::__index(lua_State* L) {
        lua_Integer i;
        const T& list = ConstListReference<T>::checkRef(L, 1);

        if(!lua_isinteger(L, 2)) {
            lua_pushvalue(L, lua_upvalueindex(1));
            lua_pushvalue(L, 2);
            lua_gettable(L, -2);
            return 1;
        }

        i = lua_tointeger(L,2) - 1;

        if(i < 0 || ((std::size_t)i) >= list.size()) return 0;
        Impl::Value::push(L, list[i], 1);
        return 1;
    }

    template<typename T, typename LT>
    class LTAGLIB_PRIVATE ConstValueListReference: public ConstImplListReference<T, ValueList<T, LT> > {
    };

    template<typename T, typename LT>
    class LTAGLIB_PRIVATE ConstPtrListReference: public ConstImplListReference<T, PtrList<T, LT> > {
    };


}

#endif
