#ifndef LTAGLIB_ID3V2_EXTENDEDHEADER_INCLUDE_GUARD
#define LTAGLIB_ID3V2_EXTENDEDHEADER_INCLUDE_GUARD

#include "../shared/userdata.h"

#include <id3v2extendedheader.h>

extern "C" {

LTAGLIB_PUBLIC int
luaopen_TagLib_ID3v2_ExtendedHeader(lua_State* L);

}

namespace LuaTagLib { namespace ID3v2 {
    typedef BaseUserdata<TagLib::ID3v2::ExtendedHeader> ExtendedHeader;
} }

#endif

