#ifndef LTAGLIB_OGG_OPUS_FILE_INCLUDE_GUARD
#define LTAGLIB_OGG_OPUS_FILE_INCLUDE_GUARD

#include "../../taglib.h"

#include "../oggfile.h"
#include "../../shared/userdata.h"
#include <opusfile.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_Ogg_Opus_File(lua_State *L);

}

namespace LuaTagLib {

#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::Ogg::Opus::File>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::Ogg::Opus::File>::mod;
#endif 


    namespace Ogg { namespace Opus {
        typedef DerivedUserdata<TagLib::Ogg::Opus::File, LuaTagLib::Ogg::File> File;
    } }
}

#endif
