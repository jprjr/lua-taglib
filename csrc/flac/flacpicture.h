#ifndef LTAGLIB_FLAC_PICTURE_INCLUDE_GUARD
#define LTAGLIB_FLAC_PICTURE_INCLUDE_GUARD

#include "../taglib.h"

#define LTAGLIB_HAS_FLAC_PICTURE (LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,7,0))

#if LTAGLIB_HAS_FLAC_PICTURE

#include "../shared/userdata.h"
#include "../shared/enum.h"
#include "flacmetadatablock.h"
#include <flacpicture.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_FLAC_Picture(lua_State *L);

LTAGLIB_PUBLIC
int luaopen_TagLib_FLAC_Picture_Type(lua_State *L);

}

namespace LuaTagLib { namespace FLAC {
    class LTAGLIB_PRIVATE Picture: public DerivedUserdata<TagLib::FLAC::Picture, FLAC::MetadataBlock> {
        public:
            typedef Enum<TagLib::FLAC::Picture::Type> Type;
    };
} }

#endif

#endif
