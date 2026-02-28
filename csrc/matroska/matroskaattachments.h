#ifndef LTAGLIB_MATROSKA_ATTACHMENTS_INCLUDE_GUARD
#define LTAGLIB_MATROSKA_ATTACHMENTS_INCLUDE_GUARD

#include "../taglib.h"
#include "../shared/userdata.h"
#include <matroskaattachments.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_Matroska_Attachments(lua_State* L);

}

namespace LuaTagLib {

#ifndef _MSC_VER 
    template<> const UserdataMetatable UserdataCommon<TagLib::Matroska::Attachments>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::Matroska::Attachments>::mod;
#endif 

    namespace Matroska {
        typedef BaseUserdata<TagLib::Matroska::Attachments> Attachments;
    }
}

#endif

