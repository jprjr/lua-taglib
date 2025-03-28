#ifndef LTAGLIB_MP4_ITEM_INCLUDE_GUARD
#define LTAGLIB_MP4_ITEM_INCLUDE_GUARD

#include "mp4.h"

#if LTAGLIB_HAS_MP4

#include "../shared/userdata.h"
#if LTAGLIB_ATLEAST(LTAGLIB_2_0)
#include "../shared/enum.h"
#endif
#include <mp4item.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_MP4_Item(lua_State* L);

#if LTAGLIB_ATLEAST(LTAGLIB_2_0)

LTAGLIB_PUBLIC
int luaopen_TagLib_MP4_Item_Type(lua_State* L);

#endif

}

namespace LuaTagLib {

    template<> const UserdataMetatable UserdataCommon<TagLib::MP4::Item>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::MP4::Item>::mod;

    namespace MP4 {
    class LTAGLIB_PRIVATE Item: public BaseUserdata<TagLib::MP4::Item> {
        public:
#if LTAGLIB_ATLEAST(LTAGLIB_2_0)
            typedef Enum<TagLib::MP4::Item::Type> Type;
#endif

    };
    }
}

#endif
#endif
