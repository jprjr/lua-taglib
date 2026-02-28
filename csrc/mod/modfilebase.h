#ifndef LTAGLIB_MOD_FILEBASE_INCLUDE_GUARD
#define LTAGLIB_MOD_FILEBASE_INCLUDE_GUARD

#include "../taglib.h"

#include "../tfile.h"
#include "../shared/userdata.h"
#include <modfilebase.h>


extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_Mod_FileBase(lua_State *L);

}

namespace LuaTagLib {
#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::Mod::FileBase>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::Mod::FileBase>::mod;
#endif 


    namespace Mod {
        typedef DerivedUserdata<TagLib::Mod::FileBase, LuaTagLib::File> FileBase;
    }
} 

#endif
