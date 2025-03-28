#ifndef LTAGLIB_ID3V2_EVENTTIMINGCODESFRAME_INCLUDE_GUARD
#define LTAGLIB_ID3V2_EVENTTIMINGCODESFRAME_INCLUDE_GUARD

#include "../taglib.h"

#define LTAGLIB_HAS_EVENTTIMINGCODESFRAME (LTAGLIB_ATLEAST(LTAGLIB_1_10))

#if LTAGLIB_HAS_EVENTTIMINGCODESFRAME

#include "../shared/enum.h"
#include "id3v2frame.h"
#include <eventtimingcodesframe.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_EventTimingCodesFrame(lua_State* L);

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_EventTimingCodesFrame_EventType(lua_State* L);

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_EventTimingCodesFrame_TimestampFormat(lua_State* L);

}

namespace LuaTagLib {

#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::ID3v2::EventTimingCodesFrame>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::ID3v2::EventTimingCodesFrame>::mod;
#endif 


    namespace ID3v2 {
    class LTAGLIB_PRIVATE EventTimingCodesFrame: public DerivedUserdata<TagLib::ID3v2::EventTimingCodesFrame, Frame> {
        public:
            typedef Enum<TagLib::ID3v2::EventTimingCodesFrame::EventType> EventType;
            typedef Enum<TagLib::ID3v2::EventTimingCodesFrame::TimestampFormat> TimestampFormat;
    };
} }

#endif

#endif
