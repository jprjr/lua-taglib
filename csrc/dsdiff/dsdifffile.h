#ifndef LTAGLIB_DSDIFF_FILE_INCLUDE_GUARD
#define LTAGLIB_DSDIFF_FILE_INCLUDE_GUARD

#include "../taglib.h"

#define LTAGLIB_HAS_DSDIFF_FILE (LTAGLIB_ATLEAST(LTAGLIB_2_0))

#if LTAGLIB_HAS_DSDIFF_FILE

#include "../tfile.h"
#include "../shared/userdata.h"
#include <dsdifffile.h>


extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_DSDIFF_File(lua_State *L);

LTAGLIB_PUBLIC
int luaopen_TagLib_DSDIFF_File_TagTypes(lua_State *L);

}

namespace LuaTagLib {
    template<> const UserdataMetatable UserdataCommon<TagLib::DSDIFF::File>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::DSDIFF::File>::mod;

    namespace DSDIFF {
        typedef DerivedUserdata<TagLib::DSDIFF::File, LuaTagLib::File> File;
    }
}

#endif

#endif
