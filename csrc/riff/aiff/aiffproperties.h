#ifndef LTAGLIB_RIFF_AIFF_PROPERTIES_INCLUDE_GUARD
#define LTAGLIB_RIFF_AIFF_PROPERTIES_INCLUDE_GUARD

#include "../../taglib.h"

#define LTAGLIB_HAS_RIFF_AIFF_PROPERTIES (LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,6,0))

#if LTAGLIB_HAS_RIFF_AIFF_PROPERTIES

#include "../../audioproperties.h"
#include "../../shared/userdata.h"

#include <tbytevector.h>
#include <aiffproperties.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_RIFF_AIFF_Properties(lua_State *L);

}

namespace LuaTagLib { namespace RIFF { namespace AIFF {
    typedef DerivedUserdata<TagLib::RIFF::AIFF::Properties, LuaTagLib::AudioProperties> Properties;
} } }

#endif

#endif
