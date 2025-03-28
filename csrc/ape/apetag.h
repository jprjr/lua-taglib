#ifndef LTAGLIB_APE_TAG_INCLUDE_GUARD
#define LTAGLIB_APE_TAG_INCLUDE_GUARD

#include "../taglib.h"

#define LTAGLIB_HAS_APE_TAG (LTAGLIB_ATLEAST(LTAGLIB_1_3))

#if LTAGLIB_HAS_APE_TAG

#include "../tag.h"
#include "../shared/userdata.h"
#include <apetag.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_APE_Tag(lua_State *L);

}

namespace LuaTagLib {

#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::APE::Tag>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::APE::Tag>::mod;
#endif 


    namespace APE {
        typedef DerivedUserdata<TagLib::APE::Tag, LuaTagLib::Tag> Tag;
    }
}

#endif

#endif


