#ifndef LTAGLIB_ID3V2_PRIVATEFRAME_INCLUDE_GUARD
#define LTAGLIB_ID3V2_PRIVATEFRAME_INCLUDE_GUARD

#include "../taglib.h"

#define LTAGLIB_HAS_PRIVATEFRAME (LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,6,0))

#if LTAGLIB_HAS_PRIVATEFRAME

#include "id3v2frame.h"
#include <privateframe.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_PrivateFrame(lua_State* L);

}

namespace LuaTagLib {

#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::ID3v2::PrivateFrame>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::ID3v2::PrivateFrame>::mod;
#endif 


    namespace ID3v2 {
    typedef DerivedUserdata<TagLib::ID3v2::PrivateFrame, Frame> PrivateFrame;
} }

#endif

#endif
