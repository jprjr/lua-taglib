#ifndef LTAGLIB_DSF_PROPERTIES_INCLUDE_GUARD
#define LTAGLIB_DSF_PROPERTIES_INCLUDE_GUARD

#include "../taglib.h"
#include "../audioproperties.h"
#include "../shared/userdata.h"

#include <tbytevector.h>
#include <dsfproperties.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_DSF_Properties(lua_State *L);

}

namespace LuaTagLib {

#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::DSF::Properties>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::DSF::Properties>::mod;
#endif 


    namespace DSF {
        typedef DerivedUserdata<TagLib::DSF::Properties, LuaTagLib::AudioProperties> Properties;
    }
}

#endif

