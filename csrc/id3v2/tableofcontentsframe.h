#ifndef LTAGLIB_ID3V2_TABLEOFCONTENTSFRAME_INCLUDE_GUARD
#define LTAGLIB_ID3V2_TABLEOFCONTENTSFRAME_INCLUDE_GUARD

#include "../taglib.h"

#define LTAGLIB_HAS_TABLEOFCONTENTSFRAME (LTAGLIB_ATLEAST(LTAGLIB_1_10))

#if LTAGLIB_HAS_TABLEOFCONTENTSFRAME

#include "id3v2frame.h"
#include <tbytevectorlist.h>
#include <tableofcontentsframe.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_TableOfContentsFrame(lua_State* L);

}

namespace LuaTagLib {

    template<> const UserdataMetatable UserdataCommon<TagLib::ID3v2::TableOfContentsFrame>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::ID3v2::TableOfContentsFrame>::mod;

    namespace ID3v2 {
    typedef DerivedUserdata<TagLib::ID3v2::TableOfContentsFrame, Frame> TableOfContentsFrame;
} }

#endif

#endif
