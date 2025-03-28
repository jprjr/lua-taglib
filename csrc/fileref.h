#ifndef LTAGLIB_FILEREF_INCLUDE_GUARD
#define LTAGLIB_FILEREF_INCLUDE_GUARD

#include "taglib.h"
#include "shared/userdata.h"
#include <fileref.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_FileRef(lua_State *L);

}

namespace LuaTagLib {

    template<> const UserdataMetatable UserdataCommon<TagLib::FileRef>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::FileRef>::mod;

    typedef BaseUserdata<TagLib::FileRef> FileRef;
}

#endif

