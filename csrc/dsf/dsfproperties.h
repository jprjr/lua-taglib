#ifndef LTAGLIB_DSF_PROPERTIES_INCLUDE_GUARD
#define LTAGLIB_DSF_PROPERTIES_INCLUDE_GUARD

#include "../taglib.h"

#define LTAGLIB_HAS_DSF_PROPERTIES (LTAGLIB_ATLEAST(LTAGLIB_2_0))

#if LTAGLIB_HAS_DSF_PROPERTIES

#include "../audioproperties.h"
#include "../shared/userdata.h"

#include <tbytevector.h>
#include <dsfproperties.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_DSF_Properties(lua_State *L);

}

namespace LuaTagLib {

    template<> const UserdataMetatable UserdataCommon<TagLib::DSF::Properties>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::DSF::Properties>::mod;

    namespace DSF {
        typedef DerivedUserdata<TagLib::DSF::Properties, LuaTagLib::AudioProperties> Properties;
    }
}

#endif

#endif

