#ifndef LTAGLIB_ID3V2_TEXTIDENTIFICATIONFRAME_INCLUDE_GUARD
#define LTAGLIB_ID3V2_TEXTIDENTIFICATIONFRAME_INCLUDE_GUARD

#include "id3v2frame.h"
#include <textidentificationframe.h>

#define LTAGLIB_HAS_USERTEXTIDENTIFICATIONFRAME (LTAGLIB_ATLEAST(LTAGLIB_1_3))

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_TextIdentificationFrame(lua_State* L);

#if LTAGLIB_HAS_USERTEXTIDENTIFICATIONFRAME

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_UserTextIdentificationFrame(lua_State* L);

#endif

}

namespace LuaTagLib {

#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::ID3v2::TextIdentificationFrame>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::ID3v2::TextIdentificationFrame>::mod;
#endif 

#if LTAGLIB_HAS_USERTEXTIDENTIFICATIONFRAME
#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::ID3v2::UserTextIdentificationFrame>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::ID3v2::UserTextIdentificationFrame>::mod;
#endif 

#endif

    namespace ID3v2 {
    typedef DerivedUserdata<TagLib::ID3v2::TextIdentificationFrame, Frame> TextIdentificationFrame;
#if LTAGLIB_HAS_USERTEXTIDENTIFICATIONFRAME
    typedef DerivedUserdata<TagLib::ID3v2::UserTextIdentificationFrame, TextIdentificationFrame> UserTextIdentificationFrame;
#endif

} }

#endif
