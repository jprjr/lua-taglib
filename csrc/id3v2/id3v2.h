#ifndef LTAGLIB_ID3V2_INCLUDE_GUARD
#define LTAGLIB_ID3V2_INCLUDE_GUARD

#include "../taglib.h"

#define LTAGLIB_HAS_ID3V2_VERSION (LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,12,0))

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2(lua_State *L);

}

#if LTAGLIB_HAS_ID3V2_VERSION

#include "../shared/enum.h"
#include <id3v2.h>

extern "C"  {

LTAGLIB_PUBLIC int
luaopen_TagLib_ID3v2_Version(lua_State* L);
}

namespace LuaTagLib { namespace ID3v2 {
    typedef Enum<TagLib::ID3v2::Version> Version;
} }

#endif

#endif

