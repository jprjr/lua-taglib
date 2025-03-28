#ifndef LTAGLIB_MOD_FILE_INCLUDE_GUARD
#define LTAGLIB_MOD_FILE_INCLUDE_GUARD

#include "../taglib.h"

#define LTAGLIB_HAS_MOD_FILE (LTAGLIB_ATLEAST(LTAGLIB_1_8))

#if LTAGLIB_HAS_MOD_FILE

#include "modfilebase.h"
#include <modfile.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_Mod_File(lua_State *L);

}

namespace LuaTagLib {
    template<> const UserdataMetatable UserdataCommon<TagLib::Mod::File>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::Mod::File>::mod;
    namespace Mod {
        typedef DerivedUserdata<TagLib::Mod::File, LuaTagLib::Mod::FileBase> File;
    }
}

#endif

#endif
