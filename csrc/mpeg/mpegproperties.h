#ifndef LTAGLIB_MPEG_PROPERTIES_INCLUDE_GUARD
#define LTAGLIB_MPEG_PROPERTIES_INCLUDE_GUARD

#include "../taglib.h"
#include "../audioproperties.h"
#include "../shared/userdata.h"
#include <mpegproperties.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_MPEG_Properties(lua_State *L);

}

namespace LuaTagLib { namespace MPEG {
    typedef DerivedUserdata<TagLib::MPEG::Properties,LuaTagLib::AudioProperties> Properties;
} }

#endif


