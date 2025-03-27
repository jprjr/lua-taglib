#ifndef LTAGLIB_AUDIOPROPERTIES_INCLUDE_GUARD
#define LTAGLIB_AUDIOPROPERTIES_INCLUDE_GUARD

#include "taglib.h"
#include "shared/userdata.h"
#include "shared/enum.h"
#include <audioproperties.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_AudioProperties(lua_State *L);

LTAGLIB_PUBLIC
int luaopen_TagLib_AudioProperties_ReadStyle(lua_State *L);

}

namespace LuaTagLib {
    class LTAGLIB_PRIVATE AudioProperties: public BaseUserdata<TagLib::AudioProperties> {
        public:
            typedef Enum<TagLib::AudioProperties::ReadStyle> ReadStyle;
    };
}

#endif


