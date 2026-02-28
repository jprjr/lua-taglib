#ifndef LTAGLIB_OGG_FLAC_FILE_INCLUDE_GUARD
#define LTAGLIB_OGG_FLAC_FILE_INCLUDE_GUARD

#include "../../taglib.h"

#include "../../shared/userdata.h"
#include "../oggfile.h"
#include <oggflacfile.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_Ogg_FLAC_File(lua_State *L);

}

namespace LuaTagLib {

#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::Ogg::FLAC::File>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::Ogg::FLAC::File>::mod;
#endif 


    namespace Ogg { namespace FLAC {
        typedef DerivedUserdata<TagLib::Ogg::FLAC::File, LuaTagLib::Ogg::File> File;
    } }
}

#endif
