#include "s3mfile.h"

#if LTAGLIB_HAS_S3M_FILE

#include "s3mproperties.h"
#include "../mod/modtag.h"
#include "../tiostream.h"

#define T S3M::File
#define TT TagLib::T
#define XSTR(s) STR(s)
#define STR(s) #s
#define NAME XSTR(TT)

using namespace LuaTagLib;

static int File_tag(lua_State* L) {
    Mod::Tag::pushPtr(L, T::checkPtr(L,1)->tag(), 1);
    return 1;
}

static int File_audioProperties(lua_State* L) {
    S3M::Properties::pushPtr(L, T::checkPtr(L,1)->audioProperties(), 1);
    return 1;
}

static
const luaL_Reg File__index[] = {
    { "tag", File_tag},
    { "audioProperties", File_audioProperties},
    { NULL, NULL }
};


LTAGLIB_PUBLIC
int luaopen_TagLib_S3M_File(lua_State* L) {
    return S3M::File::open(L);
}

template<>
const UserdataTable S3M::File::base::mod = {
    File__call<T>,
    NULL,
    NULL,
};

template<>
const UserdataMetatable S3M::File::base::metatable = {
    NAME, /* name */
    File__index, /* indextable */
    NULL, /* indexfunc */
};

#undef T
#include "../shared/userdata.tcc"
template class LuaTagLib::DerivedUserdata<TagLib::S3M::File, Mod::FileBase>;

#endif
