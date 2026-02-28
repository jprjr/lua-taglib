#ifndef LTAGLIB_MOD_TAG_INCLUDE_GUARD
#define LTAGLIB_MOD_TAG_INCLUDE_GUARD

#include "../taglib.h"

#include "../tag.h"
#include "../shared/userdata.h"
#include <modtag.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_Mod_Tag(lua_State *L);

}
namespace LuaTagLib {

#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::Mod::Tag>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::Mod::Tag>::mod;
#endif 


    namespace Mod {
        typedef DerivedUserdata<TagLib::Mod::Tag, LuaTagLib::Tag> Tag;
    }
}

#endif
