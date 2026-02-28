#ifndef LTAGLIB_MPC_PROPERTIES_INCLUDE_GUARD
#define LTAGLIB_MPC_PROPERTIES_INCLUDE_GUARD

#include "../taglib.h"
#include "../audioproperties.h"
#include "../shared/userdata.h"

#include <tbytevector.h>
#include <mpcproperties.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_MPC_Properties(lua_State *L);

}

namespace LuaTagLib {
#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::MPC::Properties>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::MPC::Properties>::mod;
#endif 


    namespace MPC {
        typedef DerivedUserdata<TagLib::MPC::Properties, LuaTagLib::AudioProperties> Properties;
    }
}

#endif

