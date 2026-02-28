#ifndef LTAGLIB_MATROSKA_PROPERTIES_INCLUDE_GUARD
#define LTAGLIB_MATROSKA_PROPERTIES_INCLUDE_GUARD

#include "../taglib.h"

#include "../audioproperties.h"
#include "../shared/userdata.h"

#include <matroskaproperties.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_Matroska_Properties(lua_State *L);

}

namespace LuaTagLib {

#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::Matroska::Properties>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::Matroska::Properties>::mod;
#endif 


    namespace Matroska {
        typedef DerivedUserdata<TagLib::Matroska::Properties, LuaTagLib::AudioProperties> Properties;
    }
}

#endif

