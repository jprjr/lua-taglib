#ifndef LTAGLIB_OGG_SPEEX_FILE_INCLUDE_GUARD
#define LTAGLIB_OGG_SPEEX_FILE_INCLUDE_GUARD

#include "../../taglib.h"

#define LTAGLIB_HAS_SPEEXFILE (LTAGLIB_ATLEAST(LTAGLIB_1_5))

#if LTAGLIB_HAS_SPEEXFILE

#include "../oggfile.h"
#include "../../shared/userdata.h"
#include <speexfile.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_Ogg_Speex_File(lua_State *L);

}

namespace LuaTagLib { namespace Ogg { namespace Speex {
    typedef DerivedUserdata<TagLib::Ogg::Speex::File, LuaTagLib::Ogg::File> File;
}}}

#endif

#endif

