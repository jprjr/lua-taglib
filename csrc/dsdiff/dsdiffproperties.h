#ifndef LTAGLIB_DSDIFF_PROPERTIES_INCLUDE_GUARD
#define LTAGLIB_DSDIFF_PROPERTIES_INCLUDE_GUARD

#include "../taglib.h"

#define LTAGLIB_HAS_DSDIFF_PROPERTIES (LTAGLIB_ATLEAST(LTAGLIB_2_0))

#if LTAGLIB_HAS_DSDIFF_PROPERTIES

#include "../audioproperties.h"
#include "../shared/userdata.h"

#include <tbytevector.h>
#include <dsdiffproperties.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_DSDIFF_Properties(lua_State *L);

}

namespace LuaTagLib {

#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::DSDIFF::Properties>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::DSDIFF::Properties>::mod;
#endif 


    namespace DSDIFF {
        typedef DerivedUserdata<TagLib::DSDIFF::Properties, LuaTagLib::AudioProperties> Properties;
    }
}

#endif

#endif

