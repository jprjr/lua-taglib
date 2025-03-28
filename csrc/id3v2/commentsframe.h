#ifndef LTAGLIB_ID3V2_COMMENTSFRAME_INCLUDE_GUARD
#define LTAGLIB_ID3V2_COMMENTSFRAME_INCLUDE_GUARD

#include "id3v2frame.h"
#include <commentsframe.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_CommentsFrame(lua_State* L);

}

namespace LuaTagLib {
    template<> const UserdataMetatable UserdataCommon<TagLib::ID3v2::CommentsFrame>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::ID3v2::CommentsFrame>::mod;
    namespace ID3v2 {
        typedef DerivedUserdata<TagLib::ID3v2::CommentsFrame, Frame> CommentsFrame;
    }
}

#endif
