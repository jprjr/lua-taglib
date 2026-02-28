#ifndef LTAGLIB_APE_PROPERTIES_INCLUDE_GUARD
#define LTAGLIB_APE_PROPERTIES_INCLUDE_GUARD

#include "../taglib.h"

#include "../audioproperties.h"
#include "../shared/userdata.h"
#include <apeproperties.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_APE_Properties(lua_State *L);

}


namespace LuaTagLib {

#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::APE::Properties>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::APE::Properties>::mod;
#endif 


    namespace APE {
        typedef DerivedUserdata<TagLib::APE::Properties, LuaTagLib::AudioProperties> Properties;
    }
}

#endif

