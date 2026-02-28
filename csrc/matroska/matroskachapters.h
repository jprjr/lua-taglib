#ifndef LTAGLIB_MATROSKA_CHAPTERS_INCLUDE_GUARD
#define LTAGLIB_MATROSKA_CHAPTERS_INCLUDE_GUARD

#include "../taglib.h"
#include "../shared/userdata.h"
#include <matroskachapters.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_Matroska_Chapters(lua_State* L);

}

namespace LuaTagLib {

#ifndef _MSC_VER 
    template<> const UserdataMetatable UserdataCommon<TagLib::Matroska::Chapters>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::Matroska::Chapters>::mod;
#endif 

    namespace Matroska {
        typedef BaseUserdata<TagLib::Matroska::Chapters> Chapters;
    }
}

#endif

