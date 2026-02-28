#ifndef LTAGLIB_XM_PROPERTIES_INCLUDE_GUARD
#define LTAGLIB_XM_PROPERTIES_INCLUDE_GUARD

#include "../taglib.h"
#include "../audioproperties.h"
#include "../shared/userdata.h"

#include <xmproperties.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_XM_Properties(lua_State *L);

}

namespace LuaTagLib {

#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::XM::Properties>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::XM::Properties>::mod;
#endif 


    namespace XM {
       typedef DerivedUserdata<TagLib::XM::Properties, LuaTagLib::AudioProperties> Properties;
    }
} 

#endif

