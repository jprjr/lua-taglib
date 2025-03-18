#ifndef LTAGLIB_BYTEVECTORLIST_INCLUDE_GUARD
#define LTAGLIB_BYTEVECTORLIST_INCLUDE_GUARD

#include "taglib.h"
#include "tlist.h"
#include "tbytevector.h"

#include <tbytevectorlist.h>

namespace LuaTagLib {
    class LTAGLIB_PRIVATE ByteVectorList: public ValueList<TagLib::ByteVectorList,ByteVector>  {
        public:
            static bool isValidish(lua_State* L, int idx) {
                int tidx = lua_gettop(L) + 1;
                unsigned int i;
                bool valid = true;

                if(lua_type(L,idx) != LUA_TTABLE) return false;

                for(i=1; ;++i) {
                    lua_rawgeti(L, idx, i);
                    if(lua_isnil(L, tidx)) break;
                    if(!(ByteVector::isValidish(L, tidx))) {
                        valid = false;
                        break;
                    }
                    lua_pop(L, 1);
                }
                lua_pop(L, 1);
                return valid;
            }

            static TagLib::ByteVectorList looseValue(lua_State* L, int idx) {
                int tidx = lua_gettop(L) + 1;
                unsigned int i;
                TagLib::ByteVectorList list = TagLib::ByteVectorList();

                luaL_checktype(L, idx, LUA_TTABLE);

                for(i=1; ;++i) {
                    lua_rawgeti(L, idx, i);
                    if(lua_isnil(L, tidx)) break;
                    list.append(ByteVector::looseValue(L, tidx));
                    lua_pop(L, 1);
                }
                lua_pop(L, 1);
                return list;
            }

            static TagLib::ByteVectorList checkValue(lua_State* L, int idx) {
                return looseValue(L, idx);
            }

            static TagLib::ByteVectorList strictValue(lua_State* L, int idx) {
                int tidx = lua_gettop(L) + 1;
                unsigned int i;
                TagLib::ByteVectorList list = TagLib::ByteVectorList();

                luaL_checktype(L, idx, LUA_TTABLE);

                for(i=1; ;++i) {
                    lua_rawgeti(L, idx, i);
                    if(lua_isnil(L, tidx)) break;
                    list.append(ByteVector::strictValue(L, tidx));
                    lua_pop(L, 1);
                }
                lua_pop(L, 1);
                return list;
            }

    };
}

#endif

