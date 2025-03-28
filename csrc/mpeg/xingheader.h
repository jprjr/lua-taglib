#ifndef LTAGLIB_MPEG_XINGHEADER_INCLUDE_GUARD
#define LTAGLIB_MPEG_XINGHEADER_INCLUDE_GUARD

#include "../taglib.h"
#include "../shared/userdata.h"
#include <xingheader.h>

#define LTAGLIB_HAS_MPEG_XINGHEADER_TYPE (LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,10,0))

#if LTAGLIB_HAS_MPEG_XINGHEADER_TYPE
#include "../shared/enum.h"
#endif

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_MPEG_XingHeader(lua_State* L);

#if LTAGLIB_HAS_MPEG_XINGHEADER_TYPE
LTAGLIB_PUBLIC
int luaopen_TagLib_MPEG_XingHeader_HeaderType(lua_State* L);
#endif

}


namespace LuaTagLib {
    template<> const UserdataMetatable UserdataCommon<TagLib::MPEG::XingHeader>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::MPEG::XingHeader>::mod;
    namespace MPEG {
    class LTAGLIB_PRIVATE XingHeader: public BaseUserdata<TagLib::MPEG::XingHeader> {
        public:
#if LTAGLIB_HAS_MPEG_XINGHEADER_TYPE
            typedef Enum<TagLib::MPEG::XingHeader::HeaderType> HeaderType;
#endif
    };
} }

#endif
