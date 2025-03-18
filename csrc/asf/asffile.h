#ifndef LTAGLIB_ASF_FILE_INCLUDE_GUARD
#define LTAGLIB_ASF_FILE_INCLUDE_GUARD

#include "asf.h"

#if LTAGLIB_HAS_ASF

#include "../tfile.h"
#include "../shared/userdata.h"
#include <asffile.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_ASF_File(lua_State *L);

}

namespace LuaTagLib { namespace ASF {
    typedef DerivedUserdata<TagLib::ASF::File, LuaTagLib::File> File;
} }

#endif

#endif
