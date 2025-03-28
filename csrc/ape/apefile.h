#ifndef LTAGLIB_APE_FILE_INCLUDE_GUARD
#define LTAGLIB_APE_FILE_INCLUDE_GUARD

#include "../taglib.h"

#define LTAGLIB_HAS_APE_FILE (LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,7,0))

#if LTAGLIB_HAS_APE_FILE

#include "../tfile.h"
#include "../shared/userdata.h"
#include <apefile.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_APE_File(lua_State *L);

LTAGLIB_PUBLIC
int luaopen_TagLib_APE_File_TagTypes(lua_State *L);

}

namespace LuaTagLib {

    template<> const UserdataMetatable UserdataCommon<TagLib::APE::File>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::APE::File>::mod;

    namespace APE {
        typedef DerivedUserdata<TagLib::APE::File, LuaTagLib::File> File;
    }
}

#endif

#endif

