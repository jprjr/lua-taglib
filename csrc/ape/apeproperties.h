#ifndef LTAGLIB_APE_PROPERTIES_INCLUDE_GUARD
#define LTAGLIB_APE_PROPERTIES_INCLUDE_GUARD

#include "../taglib.h"

#define LTAGLIB_HAS_APE_PROPERTIES (LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,7,0))

#if LTAGLIB_HAS_APE_PROPERTIES

#include "../audioproperties.h"
#include "../shared/userdata.h"
#include <apeproperties.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_APE_Properties(lua_State *L);

}


namespace LuaTagLib { namespace APE {
    typedef DerivedUserdata<TagLib::APE::Properties, LuaTagLib::AudioProperties> Properties;
} }

#endif

#endif

