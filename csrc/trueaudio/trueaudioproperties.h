#ifndef LTAGLIB_TRUEAUDIO_PROPERTIES_INCLUDE_GUARD
#define LTAGLIB_TRUEAUDIO_PROPERTIES_INCLUDE_GUARD

#include "../taglib.h"

#define LTAGLIB_HAS_TRUEAUDIO_PROPERTIES (LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,5,0))

#if LTAGLIB_HAS_TRUEAUDIO_PROPERTIES

#include "../audioproperties.h"
#include "../shared/userdata.h"

#include <tbytevector.h>
#include <trueaudioproperties.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_TrueAudio_Properties(lua_State *L);

}


namespace LuaTagLib {

#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::TrueAudio::Properties>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::TrueAudio::Properties>::mod;
#endif 


    namespace TrueAudio {
        typedef DerivedUserdata<TagLib::TrueAudio::Properties, LuaTagLib::AudioProperties> Properties;
    }
}

#endif

#endif
