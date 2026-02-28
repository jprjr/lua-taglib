#ifndef LTAGLIB_SHORTEN_FILE_INCLUDE_GUARD
#define LTAGLIB_SHORTEN_FILE_INCLUDE_GUARD

#include "../taglib.h"
#include "../tfile.h"
#include "../shared/userdata.h"
#include <shortenfile.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_Shorten_File(lua_State *L);

LTAGLIB_PUBLIC
int luaopen_TagLib_Shorten_File_TagTypes(lua_State *L);

}

namespace LuaTagLib {

#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::Shorten::File>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::Shorten::File>::mod;
#endif 


    namespace Shorten {
        typedef DerivedUserdata<TagLib::Shorten::File, LuaTagLib::File> File;
    }
}

#endif

