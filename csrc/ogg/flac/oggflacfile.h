#ifndef LTAGLIB_OGG_FLAC_FILE_INCLUDE_GUARD
#define LTAGLIB_OGG_FLAC_FILE_INCLUDE_GUARD

#include "../../taglib.h"

#define LTAGLIB_HAS_OGGFLACFILE (LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,2,0))

#if LTAGLIB_HAS_OGGFLACFILE

#include "../../shared/userdata.h"
#include "../oggfile.h"
#include <oggflacfile.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_Ogg_FLAC_File(lua_State *L);

}

namespace LuaTagLib {

    template<> const UserdataMetatable UserdataCommon<TagLib::Ogg::FLAC::File>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::Ogg::FLAC::File>::mod;

    namespace Ogg { namespace FLAC {
        typedef DerivedUserdata<TagLib::Ogg::FLAC::File, LuaTagLib::Ogg::File> File;
    } }
}

#endif

#endif
