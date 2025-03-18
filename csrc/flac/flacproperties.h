#ifndef LTAGLIB_FLAC_PROPERTIES_INCLUDE_GUARD
#define LTAGLIB_FLAC_PROPERTIES_INCLUDE_GUARD

#include "../taglib.h"
#include "../audioproperties.h"
#include "../shared/userdata.h"

/* some older versions of taglib don't include tbytevector in
 * flacproperties.h so we'll just include it here */
#include <tbytevector.h>
#include <flacproperties.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_FLAC_Properties(lua_State *L);

}


namespace LuaTagLib { namespace FLAC {
    typedef DerivedUserdata<TagLib::FLAC::Properties, LuaTagLib::AudioProperties> Properties;
} }

#endif
