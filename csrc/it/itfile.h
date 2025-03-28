#ifndef LTAGLIB_IT_FILE_INCLUDE_GUARD
#define LTAGLIB_IT_FILE_INCLUDE_GUARD

#include "../taglib.h"

#define LTAGLIB_HAS_IT_FILE (LTAGLIB_ATLEAST(LTAGLIB_1_8))

#if LTAGLIB_HAS_IT_FILE

#include "../mod/modfilebase.h"
#include <itfile.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_IT_File(lua_State *L);

}

namespace LuaTagLib {
    template<> const UserdataMetatable UserdataCommon<TagLib::IT::File>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::IT::File>::mod;
    namespace IT {
        typedef DerivedUserdata<TagLib::IT::File, LuaTagLib::Mod::FileBase> File;
    }
}

#endif

#endif
