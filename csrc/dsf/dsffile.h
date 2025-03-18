#ifndef LTAGLIB_DSF_FILE_INCLUDE_GUARD
#define LTAGLIB_DSF_FILE_INCLUDE_GUARD

#include "../taglib.h"

#define LTAGLIB_HAS_DSF_FILE (LTAGLIB_ATLEAST(LTAGLIB_2_0))

#if LTAGLIB_HAS_DSF_FILE

#include "../tfile.h"
#include "../shared/userdata.h"
#include <dsffile.h>


extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_DSF_File(lua_State *L);

LTAGLIB_PUBLIC
int luaopen_TagLib_DSF_File_TagTypes(lua_State *L);

}

namespace LuaTagLib { namespace DSF {
    typedef DerivedUserdata<TagLib::DSF::File, LuaTagLib::File> File;
} }

#endif

#endif
