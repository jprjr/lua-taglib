#ifndef LTAGLIB_ASF_TAG_INCLUDE_GUARD
#define LTAGLIB_ASF_TAG_INCLUDE_GUARD

#include "asf.h"

#if LTAGLIB_HAS_ASF

#include "../tag.h"
#include "../shared/userdata.h"

#include <asftag.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_ASF_Tag(lua_State *L);

}

namespace LuaTagLib {

#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::ASF::Tag>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::ASF::Tag>::mod;
#endif 


    namespace ASF {
        typedef DerivedUserdata<TagLib::ASF::Tag,LuaTagLib::Tag> Tag;
    }
}

#endif

#endif
