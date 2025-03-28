#ifndef LTAGLIB_ID3V2_OWNERSHIPFRAME_INCLUDE_GUARD
#define LTAGLIB_ID3V2_OWNERSHIPFRAME_INCLUDE_GUARD

#include "../taglib.h"

#define LTAGLIB_HAS_OWNERSHIPFRAME (LTAGLIB_ATLEAST(LTAGLIB_1_8))

#if LTAGLIB_HAS_OWNERSHIPFRAME

#include "id3v2frame.h"
#include <ownershipframe.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_OwnershipFrame(lua_State* L);

}

namespace LuaTagLib {
#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::ID3v2::OwnershipFrame>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::ID3v2::OwnershipFrame>::mod;
#endif 

    namespace ID3v2 {
    typedef DerivedUserdata<TagLib::ID3v2::OwnershipFrame, Frame> OwnershipFrame;
} }

#endif

#endif
