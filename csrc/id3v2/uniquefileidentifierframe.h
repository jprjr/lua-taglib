#ifndef LTAGLIB_ID3V2_UNIQUEFILEIDENTIFIERFRAME_INCLUDE_GUARD
#define LTAGLIB_ID3V2_UNIQUEFILEIDENTIFIERFRAME_INCLUDE_GUARD

#include "../taglib.h"

#define LTAGLIB_HAS_UNIQUEFILEIDENTIFIERFRAME (LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,3,0))

#if LTAGLIB_HAS_UNIQUEFILEIDENTIFIERFRAME

#include "id3v2frame.h"
#include <uniquefileidentifierframe.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_UniqueFileIdentifierFrame(lua_State* L);

}

namespace LuaTagLib {

    template<> const UserdataMetatable UserdataCommon<TagLib::ID3v2::UniqueFileIdentifierFrame>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::ID3v2::UniqueFileIdentifierFrame>::mod;

    namespace ID3v2 {
    typedef DerivedUserdata<TagLib::ID3v2::UniqueFileIdentifierFrame, Frame> UniqueFileIdentifierFrame;
} }

#endif

#endif
