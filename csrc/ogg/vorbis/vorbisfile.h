#ifndef LTAGLIB_OGG_VORBIS_FILE_INCLUDE_GUARD
#define LTAGLIB_OGG_VORBIS_FILE_INCLUDE_GUARD

#include "../../taglib.h"
#include "../oggfile.h"
#include "../../shared/userdata.h"
#include <vorbisfile.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_Ogg_Vorbis_File(lua_State *L);

}

#if LTAGLIB_UNDER(LTAGLIB_1_2)
namespace TagLib { namespace Ogg { namespace Vorbis {
    typedef TagLib::Vorbis::File File;
} } }
#endif

namespace LuaTagLib { namespace Ogg { namespace Vorbis {
    typedef DerivedUserdata<TagLib::Ogg::Vorbis::File, LuaTagLib::Ogg::File> File;
}}}


#endif

