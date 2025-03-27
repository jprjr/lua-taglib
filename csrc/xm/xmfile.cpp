#include "xmfile.h"

#if LTAGLIB_HAS_XM_FILE

#include "xmproperties.h"
#include "../mod/modtag.h"
#include "../tiostream.h"

#define T XM::File
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
    XM::Properties::pushPtr(L, T::checkPtr(L,1)->audioProperties(), 1);
    return 1;
}

static
const luaL_Reg File__index[] = {
    { "tag", File_tag},
    { "audioProperties", File_audioProperties},
    { NULL, NULL }
};


LTAGLIB_PUBLIC
int luaopen_TagLib_XM_File(lua_State* L) {
    return XM::File::open(L);
}

template<>
const UserdataTable T::base::mod = {
    File__call<T>,
    NULL,
    NULL,
};

template<>
const UserdataMetatable XM::File::base::metatable = {
    NAME, /* name */
    File__index, /* indextable */
    NULL, /* indexfunc */
};

#undef T
#include "../shared/userdata.tcc"
template class LuaTagLib::DerivedUserdata<TagLib::XM::File, Mod::FileBase>;

#endif
