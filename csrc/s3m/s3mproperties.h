#ifndef LTAGLIB_S3M_PROPERTIES_INCLUDE_GUARD
#define LTAGLIB_S3M_PROPERTIES_INCLUDE_GUARD

#include "../taglib.h"

#define LTAGLIB_HAS_S3M_PROPERTIES (LTAGLIB_ATLEAST(LTAGLIB_1_8))

#if LTAGLIB_HAS_S3M_PROPERTIES

#include "../audioproperties.h"
#include "../shared/userdata.h"

#include <s3mproperties.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_S3M_Properties(lua_State *L);

}

namespace LuaTagLib {

#ifndef _MSC_VER 
    template<> const UserdataMetatable UserdataCommon<TagLib::S3M::Properties>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::S3M::Properties>::mod;
#endif 

    namespace S3M {
        class LTAGLIB_PUBLIC Properties: public DerivedUserdata<TagLib::S3M::Properties, LuaTagLib::AudioProperties> { };
    }

}

#endif

#endif

