#ifndef LTAGLIB_XM_FILE_INCLUDE_GUARD
#define LTAGLIB_XM_FILE_INCLUDE_GUARD

#include "../taglib.h"

#define LTAGLIB_HAS_XM_FILE (LTAGLIB_ATLEAST(LTAGLIB_1_8))

#if LTAGLIB_HAS_XM_FILE

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

#endif
