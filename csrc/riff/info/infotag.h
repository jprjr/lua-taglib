#ifndef LTAGLIB_RIFF_INFO_TAG_INCLUDE_GUARD
#define LTAGLIB_RIFF_INFO_TAG_INCLUDE_GUARD

#include "../../taglib.h"

#define LTAGLIB_HAS_RIFF_INFO_TAG (LTAGLIB_ATLEAST(LTAGLIB_1_9))

#if LTAGLIB_HAS_RIFF_INFO_TAG

#include "../../tag.h"
#include "../../shared/userdata.h"

#include <infotag.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_RIFF_Info_Tag(lua_State *L);

}

namespace LuaTagLib { namespace RIFF { namespace Info {
    typedef DerivedUserdata<TagLib::RIFF::Info::Tag,LuaTagLib::Tag> Tag;
} } }


#endif

#endif
