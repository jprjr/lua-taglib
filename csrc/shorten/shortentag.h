#ifndef LTAGLIB_SHORTEN_TAG_INCLUDE_GUARD
#define LTAGLIB_SHORTEN_TAG_INCLUDE_GUARD

#include "shorten.h"

#include "../shared/userdata.h"
#include "../tag.h"
#include <shortentag.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_Shorten_Tag(lua_State *L);

}
namespace LuaTagLib {

#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::Shorten::Tag>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::Shorten::Tag>::mod;
#endif 


    namespace Shorten {
        typedef DerivedUserdata<TagLib::Shorten::Tag, LuaTagLib::Tag> Tag;
    }
}

#endif

