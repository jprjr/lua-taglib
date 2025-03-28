#ifndef LTAGLIB_MP4_FILE_INCLUDE_GUARD
#define LTAGLIB_MP4_FILE_INCLUDE_GUARD

#include "mp4.h"

#if LTAGLIB_HAS_MP4

#include "../tfile.h"
#include "../shared/userdata.h"
#include <mp4file.h>


extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_MP4_File(lua_State *L);

LTAGLIB_PUBLIC
int luaopen_TagLib_MP4_File_TagTypes(lua_State *L);

}

namespace LuaTagLib {

#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::MP4::File>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::MP4::File>::mod;
#endif 


    namespace MP4 {
        typedef DerivedUserdata<TagLib::MP4::File, LuaTagLib::File> File;
    }
}

#endif

#endif
