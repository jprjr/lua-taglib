#ifndef LTAGLIB_OGG_PAGEHEADER_INCLUDE_GUARD
#define LTAGLIB_OGG_PAGEHEADER_INCLUDE_GUARD

#include "../shared/userdata.h"
#include <oggpageheader.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_Ogg_PageHeader(lua_State *L);

}


namespace LuaTagLib { namespace Ogg {
    typedef BaseUserdata<TagLib::Ogg::PageHeader> PageHeader;
} }

#endif

