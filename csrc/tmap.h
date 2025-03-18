#ifndef LTAGLIB_TMAP_INCLUDE_GUARD
#define LTAGLIB_TMAP_INCLUDE_GUARD

#include "taglib.h"

/* T = TagLib list type, LT = LuaTag item type */
namespace LuaTagLib {

    class LTAGLIB_PRIVATE MapCommon {
        protected:
            static int __pairs(lua_State* L) {
                lua_pushvalue(L, lua_upvalueindex(1));
                lua_pushvalue(L, 1);
                lua_pushnil(L);
                return 3;
            }
    };

    template<typename T>
    class LTAGLIB_PRIVATE MapBase: public MapCommon {
        public:
            typedef T taglib_type;
            typedef MapBase<T> base;
            static const char* __name;
    };

    template<typename T, typename Impl>
    class LTAGLIB_PRIVATE Map: public MapBase<T> {
        protected:
            static bool isValid(lua_State* L, int idx);
            static T checkMap(lua_State* L, int idx);
            static void pushMap(lua_State* L, const T& map, int idx);
    };

    template<typename T, typename Impl>
    bool Map<T, Impl>::isValid(lua_State* L, int idx) {
        if(lua_type(L, idx) != LUA_TTABLE) return false;

        lua_pushnil(L);
        while(lua_next(L, idx)) {
            if(!Impl::Key::isValid(L, -2)) return false;
            if(!Impl::Value::isValid(L, -1)) return false;
            lua_pop(L, 1);
        }
        return true;
    }

    template<typename T, typename Impl>
    T Map<T, Impl>::checkMap(lua_State* L, int idx) {
        T map = T();

        lua_pushnil(L);
        while(lua_next(L, idx)) {
            map.insert(Impl::Key::checkValue(L, -2), Impl::Value::check(L, -1));
            lua_pop(L, 1);
        }
        return map;
    }

    template<typename T, typename Impl>
    void Map<T, Impl>::pushMap(lua_State* L, const T& map, int idx) {
        lua_newtable(L);
#if LTAGLIB_ATLEAST(LTAGLIB_2_0)
        for(typename T::ConstIterator it = map.cbegin(); it != map.cend(); ++it)
#else
        for(typename T::ConstIterator it = map.begin(); it != map.end(); ++it)
#endif
        {
            Impl::Key::pushValue(L, it->first);
            Impl::Value::push(L, it->second, idx);
            lua_settable(L, -3);
        }
    }

    template<typename T, typename KEY, typename VALUE>
    class LTAGLIB_PRIVATE ValueMap: public Map<T, ValueMap<T, KEY, VALUE> > {
        public:
            typedef KEY Key;
            class LTAGLIB_PRIVATE Value {
                public:
                    typedef typename VALUE::taglib_type taglib_type;
                    static void push(lua_State* L, const taglib_type& val, int parent) {
                        (void) parent;
                        VALUE::pushValue(L, val);
                    }
                    static taglib_type check(lua_State* L, int idx) {
                        return VALUE::checkValue(L, idx);
                    }
                    static bool isValid(lua_State* L, int idx) {
                        return VALUE::isValid(L, idx);
                    }
            };

            static void pushValue(lua_State* L, const T& map) {
                Map<T, ValueMap<T, KEY, VALUE> >::pushMap(L, map, 0);
            }

            static T checkValue(lua_State* L, int idx) {
                return Map<T, ValueMap<T, KEY, VALUE> >::checkMap(L, idx);
            }
    };

    template<typename T, typename KEY, typename VALUE>
    class LTAGLIB_PRIVATE PtrMap: public Map<T, PtrMap<T, KEY, VALUE> > {
        public:
            typedef KEY Key;
            class LTAGLIB_PRIVATE Value {
                public:
                    typedef typename VALUE::taglib_type taglib_type;
                    static void push(lua_State* L, const taglib_type* ptr, int parent) {
                        VALUE::pushPtr(L, ptr, parent);
                    }
                    static taglib_type* check(lua_State* L, int idx) {
                        return VALUE::checkPtr(L, idx);
                    }
                    static bool isValid(lua_State* L, int idx) {
                        return VALUE::isValid(L, idx);
                    }
            };

            static void pushPtr(lua_State* L, const T& map) {
                Map<T, PtrMap<T, KEY, VALUE> >::pushMap(L, map, 0);
            }

            static T checkPtr(lua_State* L, int idx) {
                return Map<T, PtrMap<T, KEY, VALUE> >::checkMap(L, idx);
            }
    };

    template<typename T>
    class LTAGLIB_PRIVATE ConstMapReference: public MapBase<T> {
        protected:
            LTAGLIB_CONSTEXPR ConstMapReference(const T& map)
                : m_map(map) { }

            static void pushRef(lua_State* L, const T& list, int parent);
            static int getMetatable(lua_State* L);
            static const T& checkRef(lua_State* L, int idx);

        private:
            const T& m_map;

            static ConstMapReference<T>* checkRefPtr(lua_State* L, int idx);
            static const void* getKey();
            static int __gc(lua_State* L);
    };

    template<typename T>
    const void* ConstMapReference<T>::getKey() {
        static char key;
        return &key;
    }

    template<typename T>
    int ConstMapReference<T>::getMetatable(lua_State* L) {
        int created = newmetatable(L, getKey());
        if(created) {
            lua_pushstring(L, MapBase<T>::__name);
            lua_setfield(L, -2, "__name");

            lua_pushcclosure(L, __gc, 0);
            lua_setfield(L, -2, "__gc");
        }
        return created;
    }

    template<typename T>
    void ConstMapReference<T>::pushRef(lua_State* L, const T& map, int parent) {
        new
            (newuserdata(L, sizeof(ConstMapReference<T>)))
            ConstMapReference<T>(map);
        addreference(L, -1, parent);
    }

    template<typename T>
    ConstMapReference<T>* ConstMapReference<T>::checkRefPtr(lua_State* L, int idx) {
        void* p = testuserdata(L, idx, getKey());
        if(p == NULL) luaL_typeerror(L, idx, MapBase<T>::__name);
        return static_cast<ConstMapReference<T>*>(p);
    }

    template<typename T>
    const T& ConstMapReference<T>::checkRef(lua_State* L, int idx) {
        return checkRefPtr(L,idx)->m_map;
    }

    template<typename T>
    int ConstMapReference<T>::__gc(lua_State* L) {
        ConstMapReference<T>* p = checkRefPtr(L, 1);
        p->~ConstMapReference<T>();
        return 0;
    }

    template<typename T, typename Impl>
    class LTAGLIB_PRIVATE ConstImplMapReference: public ConstMapReference<T> {
        public:
            static int getMetatable(lua_State* L);
            static void pushRef(lua_State* L, const T& map, int parent);
        private:
            static int __next(lua_State* L);
            static int __index(lua_State* L);
    };

    template<typename T, typename Impl>
    int ConstImplMapReference<T, Impl>::getMetatable(lua_State* L) {
        int created = ConstMapReference<T>::getMetatable(L);
        if(created) {
            /* we don't really re-use anything from the base class */
            lua_pushcclosure(L, __next, 0);
            lua_pushcclosure(L, MapCommon::__pairs, 1);
            lua_setfield(L, -2, "__pairs");

            lua_pushcclosure(L, __index, 0);
            lua_setfield(L, -2, "__index");
        }
        return created;
    }

    template<typename T, typename Impl>
    void ConstImplMapReference<T, Impl>::pushRef(lua_State* L, const T& map, int parent) {
        ConstMapReference<T>::pushRef(L, map, parent);
        getMetatable(L);
        lua_setmetatable(L, -2);
    }

    template<typename T, typename Impl>
    int ConstImplMapReference<T, Impl>::__index(lua_State* L) {
        const T& map = ConstMapReference<T>::checkRef(L, 1);
#if LTAGLIB_ATLEAST(LTAGLIB_1_2)
        typename T::ConstIterator it = map.find(Impl::Key::checkValue(L, 2));
#else
        typename T::ConstIterator it = map.begin();
        typename Impl::Key::taglib_type key = Impl::Key::checkValue(L, 2);
        while( (!(it->first == key)) && it != map.end()) ++it;
#endif

#if LTAGLIB_ATLEAST(LTAGLIB_2_0)
        if(it == map.cend())
#else
        if(it == map.end())
#endif
        {
            return 0;
        }

        Impl::Value::push(L, it->second, 1);
        return 1;
    }

    template<typename T, typename Impl>
    int ConstImplMapReference<T, Impl>::__next(lua_State* L) {
        const T& map = ConstMapReference<T>::checkRef(L, 1);
        typename T::ConstIterator it;

        lua_settop(L, 2);
        if(lua_isnil(L, 2)) {
#if LTAGLIB_ATLEAST(LTAGLIB_2_0)
            it = map.cbegin();
#else
            it = map.begin();
#endif
        } else {
            typename Impl::Key::taglib_type key = Impl::Key::checkValue(L, 2);

#if LTAGLIB_ATLEAST(LTAGLIB_1_2)
            it = map.find(key);
#else
            /* go directly to the end to trigger the manual search */
            it = map.end();
#endif
#if LTAGLIB_ATLEAST(LTAGLIB_2_0)
            if(it == map.cend())
#else
            if(it == map.end())
#endif
            {
                /* this is the worst-case scenario, it means a key was removed
                 * while traversing the table so we'll do a search from the beginning */
#if LTAGLIB_ATLEAST(LTAGLIB_2_0)
                it = map.cbegin();
                while(it->first < key && !(it->first == key) && it != map.cend()) ++it;
#else
                it = map.begin();
                while(it->first < key && !(it->first == key) && it != map.end()) ++it;
#endif
            } else {
                ++it;
            }
        }

#if LTAGLIB_ATLEAST(LTAGLIB_2_0)
        if(it == map.cend())
#else
        if(it == map.end())
#endif
        {
            return 0;
        }
        Impl::Key::pushValue(L, it->first);
        Impl::Value::push(L, it->second, 1);
        return 2;
    }

    template<typename T, typename KEY, typename VALUE>
    class LTAGLIB_PRIVATE ConstValueMapReference: public ConstImplMapReference<T, ValueMap<T, KEY, VALUE> > { };

    template<typename T, typename KEY, typename VALUE>
    class LTAGLIB_PRIVATE ConstPtrMapReference: public ConstImplMapReference<T, PtrMap<T, KEY, VALUE> > { };

    template<typename T>
    class LTAGLIB_PRIVATE MapReference: public ConstMapReference<T> {
        protected:
            LTAGLIB_CONSTEXPR MapReference(T& map)
                : ConstMapReference<T>(map), m_map(map) { }

            static void pushRef(lua_State* L, T& list, int parent);
            static int getMetatable(lua_State* L);
            static T& checkRef(lua_State* L, int idx);

        private:
            T& m_map;
            static MapReference<T>* checkRefPtr(lua_State* L, int idx);
            static const void* getKey();
            static int __gc(lua_State* L);
    };

    template<typename T>
    const void* MapReference<T>::getKey() {
        static char key;
        return &key;
    }

    template<typename T>
    void MapReference<T>::pushRef(lua_State* L, T& map, int parent) {
        new
            (newuserdata(L, sizeof(MapReference<T>)))
            MapReference<T>(map);
        addreference(L, -1, parent);
    }

    template<typename T>
    MapReference<T>* MapReference<T>::checkRefPtr(lua_State* L, int idx) {
        void* p = testuserdata(L, idx, getKey());
        if(p == NULL) luaL_typeerror(L, idx, MapBase<T>::__name);
        return static_cast<MapReference<T>*>(p);
    }

    template<typename T>
    T& MapReference<T>::checkRef(lua_State* L, int idx) {
        return checkRefPtr(L,idx)->m_map;
    }

    template<typename T>
    int MapReference<T>::__gc(lua_State* L) {
        MapReference<T>* p = checkRefPtr(L, 1);
        p->~MapReference<T>();
        return 0;
    }

    template<typename T>
    int MapReference<T>::getMetatable(lua_State* L) {
        int created = newmetatable(L, getKey());
        if(created) {
            lua_pushstring(L, MapBase<T>::__name);
            lua_setfield(L, -2, "__name");

            lua_pushcclosure(L, __gc, 0);
            lua_setfield(L, -2, "__gc");
        }
        return created;
    }

    template<typename T, typename Impl>
    class LTAGLIB_PRIVATE ImplMapReference: public MapReference<T> {
        public:
            static int getMetatable(lua_State* L);
            static void pushRef(lua_State* L, T& map, int parent);
        private:
            static int __newindex(lua_State* L);
    };

    template<typename T, typename Impl>
    int ImplMapReference<T, Impl>::getMetatable(lua_State* L) {
        int created = MapReference<T>::getMetatable(L);
        if(created) {
            lua_pushcclosure(L, __newindex, 0);
            lua_setfield(L, -2, "__newindex");

            /* copy __index and __pairs from the const implementation */
            ConstImplMapReference<T, Impl>::getMetatable(L);
            lua_getfield(L, -1, "__index");
            lua_setfield(L, -3, "__index");
            lua_getfield(L, -1, "__pairs");
            lua_setfield(L, -3, "__pairs");

            /* mark the const class as being our parent */
            lua_rawsetp(L, -2, getParentKey());
        }
        return created;
    }

    template<typename T, typename Impl>
    void ImplMapReference<T, Impl>::pushRef(lua_State* L, T& map, int parent) {
        MapReference<T>::pushRef(L, map, parent);
        getMetatable(L);
        lua_setmetatable(L, -2);
    }

    template<typename T, typename Impl>
    int ImplMapReference<T, Impl>::__newindex(lua_State* L) {
        T& map = MapReference<T>::checkRef(L, 1);
        typename Impl::Key::taglib_type key = Impl::Key::checkValue(L, 2);

        if(lua_isnoneornil(L,3)) {
            map.erase(key);
        } else {
            map.insert(key, Impl::Value::check(L, 3));
        }
        return 0;
    }

    template<typename T, typename KEY, typename VALUE>
    class LTAGLIB_PRIVATE ValueMapReference: public ImplMapReference<T, ValueMap<T, KEY, VALUE> > { };

    template<typename T, typename KEY, typename VALUE>
    class LTAGLIB_PRIVATE PtrMapReference: public ImplMapReference<T, PtrMap<T, KEY, VALUE> > { };

}



#endif

