#ifndef LTAGLIB_MPEG_FILE_INCLUDE_GUARD
#define LTAGLIB_MPEG_FILE_INCLUDE_GUARD

#include "../taglib.h"
#include "../tfile.h"
#include "../shared/userdata.h"
#include "../shared/enum.h"
#include <mpegfile.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_MPEG_File(lua_State *L);

LTAGLIB_PUBLIC
int luaopen_TagLib_MPEG_File_TagTypes(lua_State *L);

}

namespace LuaTagLib {

    template<> const UserdataMetatable UserdataCommon<TagLib::MPEG::File>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::MPEG::File>::mod;

    namespace MPEG {
    class LTAGLIB_PRIVATE File: public DerivedUserdata<TagLib::MPEG::File, LuaTagLib::File> {
        public:
#if LTAGLIB_HAS_FILE_STRIPTAGS
            class LTAGLIB_PRIVATE StripTags: public LuaTagLib::File::StripTags { };
#endif
#if LTAGLIB_HAS_FILE_DUPLICATETAGS
            class LTAGLIB_PRIVATE DuplicateTags: public LuaTagLib::File::DuplicateTags { };
#endif
    };
} }

#endif


