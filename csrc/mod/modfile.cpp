#include "modfile.h"

#if LTAGLIB_HAS_MOD_FILE

#include "modproperties.h"
#include "modtag.h"
#include "../tiostream.h"

#define T Mod::File
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
    Mod::Properties::pushPtr(L, T::checkPtr(L,1)->audioProperties(), 1);
    return 1;
}

static
const luaL_Reg File__index[] = {
    { "tag", File_tag},
    { "audioProperties", File_audioProperties},
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_Mod_File(lua_State* L) {
    return Mod::File::open(L);
}

template<>
const UserdataTable Mod::File::base::mod = {
    File__call<T>,
    NULL,
    NULL
};


template<>
const UserdataMetatable Mod::File::base::metatable = {
    "TagLib::Mod::File", /* name */
    File__index, /* indextable */
    NULL, /* indexfunc */
};

#undef T
#include "../shared/userdata.tcc"
template class DerivedUserdata<TagLib::Mod::File, LuaTagLib::Mod::FileBase>;

#endif
