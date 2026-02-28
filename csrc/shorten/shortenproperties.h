#ifndef LTAGLIB_SHORTEN_PROPERTIES_INCLUDE_GUARD
#define LTAGLIB_SHORTEN_PROPERTIES_INCLUDE_GUARD

#include "../taglib.h"

#include "../audioproperties.h"
#include "../shared/userdata.h"

#include <shortenproperties.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_Shorten_Properties(lua_State *L);

}

namespace LuaTagLib {

#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::Shorten::Properties>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::Shorten::Properties>::mod;
#endif 


    namespace Shorten {
        typedef DerivedUserdata<TagLib::Shorten::Properties, LuaTagLib::AudioProperties> Properties;
    }
}

#endif

