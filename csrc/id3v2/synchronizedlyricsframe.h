#ifndef LTAGLIB_ID3V2_SYNCHRONIZEDLYRICSFRAME_INCLUDE_GUARD
#define LTAGLIB_ID3V2_SYNCHRONIZEDLYRICSFRAME_INCLUDE_GUARD

#include "../taglib.h"

#define LTAGLIB_HAS_SYNCHRONIZEDLYRICSFRAME (LTAGLIB_ATLEAST(LTAGLIB_1_10))

#if LTAGLIB_HAS_SYNCHRONIZEDLYRICSFRAME

#include "../shared/enum.h"
#include "id3v2frame.h"
#include <synchronizedlyricsframe.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_SynchronizedLyricsFrame(lua_State* L);

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_SynchronizedLyricsFrame_Type(lua_State* L);

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_SynchronizedLyricsFrame_TimestampFormat(lua_State* L);

}

namespace LuaTagLib {

    template<> const UserdataMetatable UserdataCommon<TagLib::ID3v2::SynchronizedLyricsFrame>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::ID3v2::SynchronizedLyricsFrame>::mod;

    namespace ID3v2 {
    class LTAGLIB_PRIVATE SynchronizedLyricsFrame: public DerivedUserdata<TagLib::ID3v2::SynchronizedLyricsFrame, Frame> {
        public:
            typedef Enum<TagLib::ID3v2::SynchronizedLyricsFrame::Type> Type;
            typedef Enum<TagLib::ID3v2::SynchronizedLyricsFrame::TimestampFormat> TimestampFormat;
    };
} }

#endif

#endif
