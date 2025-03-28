#ifndef LTAGLIB_S3M_FILE_INCLUDE_GUARD
#define LTAGLIB_S3M_FILE_INCLUDE_GUARD

#include "../taglib.h"

#define LTAGLIB_HAS_S3M_FILE (LTAGLIB_ATLEAST(LTAGLIB_1_8))

#if LTAGLIB_HAS_S3M_FILE

#include "../mod/modfilebase.h"
#include <s3mfile.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_S3M_File(lua_State *L);

}

namespace LuaTagLib {
#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::S3M::File>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::S3M::File>::mod;
#endif 

    namespace S3M {
        typedef DerivedUserdata<TagLib::S3M::File, LuaTagLib::Mod::FileBase> File;
    }
}

#endif

#endif
