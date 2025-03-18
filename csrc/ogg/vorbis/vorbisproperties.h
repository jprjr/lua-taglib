#ifndef LTAGLIB_OGG_VORBIS_PROPERTIES_INCLUDE_GUARD
#define LTAGLIB_OGG_VORBIS_PROPERTIES_INCLUDE_GUARD

#include "../../taglib.h"
#include "../../audioproperties.h"
#include "../../shared/userdata.h"
#include <vorbisproperties.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_Ogg_Vorbis_Properties(lua_State *L);

}

#if LTAGLIB_UNDER(LTAGLIB_2_0)
namespace TagLib { namespace Ogg { namespace Vorbis {
    typedef TagLib::Vorbis::Properties Properties;
} } }
#endif

namespace LuaTagLib { namespace Ogg { namespace Vorbis {
    typedef DerivedUserdata<TagLib::Ogg::Vorbis::Properties, LuaTagLib::AudioProperties> Properties;
} } }

#endif

