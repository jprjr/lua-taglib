#ifndef LTAGLIB_MATROSKA_FILE_INCLUDE_GUARD
#define LTAGLIB_MATROSKA_FILE_INCLUDE_GUARD

#include "../taglib.h"
#include "../tfile.h"
#include "../shared/userdata.h"
#include <matroskafile.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_Matroska_File(lua_State *L);

}

namespace LuaTagLib {

#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::Matroska::File>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::Matroska::File>::mod;
#endif 


    namespace Matroska {
        typedef DerivedUserdata<TagLib::Matroska::File, LuaTagLib::File> File;
    }
}

#endif


