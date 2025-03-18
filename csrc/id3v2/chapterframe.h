#ifndef LTAGLIB_ID3V2_CHAPTERFRAME_INCLUDE_GUARD
#define LTAGLIB_ID3V2_CHAPTERFRAME_INCLUDE_GUARD

#include "../taglib.h"

#define LTAGLIB_HAS_CHAPTERFRAME (LTAGLIB_ATLEAST(LTAGLIB_1_10))

#if LTAGLIB_HAS_CHAPTERFRAME

#include "id3v2frame.h"
#include <chapterframe.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_ChapterFrame(lua_State* L);

}

namespace LuaTagLib { namespace ID3v2 {
    typedef DerivedUserdata<TagLib::ID3v2::ChapterFrame, Frame> ChapterFrame;
} }

#endif

#endif
