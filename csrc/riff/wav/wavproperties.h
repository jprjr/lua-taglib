#ifndef LTAGLIB_RIFF_WAV_PROPERTIES_INCLUDE_GUARD
#define LTAGLIB_RIFF_WAV_PROPERTIES_INCLUDE_GUARD

#include "../../taglib.h"

#define LTAGLIB_HAS_RIFF_WAV_PROPERTIES (LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,6,0))

#if LTAGLIB_HAS_RIFF_WAV_PROPERTIES

#include "../../audioproperties.h"
#include "../../shared/userdata.h"

#include <tbytevector.h>
#include <wavproperties.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_RIFF_WAV_Properties(lua_State *L);

}

namespace LuaTagLib { namespace RIFF { namespace WAV {
    typedef DerivedUserdata<TagLib::RIFF::WAV::Properties, LuaTagLib::AudioProperties> Properties;
} } }

#endif

#endif
