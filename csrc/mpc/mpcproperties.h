#ifndef LTAGLIB_MPC_PROPERTIES_INCLUDE_GUARD
#define LTAGLIB_MPC_PROPERTIES_INCLUDE_GUARD

#include "../taglib.h"

#define LTAGLIB_HAS_MPC_PROPERTIES (LTAGLIB_ATLEAST(LTAGLIB_1_3))

#if LTAGLIB_HAS_MPC_PROPERTIES

#include "../audioproperties.h"
#include "../shared/userdata.h"

#include <tbytevector.h>
#include <mpcproperties.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_MPC_Properties(lua_State *L);

}

namespace LuaTagLib {
    template<> const UserdataMetatable UserdataCommon<TagLib::MPC::Properties>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::MPC::Properties>::mod;

    namespace MPC {
        typedef DerivedUserdata<TagLib::MPC::Properties, LuaTagLib::AudioProperties> Properties;
    }
}

#endif

#endif
