#ifndef LTAGLIB_IT_PROPERTIES_INCLUDE_GUARD
#define LTAGLIB_IT_PROPERTIES_INCLUDE_GUARD

#include "../taglib.h"

#include "../audioproperties.h"
#include "../shared/userdata.h"

#include <itproperties.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_IT_Properties(lua_State *L);

}

namespace LuaTagLib {

#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::IT::Properties>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::IT::Properties>::mod;
#endif 


    namespace IT {
        class LTAGLIB_PUBLIC Properties: public DerivedUserdata<TagLib::IT::Properties, LuaTagLib::AudioProperties> { };
    }
}

#endif
