#include "speexfile.h"

#if LTAGLIB_HAS_SPEEXFILE

#include "../xiphcomment.h"
#include "speexproperties.h"
#include "../../tiostream.h"

#define T Ogg::Speex::File
#define TT TagLib::T
#define XSTR(s) STR(s)
#define STR(s) #s
#define NAME XSTR(TT)

using namespace LuaTagLib;

static int File_tag(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    Ogg::XiphComment::pushPtr(L, f->tag(), 1);
    return 1;
}

static int File_audioProperties(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    Ogg::Speex::Properties::pushPtr(L, f->audioProperties(), 1);
    return 1;
}

static
const luaL_Reg File__index[] = {
    { "tag", File_tag },
    { "audioProperties", File_audioProperties },
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_Ogg_Speex_File(lua_State *L) {
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
template class LuaTagLib::DerivedUserdata<TagLib::Ogg::Speex::File, LuaTagLib::Ogg::File>;

#endif
