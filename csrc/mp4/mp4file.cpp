#include "mp4file.h"

#if LTAGLIB_HAS_MP4

#include "mp4properties.h"
#include "mp4tag.h"
#include "../tiostream.h"

using namespace LuaTagLib;

static int File_tag(lua_State* L) {
    TagLib::MP4::File* f = MP4::File::checkPtr(L, 1);
    int args = lua_gettop(L);

    switch(args) {
        case 1: {
            MP4::Tag::pushPtr(L, f->tag(), 1);
            break;
        }
        default: {
            return luaL_error(L, "invalid arguments");
        }
    }
    return 1;
}

static int File_audioProperties(lua_State* L) {
   TagLib::MP4::File* f = MP4::File::checkPtr(L, 1);
   MP4::Properties::pushPtr(L, f->audioProperties(), 1);
   return 1;
}

#if LTAGLIB_ATLEAST(LTAGLIB_1_11)
static int File_hasMP4Tag(lua_State* L) {
    lua_pushboolean(L, MP4::File::checkPtr(L,1)->hasMP4Tag());
    return 1;
}
#endif

#if LTAGLIB_ATLEAST(LTAGLIB_1_13)
static int File_strip(lua_State* L) {
    int args = lua_gettop(L);
    switch(args) {
        case 1: {
            lua_pushboolean(L, MP4::File::checkPtr(L,1)->strip());
            return 1;
        }
        case 2: {
            lua_pushboolean(L, MP4::File::checkPtr(L,1)->strip(luaL_checkinteger(L,2)));
            return 1;
        }
        default: break;
    }
    return luaL_error(L, "invalid arguments");
}
#endif

static
const luaL_Reg File__index[] = {
    { "tag", File_tag },
    { "audioProperties", File_audioProperties },
#if LTAGLIB_ATLEAST(LTAGLIB_1_11)
    { "hasMP4Tag", File_hasMP4Tag },
#endif
#if LTAGLIB_ATLEAST(LTAGLIB_1_13)
    { "strip", File_strip },
#endif
    { NULL, NULL }
};

static int File__submodules(lua_State* L) {
#if LTAGLIB_ATLEAST(LTAGLIB_1_13)
    luaL_requiref(L, "TagLib.MP4.File.TagTypes",
      luaopen_TagLib_MP4_File_TagTypes, 0);
    lua_setfield(L, -2, "TagTypes");
#else
    (void)L;
#endif
    return 0;
}

LTAGLIB_PUBLIC
int luaopen_TagLib_MP4_File(lua_State *L) {
    return MP4::File::open(L);
}

#if LTAGLIB_ATLEAST(LTAGLIB_1_13)
LTAGLIB_PUBLIC
int luaopen_TagLib_MP4_File_TagTypes(lua_State *L) {
    lua_newtable(L);

    lua_pushinteger(L, TagLib::MP4::File::NoTags);
    lua_setfield(L, -2, "NoTags");

    lua_pushinteger(L, TagLib::MP4::File::MP4);
    lua_setfield(L, -2, "MP4");

    lua_pushinteger(L, TagLib::MP4::File::AllTags);
    lua_setfield(L, -2, "AllTags");

    return 1;
}
#endif

template<>
const UserdataTable MP4::File::base::mod = {
    File__call<MP4::File>,
    NULL,
    File__submodules,
};

template<>
const UserdataMetatable MP4::File::base::metatable = {
    "TagLib::MP4::File", /* name */
    File__index, /* indextable */
    NULL, /* indexfunc */
};

#include "../shared/userdata.tcc"
template class DerivedUserdata<TagLib::MP4::File, LuaTagLib::File>;

#endif
