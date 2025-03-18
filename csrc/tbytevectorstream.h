#ifndef LTAGLIB_BYTEVECTORSTREAM_INCLUDE_GUARD
#define LTAGLIB_BYTEVECTORSTREAM_INCLUDE_GUARD

#include "taglib.h"

#define LTAGLIB_HAS_BYTEVECTORSTREAM (LTAGLIB_ATLEAST(LTAGLIB_1_8))

#if LTAGLIB_HAS_BYTEVECTORSTREAM

#include "tiostream.h"
#include <tbytevectorstream.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_ByteVectorStream(lua_State* L);

}

namespace LuaTagLib {
    typedef DerivedUserdata<TagLib::ByteVectorStream, LuaTagLib::IOStream> ByteVectorStream;
}

#endif

#endif
