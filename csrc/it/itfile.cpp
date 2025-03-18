#include "itfile.h"

#if LTAGLIB_HAS_IT_FILE

#include "itproperties.h"
#include "../mod/modtag.h"
#include "../tiostream.h"

#define T IT::File
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
    IT::Properties::pushPtr(L, T::checkPtr(L,1)->audioProperties(), 1);
    return 1;
}

static
const luaL_Reg File__index[] = {
    { "tag", File_tag},
    { "audioProperties", File_audioProperties},
    { NULL, NULL }
};


LTAGLIB_PUBLIC
int luaopen_TagLib_IT_File(lua_State* L) {
    return IT::File::open(L);
}

template<>
const UserdataTable IT::File::base::mod = {
    File__call<T>,
    NULL,
    NULL,
};


template<>
const UserdataMetatable IT::File::base::metatable = {
    NAME, /* name */
    File__index, /* indextable */
    NULL, /* indexfunc */
};

#undef T
#include "../shared/userdata.tcc"
template class DerivedUserdata<TagLib::IT::File, Mod::FileBase>;

#endif
