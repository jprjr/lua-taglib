#ifndef LTAGLIB_ID3V2_HEADER_INCLUDE_GUARD
#define LTAGLIB_ID3V2_HEADER_INCLUDE_GUARD

#include "../taglib.h"
#include "../shared/userdata.h"
#include <id3v2header.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_Header(lua_State* L);

}

namespace LuaTagLib {

#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::ID3v2::Header>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::ID3v2::Header>::mod;
#endif 


    namespace ID3v2 {
        typedef BaseUserdata<TagLib::ID3v2::Header> Header;
    }
}

#endif

