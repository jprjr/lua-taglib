#ifndef LTAGLIB_ASF_PROPERTIES_INCLUDE_GUARD
#define LTAGLIB_ASF_PROPERTIES_INCLUDE_GUARD

#include "asf.h"

#if LTAGLIB_HAS_ASF

#include "../audioproperties.h"
#include "../shared/userdata.h"

#include <tbytevector.h>
#include <asfproperties.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_ASF_Properties(lua_State *L);

#if LTAGLIB_ATLEAST(LTAGLIB_1_10)

LTAGLIB_PUBLIC
int luaopen_TagLib_ASF_Properties_Codec(lua_State *L);

#endif

}


namespace LuaTagLib {

#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::ASF::Properties>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::ASF::Properties>::mod;
#endif 


    namespace ASF {

    class LTAGLIB_PRIVATE Properties: public DerivedUserdata<TagLib::ASF::Properties, LuaTagLib::AudioProperties> {
        public:
#if LTAGLIB_ATLEAST(LTAGLIB_1_10)
            typedef Enum<TagLib::ASF::Properties::Codec> Codec;
#endif
    };
} }

#endif

#endif

