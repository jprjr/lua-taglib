#ifndef LTAGLIB_XM_FILE_INCLUDE_GUARD
#define LTAGLIB_XM_FILE_INCLUDE_GUARD

#include "../taglib.h"

#include "../mod/modfilebase.h"
#include <xmfile.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_XM_File(lua_State *L);

}

namespace LuaTagLib {

#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::XM::File>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::XM::File>::mod;
#endif 


    namespace XM {
        typedef DerivedUserdata<TagLib::XM::File, LuaTagLib::Mod::FileBase> File;
    }
}

#endif
