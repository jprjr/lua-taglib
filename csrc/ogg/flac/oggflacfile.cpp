#include "oggflacfile.h"

#if LTAGLIB_HAS_OGGFLACFILE

#include "../xiphcomment.h"
#include "../../flac/flacproperties.h"
#include "../../tiostream.h"

#define T Ogg::FLAC::File
#define TT TagLib::T
#define XSTR(s) STR(s)
#define STR(s) #s
#define NAME XSTR(TT)

using namespace LuaTagLib;


#if LTAGLIB_ATLEAST(LTAGLIB_1_9)
static int File_hasXiphComment(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    lua_pushboolean(L, f->hasXiphComment());
    return 1;
}
#endif

static int File_tag(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    Ogg::XiphComment::pushPtr(L, f->tag(), 1);
    return 1;
}

static int File_audioProperties(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    LuaTagLib::FLAC::Properties::pushPtr(L, f->audioProperties(), 1);
    return 1;
}

static int File_streamLength(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    lua_pushinteger(L,f->streamLength());
    return 1;
}

static
const luaL_Reg File__index[] = {
#if LTAGLIB_ATLEAST(LTAGLIB_1_9)
    { "hasXiphComment", File_hasXiphComment },
#endif
    { "tag", File_tag },
    { "audioProperties", File_audioProperties },
    { "streamLength", File_streamLength },
    { NULL, NULL }
};


LTAGLIB_PUBLIC
int luaopen_TagLib_Ogg_FLAC_File(lua_State *L) {
    return T::open(L);
}

template<>
const UserdataTable T::base::mod = {
    File__call<T>,
    NULL,
    NULL
};

template<>
const UserdataMetatable T::base::metatable = {
    NAME, /* name */
    File__index, /* indextable */
    NULL, /* indexfunc */
};

#undef T
#include "../../shared/userdata.tcc"
template class DerivedUserdata<TagLib::Ogg::FLAC::File, LuaTagLib::Ogg::File>;

#endif
