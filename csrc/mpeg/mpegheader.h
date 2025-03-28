#ifndef LTAGLIB_MPEG_HEADER_INCLUDE_GUARD
#define LTAGLIB_MPEG_HEADER_INCLUDE_GUARD

#include "../taglib.h"

#include "../shared/userdata.h"
#include "../shared/enum.h"
#include <mpegheader.h>

#define LTAGLIB_HAS_MPEG_HEADER_CHANNELCONFIGURATION (LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(2,0,0))

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_MPEG_Header(lua_State *L);

LTAGLIB_PUBLIC
int luaopen_TagLib_MPEG_Header_Version(lua_State *L);

LTAGLIB_PUBLIC
int luaopen_TagLib_MPEG_Header_ChannelMode(lua_State *L);

#if LTAGLIB_HAS_MPEG_HEADER_CHANNELCONFIGURATION

LTAGLIB_PUBLIC
int luaopen_TagLib_MPEG_Header_ChannelConfiguration(lua_State *L);

#endif

}

namespace LuaTagLib {

    template<> const UserdataMetatable UserdataCommon<TagLib::MPEG::Header>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::MPEG::Header>::mod;

    namespace MPEG {
    class LTAGLIB_PRIVATE Header: public BaseUserdata<TagLib::MPEG::Header> {
        public:
            typedef Enum<TagLib::MPEG::Header::Version> Version;
            typedef Enum<TagLib::MPEG::Header::ChannelMode> ChannelMode;
            #if LTAGLIB_HAS_MPEG_HEADER_CHANNELCONFIGURATION
            typedef Enum<TagLib::MPEG::Header::ChannelConfiguration> ChannelConfiguration;
            #endif
    };
} }

#endif


