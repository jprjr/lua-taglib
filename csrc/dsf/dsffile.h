#ifndef LTAGLIB_DSF_FILE_INCLUDE_GUARD
#define LTAGLIB_DSF_FILE_INCLUDE_GUARD

#include "../taglib.h"

#include "../tfile.h"
#include "../shared/userdata.h"
#include <dsffile.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_DSF_File(lua_State *L);

LTAGLIB_PUBLIC
int luaopen_TagLib_DSF_File_TagTypes(lua_State *L);

}

namespace LuaTagLib {

#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::DSF::File>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::DSF::File>::mod;
#endif 


    namespace DSF {
        typedef DerivedUserdata<TagLib::DSF::File, LuaTagLib::File> File;
    }
}

#endif
