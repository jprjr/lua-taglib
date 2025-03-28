#ifndef LTAGLIB_ID3V2_UNKNOWNFRAME_INCLUDE_GUARD
#define LTAGLIB_ID3V2_UNKNOWNFRAME_INCLUDE_GUARD

#include "id3v2frame.h"
#include <unknownframe.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_UnknownFrame(lua_State* L);

}

namespace LuaTagLib {
    template<> const UserdataMetatable UserdataCommon<TagLib::ID3v2::UnknownFrame>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::ID3v2::UnknownFrame>::mod;
    namespace ID3v2 {
    typedef DerivedUserdata<TagLib::ID3v2::UnknownFrame, Frame> UnknownFrame;
} }

#endif
