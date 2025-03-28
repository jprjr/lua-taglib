#ifndef LTAGLIB_TAG_INCLUDE_GUARD
#define LTAGLIB_TAG_INCLUDE_GUARD

#include "shared/userdata.h"

#include <tag.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_Tag(lua_State* L);

}

namespace LuaTagLib {

    template<> const UserdataMetatable UserdataCommon<TagLib::Tag>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::Tag>::mod;

    typedef BaseUserdata<TagLib::Tag> Tag;
}

#endif

