#ifndef LTAGLIB_BYTEVECTOR_INCLUDE_GUARD
#define LTAGLIB_BYTEVECTOR_INCLUDE_GUARD

#include "shared/userdata.h"
#include <tbytevector.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_ByteVector(lua_State* L);

}

namespace LuaTagLib {

    template<> const UserdataMetatable UserdataCommon<TagLib::ByteVector>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::ByteVector>::mod;

    class LTAGLIB_PRIVATE ByteVector: public BaseUserdata<TagLib::ByteVector> {
        public:
            /* "loose" check, accepts either a ByteVector or lua string
             * at idx, throws an error if not one of the two */
            static TagLib::ByteVector looseValue(lua_State* L, int idx);

            /* "loose" isValid, returns true for either a ByteVector or lua string */
            static bool isValidish(lua_State* L, int idx);

            /* override the default checkValue to use looseValue */
            static TagLib::ByteVector checkValue(lua_State* L, int idx) {
                return looseValue(L, idx);
            }

            /* add a new strictValue for the few times we truly need a bytevector */
            static TagLib::ByteVector strictValue(lua_State* L, int idx) {
                return BaseUserdata<TagLib::ByteVector>::checkValue(L, idx);
            }

            /* override pushValue - it just pushes the bytevector as a raw lua string */
            static void pushValue(lua_State* L, const TagLib::ByteVector& bv) {
                lua_pushlstring(L, bv.data(), bv.size());
            }
    };
}

#endif
