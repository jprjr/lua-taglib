#ifndef LTAGLIB_ID3V2_POPULARIMETERFRAME_INCLUDE_GUARD
#define LTAGLIB_ID3V2_POPULARIMETERFRAME_INCLUDE_GUARD

#include "../taglib.h"

#define LTAGLIB_HAS_POPULARIMETERFRAME (LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,6,0))

#if LTAGLIB_HAS_POPULARIMETERFRAME

#include "id3v2frame.h"
#include <popularimeterframe.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_PopularimeterFrame(lua_State* L);

}

namespace LuaTagLib {

#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::ID3v2::PopularimeterFrame>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::ID3v2::PopularimeterFrame>::mod;
#endif 


    namespace ID3v2 {
    typedef DerivedUserdata<TagLib::ID3v2::PopularimeterFrame, Frame> PopularimeterFrame;
} }

#endif

#endif
