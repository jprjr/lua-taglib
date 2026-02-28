#include "shortenfile.h"

#include "shortenproperties.h"
#include "shortentag.h"
/* no check for LTAGLIB_HAS_IOSTREAM
 * since shorten support implies we're in v2.1+ */
#include "../tiostream.h"

using namespace LuaTagLib;

static int File_tag(lua_State* L) {
    TagLib::Shorten::File* f = Shorten::File::checkPtr(L, 1);
    int args = lua_gettop(L);

    switch(args) {
        case 1: {
            Shorten::Tag::pushPtr(L, f->tag(), 1);
            break;
        }
        default: {
            return luaL_error(L, "invalid arguments");
        }
    }
    return 1;
}

static int File_audioProperties(lua_State* L) {
   TagLib::Shorten::File* f = Shorten::File::checkPtr(L, 1);
   Shorten::Properties::pushPtr(L, f->audioProperties(), 1);
   return 1;
}

static int
File_static_isSupported(lua_State* L) {
    lua_pushboolean(L, TagLib::Shorten::File::isSupported(IOStream::checkPtr(L, 1)));
    return 1;
}

static
const luaL_Reg File__index[] = {
    { "tag", File_tag },
    { "audioProperties", File_audioProperties },
    { NULL, NULL }
};

static
const luaL_Reg File__static[] = {
    { "isSupported", File_static_isSupported },
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_Shorten_File(lua_State *L) {
    return Shorten::File::open(L);
}

template<>
const UserdataTable Shorten::File::base::mod = {
    File__call<Shorten::File>,
    File__static,
    NULL, /* submodules */
};

template<>
const UserdataMetatable Shorten::File::base::metatable = {
    "TagLib::Shorten::File", /* name */
    File__index, /* indextable */
    NULL, /* indexfunc */
};

#include "../shared/userdata.tcc"
template class LuaTagLib::DerivedUserdata<TagLib::Shorten::File, LuaTagLib::File>;
