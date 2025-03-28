#ifndef LTAGLIB_OGG_XIPHCOMMENT_INCLUDE_GUARD
#define LTAGLIB_OGG_XIPHCOMMENT_INCLUDE_GUARD

#include "../tag.h"
#include "../shared/userdata.h"

#include <xiphcomment.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_Ogg_XiphComment(lua_State *L);

}

namespace LuaTagLib {
    template<> const UserdataMetatable UserdataCommon<TagLib::Ogg::XiphComment>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::Ogg::XiphComment>::mod;
    namespace Ogg {
        typedef DerivedUserdata<TagLib::Ogg::XiphComment, LuaTagLib::Tag> XiphComment;
    }
}

#endif

