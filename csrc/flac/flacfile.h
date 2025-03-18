#ifndef LTAGLIB_FLAC_FILE_INCLUDE_GUARD
#define LTAGLIB_FLAC_FILE_INCLUDE_GUARD

#include "../taglib.h"
#include "../tfile.h"
#include "../shared/userdata.h"
#include <flacfile.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_FLAC_File(lua_State *L);

#if LTAGLIB_ATLEAST(LTAGLIB_1_11)

LTAGLIB_PUBLIC
int luaopen_TagLib_FLAC_File_TagTypes(lua_State *L);

#endif

}

namespace LuaTagLib { namespace FLAC {
    typedef DerivedUserdata<TagLib::FLAC::File, LuaTagLib::File> File;
} }

#endif
