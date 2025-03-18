#ifndef LTAGLIB_MOD_PROPERTIES_INCLUDE_GUARD
#define LTAGLIB_MOD_PROPERTIES_INCLUDE_GUARD

#include "../taglib.h"

#define LTAGLIB_HAS_MOD_PROPERTIES (LTAGLIB_ATLEAST(LTAGLIB_1_8))

#if LTAGLIB_HAS_MOD_PROPERTIES

#include "../audioproperties.h"
#include "../shared/userdata.h"

#include <tbytevector.h>
#include <modproperties.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_Mod_Properties(lua_State *L);

}

namespace LuaTagLib { namespace Mod {
    typedef DerivedUserdata<TagLib::Mod::Properties, LuaTagLib::AudioProperties> Properties;
} }

#endif

#endif

