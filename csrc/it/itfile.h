#ifndef LTAGLIB_IT_FILE_INCLUDE_GUARD
#define LTAGLIB_IT_FILE_INCLUDE_GUARD

#include "../taglib.h"

#include "../mod/modfilebase.h"
#include <itfile.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_IT_File(lua_State *L);

}

namespace LuaTagLib {
#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::IT::File>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::IT::File>::mod;
#endif 

    namespace IT {
        typedef DerivedUserdata<TagLib::IT::File, LuaTagLib::Mod::FileBase> File;
    }
}

#endif
