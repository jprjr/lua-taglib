#include "asffile.h"

#if LTAGLIB_HAS_ASF

#include "asfproperties.h"
#include "asftag.h"
#include "../tiostream.h"

using namespace LuaTagLib;

static int File_tag(lua_State* L) {
   TagLib::ASF::File* f = ASF::File::checkPtr(L, 1);
   ASF::Tag::pushPtr(L, f->tag(), 1);
   return 1;
}

static int File_audioProperties(lua_State* L) {
   TagLib::ASF::File* f = ASF::File::checkPtr(L, 1);
   ASF::Properties::pushPtr(L, f->audioProperties(), 1);
   return 1;
}

static
const luaL_Reg File__index[] = {
    { "tag", File_tag },
    { "audioProperties", File_audioProperties },
    { NULL, NULL }
};

#if LTAGLIB_ATLEAST(LTAGLIB_1_12)
static int
File_static_isSupported(lua_State* L) {
    lua_pushboolean(L, TagLib::ASF::File::isSupported(IOStream::checkPtr(L, 1)));
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
int luaopen_TagLib_ASF_File(lua_State *L) {
    return ASF::File::open(L);
}

template<>
const UserdataTable ASF::File::base::mod = {
    File__call<ASF::File>,
    File__static,
    NULL,
};

template<>
const UserdataMetatable ASF::File::base::metatable = {
    "TagLib::ASF::File", /* name */
    File__index, /* indextable */
    NULL, /* indexfunc */
};

#include "../shared/userdata.tcc"
template class LuaTagLib::DerivedUserdata<TagLib::ASF::File, LuaTagLib::File>;

#endif
