#ifndef LTAGLIB_MOD_FILEBASE_INCLUDE_GUARD
#define LTAGLIB_MOD_FILEBASE_INCLUDE_GUARD

#include "../taglib.h"

#define LTAGLIB_HAS_MOD_FILEBASE (LTAGLIB_ATLEAST(LTAGLIB_1_8))

#if LTAGLIB_HAS_MOD_FILEBASE

#include "../tfile.h"
#include "../shared/userdata.h"
#include <modfilebase.h>


extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_Mod_FileBase(lua_State *L);

}

namespace LuaTagLib {
    template<> const UserdataMetatable UserdataCommon<TagLib::Mod::FileBase>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::Mod::FileBase>::mod;

    namespace Mod {
        typedef DerivedUserdata<TagLib::Mod::FileBase, LuaTagLib::File> FileBase;
    }
} 

#endif

#endif

