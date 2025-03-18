#ifndef LTAGLIB_TRUEAUDIO_FILE_INCLUDE_GUARD
#define LTAGLIB_TRUEAUDIO_FILE_INCLUDE_GUARD

#include "../taglib.h"

#define LTAGLIB_HAS_TRUEAUDIO_FILE (LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,5,0))

#if LTAGLIB_HAS_TRUEAUDIO_FILE

#include "../tfile.h"
#include "../shared/userdata.h"
#include <trueaudiofile.h>


extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_TrueAudio_File(lua_State *L);

LTAGLIB_PUBLIC
int luaopen_TagLib_TrueAudio_File_TagTypes(lua_State *L);

}

namespace LuaTagLib { namespace TrueAudio {
    typedef DerivedUserdata<TagLib::TrueAudio::File, LuaTagLib::File> File;
} }

#endif

#endif
