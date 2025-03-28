#ifndef LTAGLIB_APE_ITEM_INCLUDE_GUARD
#define LTAGLIB_APE_ITEM_INCLUDE_GUARD

#include "../taglib.h"

#define LTAGLIB_HAS_APE_ITEM (LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,3,0))

#if LTAGLIB_HAS_APE_ITEM

#include "../shared/userdata.h"
#include "../shared/enum.h"
#include <apeitem.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_APE_Item(lua_State *L);

LTAGLIB_PUBLIC
int luaopen_TagLib_APE_Item_ItemTypes(lua_State *L);

}

namespace LuaTagLib {

#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::APE::Item>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::APE::Item>::mod;
#endif 


    namespace APE {
        class LTAGLIB_PRIVATE Item : public BaseUserdata<TagLib::APE::Item> {
            public:
                typedef Enum<TagLib::APE::Item::ItemTypes> ItemTypes;
        };
    }
}

#endif

#endif

