#ifndef LTAGLIB_ID3V1_TAG_INCLUDE_GUARD
#define LTAGLIB_ID3V1_TAG_INCLUDE_GUARD

#include "../tag.h"
#include "../shared/userdata.h"

#include <id3v1tag.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v1_Tag(lua_State *L);

}

namespace LuaTagLib {

#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::ID3v1::Tag>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::ID3v1::Tag>::mod;
#endif 


    namespace ID3v1 {
        typedef DerivedUserdata<TagLib::ID3v1::Tag,LuaTagLib::Tag> Tag;
    }
}


#endif
