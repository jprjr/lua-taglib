#ifndef LTAGLIB_MP4_PROPERTIES_INCLUDE_GUARD
#define LTAGLIB_MP4_PROPERTIES_INCLUDE_GUARD

#include "mp4.h"

#if LTAGLIB_HAS_MP4

#include "../audioproperties.h"
#include "../shared/userdata.h"

#include <tbytevector.h>
#include <mp4properties.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_MP4_Properties(lua_State *L);

#if LTAGLIB_ATLEAST(LTAGLIB_1_10)

LTAGLIB_PUBLIC
int luaopen_TagLib_MP4_Properties_Codec(lua_State *L);

#endif

}

namespace LuaTagLib {

#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::MP4::Properties>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::MP4::Properties>::mod;
#endif 


    namespace MP4 {
    class LTAGLIB_PRIVATE Properties: public DerivedUserdata<TagLib::MP4::Properties, LuaTagLib::AudioProperties> {
        public:
#if LTAGLIB_ATLEAST(LTAGLIB_1_10)
            typedef Enum<TagLib::MP4::Properties::Codec> Codec;
#endif

    };
    }
}

#endif

#endif
