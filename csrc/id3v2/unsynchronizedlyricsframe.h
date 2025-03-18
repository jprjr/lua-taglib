#ifndef LTAGLIB_ID3V2_UNSYNCHRONIZEDLYRICSFRAME_INCLUDE_GUARD
#define LTAGLIB_ID3V2_UNSYNCHRONIZEDLYRICSFRAME_INCLUDE_GUARD

#include "../taglib.h"

#define LTAGLIB_HAS_UNSYNCHRONIZEDLYRICSFRAME (LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,5,0))

#if LTAGLIB_HAS_UNSYNCHRONIZEDLYRICSFRAME

#include "id3v2frame.h"
#include <unsynchronizedlyricsframe.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_UnsynchronizedLyricsFrame(lua_State* L);

}

namespace LuaTagLib { namespace ID3v2 {
    typedef DerivedUserdata<TagLib::ID3v2::UnsynchronizedLyricsFrame, Frame> UnsynchronizedLyricsFrame;
} }

#endif

#endif
