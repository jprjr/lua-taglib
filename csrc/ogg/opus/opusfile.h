#ifndef LTAGLIB_OGG_OPUS_FILE_INCLUDE_GUARD
#define LTAGLIB_OGG_OPUS_FILE_INCLUDE_GUARD

#include "../../taglib.h"

#define LTAGLIB_HAS_OPUSFILE (LTAGLIB_ATLEAST(LTAGLIB_1_9))

#if LTAGLIB_HAS_OPUSFILE

#include "../oggfile.h"
#include "../../shared/userdata.h"
#include <opusfile.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_Ogg_Opus_File(lua_State *L);

}

namespace LuaTagLib { namespace Ogg { namespace Opus {
    typedef DerivedUserdata<TagLib::Ogg::Opus::File, LuaTagLib::Ogg::File> File;
}}}

#endif

#endif

