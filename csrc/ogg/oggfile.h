#ifndef LTAGLIB_OGG_FILE_INCLUDE_GUARD
#define LTAGLIB_OGG_FILE_INCLUDE_GUARD

#include "../taglib.h"
#include "../tfile.h"
#include "../shared/userdata.h"
#include <oggfile.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_Ogg_File(lua_State *L);

}

namespace LuaTagLib {

#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::Ogg::File>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::Ogg::File>::mod;
#endif 


    namespace Ogg {
        typedef DerivedUserdata<TagLib::Ogg::File, LuaTagLib::File> File;
    }
}

#endif


