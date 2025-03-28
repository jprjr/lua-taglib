#include "aifffile.h"

#if LTAGLIB_HAS_RIFF_AIFF_FILE

#include "aiffproperties.h"
#include "../../id3v2/id3v2tag.h"
#include "../../tiostream.h"

#define T RIFF::AIFF::File
#define TT TagLib::T
#define XSTR(s) STR(s)
#define STR(s) #s
#define NAME XSTR(TT)

using namespace LuaTagLib;

static int File_tag(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    int args = lua_gettop(L);

    switch(args) {
        case 1: {
            ID3v2::Tag::pushPtr(L, f->tag(), 1);
            break;
        }
        default: {
            return luaL_error(L, "invalid arguments");
        }
    }
    return 1;
}


static int File_audioProperties(lua_State* L) {
   TT* f = T::checkPtr(L, 1);
   RIFF::AIFF::Properties::pushPtr(L, f->audioProperties(), 1);
   return 1;
}

#if LTAGLIB_ATLEAST(LTAGLIB_1_10)
/* this shows up in the headers for 1.9 but doesn't show up in the binary
 * until 1.10 */
static int File_hasID3v2Tag(lua_State* L) {
    lua_pushboolean(L, T::checkPtr(L,1)->hasID3v2Tag());
    return 1;
}
#endif

static
const luaL_Reg File__index[] = {
    { "tag", File_tag },
    { "audioProperties", File_audioProperties },
#if LTAGLIB_ATLEAST(LTAGLIB_1_10)
    { "hasID3v2Tag", File_hasID3v2Tag },
#endif
    { NULL, NULL }
};

#if LTAGLIB_ATLEAST(LTAGLIB_1_12)
static int
File_static_isSupported(lua_State* L) {
    lua_pushboolean(L, TagLib::RIFF::AIFF::File::isSupported(IOStream::checkPtr(L, 1)));
    return 1;
}
#endif

static
const luaL_Reg File__static[] = {
#if LTAGLIB_ATLEAST(LTAGLIB_1_12)
    { "isSupported", File_static_isSupported },
#endif
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_RIFF_AIFF_File(lua_State *L) {
    return T::open(L);
}

template<>
const UserdataTable T::base::mod = {
    File__call<T>,
    File__static,
    NULL,
};


template<>
const UserdataMetatable T::base::metatable = {
    NAME, /* name */
    File__index, /* indextable */
    NULL, /* indexfunc */
};

#undef T
#include "../../shared/userdata.tcc"
template class LuaTagLib::DerivedUserdata<TagLib::RIFF::AIFF::File, LuaTagLib::File>;

#endif
