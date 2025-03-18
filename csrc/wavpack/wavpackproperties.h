#ifndef LTAGLIB_WAVPACK_PROPERTIES_INCLUDE_GUARD
#define LTAGLIB_WAVPACK_PROPERTIES_INCLUDE_GUARD

#include "../taglib.h"

#define LTAGLIB_HAS_WAVPACK_PROPERTIES (LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,5,0))

#if LTAGLIB_HAS_WAVPACK_PROPERTIES

#include "../audioproperties.h"
#include "../shared/userdata.h"

#include <tbytevector.h>
#include <wavpackproperties.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_WavPack_Properties(lua_State *L);

}


namespace LuaTagLib { namespace WavPack {
    typedef DerivedUserdata<TagLib::WavPack::Properties, LuaTagLib::AudioProperties> Properties;
} }

#endif

#endif
