#ifndef LTAGLIB_ID3V2_PODCASTFRAME_INCLUDE_GUARD
#define LTAGLIB_ID3V2_PODCASTFRAME_INCLUDE_GUARD

#include "../taglib.h"

#define LTAGLIB_HAS_PODCASTFRAME (LTAGLIB_ATLEAST(LTAGLIB_1_11))

#if LTAGLIB_HAS_PODCASTFRAME

#include "id3v2frame.h"
#include <podcastframe.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_PodcastFrame(lua_State* L);

}

namespace LuaTagLib {

#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::ID3v2::PodcastFrame>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::ID3v2::PodcastFrame>::mod;
#endif 


    namespace ID3v2 {
    typedef DerivedUserdata<TagLib::ID3v2::PodcastFrame, Frame> PodcastFrame;
} }

#endif

#endif
