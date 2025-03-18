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
    typedef BaseUserdata<TagLib::FileRef> FileRef;
}

#endif

