#ifndef LTAGLIB_OGG_OPUS_PROPERTIES_INCLUDE_GUARD
#define LTAGLIB_OGG_OPUS_PROPERTIES_INCLUDE_GUARD

#include "../../taglib.h"

#define LTAGLIB_HAS_OPUSPROPERTIES (LTAGLIB_ATLEAST(LTAGLIB_1_9))

#if LTAGLIB_HAS_OPUSPROPERTIES

#include "../../shared/userdata.h"
#include "../../audioproperties.h"
#include <opusproperties.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_Ogg_Opus_Properties(lua_State *L);

}


namespace LuaTagLib { namespace Ogg { namespace Opus {
    typedef DerivedUserdata<TagLib::Ogg::Opus::Properties, LuaTagLib::AudioProperties> Properties;
} } }

#endif

#endif

