#ifndef LTAGLIB_FILESTREAM_INCLUDE_GUARD
#define LTAGLIB_FILESTREAM_INCLUDE_GUARD

#include "taglib.h"

#define LTAGLIB_HAS_FILESTREAM (LTAGLIB_ATLEAST(LTAGLIB_1_8))

#if LTAGLIB_HAS_FILESTREAM

#include "tiostream.h"
#include <tfilestream.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_FileStream(lua_State* L);

}

namespace LuaTagLib {
    typedef DerivedUserdata<TagLib::FileStream, LuaTagLib::IOStream> FileStream;
}

#endif

#endif
