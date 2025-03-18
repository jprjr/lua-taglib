#ifndef LTAGLIB_MOD_TAG_INCLUDE_GUARD
#define LTAGLIB_MOD_TAG_INCLUDE_GUARD

#include "../taglib.h"

#define LTAGLIB_HAS_MOD_TAG (LTAGLIB_ATLEAST(LTAGLIB_1_8))

#if LTAGLIB_HAS_MOD_TAG

#include "../tag.h"
#include "../shared/userdata.h"
#include <modtag.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_Mod_Tag(lua_State *L);

}
namespace LuaTagLib { namespace Mod {
    typedef DerivedUserdata<TagLib::Mod::Tag, LuaTagLib::Tag> Tag;
} }

#endif

#endif


