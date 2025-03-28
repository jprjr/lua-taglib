#ifndef LTAGLIB_OGG_PAGE_INCLUDE_GUARD
#define LTAGLIB_OGG_PAGE_INCLUDE_GUARD

#include "../taglib.h"
#include "../shared/userdata.h"
#include "../shared/enum.h"
#include <oggpage.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_Ogg_Page(lua_State *L);

LTAGLIB_PUBLIC
int luaopen_TagLib_Ogg_Page_ContainsPacketFlags(lua_State *L);

LTAGLIB_PUBLIC
int luaopen_TagLib_Ogg_Page_PaginationStrategy(lua_State* L);

}

namespace LuaTagLib {

    template<> const UserdataMetatable UserdataCommon<TagLib::Ogg::Page>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::Ogg::Page>::mod;

    namespace Ogg {
    class LTAGLIB_PRIVATE Page: public BaseUserdata<TagLib::Ogg::Page> {
        public:
            typedef Enum<TagLib::Ogg::Page::ContainsPacketFlags> ContainsPacketFlags;
            typedef Enum<TagLib::Ogg::Page::PaginationStrategy> PaginationStrategy;
    };

}
}

#endif
