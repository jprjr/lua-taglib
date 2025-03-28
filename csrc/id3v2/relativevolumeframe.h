#ifndef LTAGLIB_ID3V2_RELATIVEVOLUMEFRAME_INCLUDE_GUARD
#define LTAGLIB_ID3V2_RELATIVEVOLUMEFRAME_INCLUDE_GUARD

#include "../taglib.h"

#define LTAGLIB_HAS_RELATIVEVOLUMEFRAME (LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,2,0))

#if LTAGLIB_HAS_RELATIVEVOLUMEFRAME

#include "id3v2frame.h"
#include "../shared/enum.h"
#include <relativevolumeframe.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_RelativeVolumeFrame(lua_State* L);

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_RelativeVolumeFrame_ChannelType(lua_State* L);

}

namespace LuaTagLib {

#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::ID3v2::RelativeVolumeFrame>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::ID3v2::RelativeVolumeFrame>::mod;
#endif 


    namespace ID3v2 {
    class LTAGLIB_PRIVATE RelativeVolumeFrame: public DerivedUserdata<TagLib::ID3v2::RelativeVolumeFrame, Frame> {
        public:
            typedef Enum<TagLib::ID3v2::RelativeVolumeFrame::ChannelType> ChannelType;
    };
} }

#endif

#endif
