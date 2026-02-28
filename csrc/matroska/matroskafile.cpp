#include "matroskafile.h"

#include "matroskaproperties.h"
#include "matroskatag.h"
/* no check for LTAGLIB_HAS_IOSTREAM
 * since matroska support implies we're in v2.2+ */
#include "../tiostream.h"

using namespace LuaTagLib;

static int File_tag(lua_State* L) {
    TagLib::Matroska::File* f = Matroska::File::checkPtr(L, 1);
    int args = lua_gettop(L);

    switch(args) {
        case 1: {
            Tag::pushPtr(L, f->tag(), 1);
            break;
        }
        case 2: {
            Matroska::Tag::pushPtr(L, f->tag((bool)lua_toboolean(L,2)), 1);
            break;
        }
        default: {
            return luaL_error(L, "invalid arguments");
        }
    }
    return 1;
}

static int File_audioProperties(lua_State* L) {
   TagLib::Matroska::File* f = Matroska::File::checkPtr(L, 1);
   Matroska::Properties::pushPtr(L, f->audioProperties(), 1);
   return 1;
}

static int
File_static_isSupported(lua_State* L) {
    lua_pushboolean(L, TagLib::Matroska::File::isSupported(IOStream::checkPtr(L, 1)));
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
int luaopen_TagLib_Matroska_File(lua_State *L) {
    return Matroska::File::open(L);
}

template<>
const UserdataTable Matroska::File::base::mod = {
    File__call<Matroska::File>,
    File__static,
    NULL, /* submodules */
};

template<>
const UserdataMetatable Matroska::File::base::metatable = {
    "TagLib::Matroska::File", /* name */
    File__index, /* indextable */
    NULL, /* indexfunc */
};

#include "../shared/userdata.tcc"
template class LuaTagLib::DerivedUserdata<TagLib::Matroska::File, LuaTagLib::File>;
