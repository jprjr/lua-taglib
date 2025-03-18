#ifndef LTAGLIB_MP4_TAG_INCLUDE_GUARD
#define LTAGLIB_MP4_TAG_INCLUDE_GUARD

#include "mp4.h"

#if LTAGLIB_HAS_MP4

#include "../shared/userdata.h"
#include "../tag.h"
#include <mp4tag.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_MP4_Tag(lua_State *L);

}
namespace LuaTagLib { namespace MP4 {
    typedef DerivedUserdata<TagLib::MP4::Tag, LuaTagLib::Tag> Tag;
} }

#endif

#endif


