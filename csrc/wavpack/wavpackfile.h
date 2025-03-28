#ifndef LTAGLIB_WAVPACK_FILE_INCLUDE_GUARD
#define LTAGLIB_WAVPACK_FILE_INCLUDE_GUARD

#include "../taglib.h"

#define LTAGLIB_HAS_WAVPACK_FILE (LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,5,0))

#if LTAGLIB_HAS_WAVPACK_FILE

#include "../tfile.h"
#include "../shared/userdata.h"
#include <wavpackfile.h>


extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_WavPack_File(lua_State *L);

LTAGLIB_PUBLIC
int luaopen_TagLib_WavPack_File_TagTypes(lua_State *L);

}

namespace LuaTagLib {

#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::WavPack::File>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::WavPack::File>::mod;
#endif 


    namespace WavPack {
        typedef DerivedUserdata<TagLib::WavPack::File, LuaTagLib::File> File;
    }
}

#endif

#endif
