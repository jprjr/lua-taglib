#ifndef LTAGLIB_RIFF_AIFF_FILE_INCLUDE_GUARD
#define LTAGLIB_RIFF_AIFF_FILE_INCLUDE_GUARD

#include "../../taglib.h"

#define LTAGLIB_HAS_RIFF_AIFF_FILE (LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,6,0))

#if LTAGLIB_HAS_RIFF_AIFF_FILE

#include "../../tfile.h"
#include "../../shared/userdata.h"
#include <aifffile.h>


extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_RIFF_AIFF_File(lua_State *L);

LTAGLIB_PUBLIC
int luaopen_TagLib_RIFF_AIFF_File_TagTypes(lua_State *L);

}

namespace LuaTagLib {

#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::RIFF::AIFF::File>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::RIFF::AIFF::File>::mod;
#endif 


    namespace RIFF { namespace AIFF {
        typedef DerivedUserdata<TagLib::RIFF::AIFF::File, LuaTagLib::File> File;
    } }
}

#endif

#endif
