#ifndef LTAGLIB_ID3V2_GENERALENCAPSULATEDOBJECTFRAME_INCLUDE_GUARD
#define LTAGLIB_ID3V2_GENERALENCAPSULATEDOBJECTFRAME_INCLUDE_GUARD

#include "../taglib.h"

#define LTAGLIB_HAS_GENERALENCAPSULATEDOBJECTFRAME (LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,5,0))

#if LTAGLIB_HAS_GENERALENCAPSULATEDOBJECTFRAME

#include "id3v2frame.h"
#include <generalencapsulatedobjectframe.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_GeneralEncapsulatedObjectFrame(lua_State* L);

}

namespace LuaTagLib { namespace ID3v2 {
    typedef DerivedUserdata<TagLib::ID3v2::GeneralEncapsulatedObjectFrame, Frame> GeneralEncapsulatedObjectFrame;
} }

#endif

#endif
