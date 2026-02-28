#ifndef LTAGLIB_MATROSKA_TAG_INCLUDE_GUARD
#define LTAGLIB_MATROSKA_TAG_INCLUDE_GUARD

#include "../taglib.h"

#include "../shared/userdata.h"
#include "../tag.h"
#include <matroskatag.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_Matroska_Tag(lua_State *L);

}
namespace LuaTagLib {

#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::Matroska::Tag>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::Matroska::Tag>::mod;
#endif 


    namespace Matroska {
        typedef DerivedUserdata<TagLib::Matroska::Tag, LuaTagLib::Tag> Tag;
    }
}

#endif


