#ifndef LTAGLIB_ID3V2_FOOTER_INCLUDE_GUARD
#define LTAGLIB_ID3V2_FOOTER_INCLUDE_GUARD

#include "../taglib.h"
#include "../shared/userdata.h"
#include <id3v2footer.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_Footer(lua_State* L);

}

namespace LuaTagLib {

    template<> const UserdataMetatable UserdataCommon<TagLib::ID3v2::Footer>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::ID3v2::Footer>::mod;

    namespace ID3v2 {
        typedef BaseUserdata<TagLib::ID3v2::Footer> Footer;
    }
}

#endif


