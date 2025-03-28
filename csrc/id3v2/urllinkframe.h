#ifndef LTAGLIB_ID3V2_URLLINKFRAME_INCLUDE_GUARD
#define LTAGLIB_ID3V2_URLLINKFRAME_INCLUDE_GUARD

#include "../taglib.h"

#define LTAGLIB_HAS_URLLINKFRAME (LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,5,0))

#if LTAGLIB_HAS_URLLINKFRAME

#include "id3v2frame.h"
#include <urllinkframe.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_UrlLinkFrame(lua_State* L);

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_UserUrlLinkFrame(lua_State* L);

}

namespace LuaTagLib {

    template<> const UserdataMetatable UserdataCommon<TagLib::ID3v2::UrlLinkFrame>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::ID3v2::UrlLinkFrame>::mod;

    template<> const UserdataMetatable UserdataCommon<TagLib::ID3v2::UserUrlLinkFrame>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::ID3v2::UserUrlLinkFrame>::mod;

    namespace ID3v2 {
    typedef DerivedUserdata<TagLib::ID3v2::UrlLinkFrame, Frame> UrlLinkFrame;
    typedef DerivedUserdata<TagLib::ID3v2::UserUrlLinkFrame, UrlLinkFrame> UserUrlLinkFrame;
} }

#endif

#endif
