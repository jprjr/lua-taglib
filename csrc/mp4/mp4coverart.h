#ifndef LTAGLIB_MP4_COVERART_INCLUDE_GUARD
#define LTAGLIB_MP4_COVERART_INCLUDE_GUARD

#include "mp4.h"

#define LTAGLIB_HAS_MP4_COVERART (LTAGLIB_HAS_MP4 && LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,7,0))

#if LTAGLIB_HAS_MP4_COVERART

#include "../shared/userdata.h"
#include "../shared/enum.h"
#include "../tlist.h"
#include "../tbytevector.h"
#include <mp4coverart.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_MP4_CoverArt(lua_State *L);

LTAGLIB_PUBLIC
int luaopen_TagLib_MP4_CoverArt_Format(lua_State *L);

}

namespace LuaTagLib { namespace MP4 {
    class LTAGLIB_PRIVATE CoverArt: public BaseUserdata<TagLib::MP4::CoverArt> {
        public:
            typedef Enum<TagLib::MP4::CoverArt::Format> Format;
    };
    typedef ValueList<TagLib::MP4::CoverArtList,CoverArt> CoverArtList;
} }

#endif

#endif
