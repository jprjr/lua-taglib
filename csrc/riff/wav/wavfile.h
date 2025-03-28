#ifndef LTAGLIB_RIFF_WAV_FILE_INCLUDE_GUARD
#define LTAGLIB_RIFF_WAV_FILE_INCLUDE_GUARD

#include "../../taglib.h"

#define LTAGLIB_HAS_RIFF_WAV_FILE (LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,6,0))

#if LTAGLIB_HAS_RIFF_WAV_FILE

#include "../../tfile.h"
#include "../../shared/userdata.h"
#include <wavfile.h>


extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_RIFF_WAV_File(lua_State *L);

#if LTAGLIB_ATLEAST(LTAGLIB_1_9)
LTAGLIB_PUBLIC
int luaopen_TagLib_RIFF_WAV_File_TagTypes(lua_State *L);
#endif

}

namespace LuaTagLib {

    template<> const UserdataMetatable UserdataCommon<TagLib::RIFF::WAV::File>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::RIFF::WAV::File>::mod;

    namespace RIFF { namespace WAV {
        typedef DerivedUserdata<TagLib::RIFF::WAV::File, LuaTagLib::File> File;
    }
} }

#endif

#endif
