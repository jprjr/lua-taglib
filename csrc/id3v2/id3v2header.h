#ifndef LTAGLIB_ID3V2_HEADER_INCLUDE_GUARD
#define LTAGLIB_ID3V2_HEADER_INCLUDE_GUARD

#include "../taglib.h"
#include "../shared/userdata.h"
#include <id3v2header.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_Header(lua_State* L);

}

namespace LuaTagLib { namespace ID3v2 {
    typedef BaseUserdata<TagLib::ID3v2::Header> Header;
} }

#endif

