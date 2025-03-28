#ifndef LTAGLIB_OGG_SPEEX_PROPERTIES_INCLUDE_GUARD
#define LTAGLIB_OGG_SPEEX_PROPERTIES_INCLUDE_GUARD

#include "../../taglib.h"

#define LTAGLIB_HAS_SPEEXPROPERTIES (LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,5,0))

#if LTAGLIB_HAS_SPEEXPROPERTIES

#include "../../shared/userdata.h"
#include "../../audioproperties.h"
#include <speexproperties.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_Ogg_Speex_Properties(lua_State *L);

}

namespace LuaTagLib {

#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::Ogg::Speex::Properties>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::Ogg::Speex::Properties>::mod;
#endif 


    namespace Ogg { namespace Speex {
        typedef DerivedUserdata<TagLib::Ogg::Speex::Properties, LuaTagLib::AudioProperties> Properties;
    } }
}

#endif

#endif

