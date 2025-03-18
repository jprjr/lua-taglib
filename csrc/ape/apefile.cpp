#include "apefile.h"

#if LTAGLIB_HAS_APE_FILE

#include "apetag.h"
#include "apeproperties.h"
#include "../id3v1/id3v1tag.h"
#include "../tiostream.h"

using namespace LuaTagLib;

#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,9,0)
static int File_hasID3v1Tag(lua_State* L) {
    TagLib::APE::File* f = APE::File::checkPtr(L, 1);
    lua_pushboolean(L, f->hasID3v1Tag());
    return 1;
}

static int File_hasAPETag(lua_State* L) {
    TagLib::APE::File* f = APE::File::checkPtr(L, 1);
    lua_pushboolean(L, f->hasAPETag());
    return 1;
}
#endif

static int File_audioProperties(lua_State* L) {
    TagLib::APE::File* f = APE::File::checkPtr(L, 1);
    APE::Properties::pushPtr(L, f->audioProperties(), 1);
    return 1;
}

static int File_ID3v1Tag(lua_State* L) {
    int args = lua_gettop(L);
    TagLib::APE::File* f = APE::File::checkPtr(L, 1);

    switch(args) {
        case 1: {
            ID3v1::Tag::pushPtr(L, f->ID3v1Tag(), 1);
            break;
        }
        case 2: {
            ID3v1::Tag::pushPtr(L, f->ID3v1Tag( (bool) lua_toboolean(L, 2)), 1);
            break;
        }
        default: {
            return luaL_error(L, "invalid arguments");
        }
    }
    return 1;
}

static int File_APETag(lua_State* L) {
    int args = lua_gettop(L);
    TagLib::APE::File* f = APE::File::checkPtr(L, 1);

    switch(args) {
        case 1: {
            APE::Tag::pushPtr(L, f->APETag(), 1);
            break;
        }
        case 2: {
            APE::Tag::pushPtr(L, f->APETag( (bool) lua_toboolean(L, 2)), 1);
            break;
        }
        default: {
            return luaL_error(L, "invalid arguments");
        }
    }
    return 1;
}

static int File_strip(lua_State* L) {
    TagLib::APE::File* f = APE::File::checkPtr(L, 1);
    int args = lua_gettop(L);

    switch(args) {
        case 1: {
            f->strip();
            break;
        }
        case 2: {
            f->strip(luaL_checkinteger(L, 2));
            break;
        }
        default: {
            return luaL_error(L, "invalid arguments");
        }
    }

    lua_settop(L,1);
    return 1;
}

static
const luaL_Reg File__index[] = {
#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,9,0)
    { "hasID3v1Tag", File_hasID3v1Tag },
    { "hasAPETag", File_hasAPETag },
#endif
    { "audioProperties", File_audioProperties },
    { "ID3v1Tag", File_ID3v1Tag },
    { "APETag", File_APETag },
    { "strip", File_strip },
    { NULL, NULL }
};


LTAGLIB_PUBLIC
int luaopen_TagLib_APE_File_TagTypes(lua_State *L) {
    lua_newtable(L);

    lua_pushinteger(L, TagLib::APE::File::NoTags);
    lua_setfield(L, -2, "NoTags");

    lua_pushinteger(L, TagLib::APE::File::ID3v1);
    lua_setfield(L, -2, "ID3v1");

    lua_pushinteger(L, TagLib::APE::File::APE);
    lua_setfield(L, -2, "APE");

    lua_pushinteger(L, TagLib::APE::File::AllTags);
    lua_setfield(L, -2, "AllTags");

    return 1;
}

static int File__submodules(lua_State* L) {
    luaL_requiref(L, "TagLib.APE.File.TagTypes", luaopen_TagLib_APE_File_TagTypes, 0);
    lua_setfield(L, -2, "TagTypes");
    return 0;
}

template<>
const UserdataTable APE::File::base::mod = {
    File__call<APE::File>,
    NULL,
    File__submodules,
};

LTAGLIB_PUBLIC
int luaopen_TagLib_APE_File(lua_State *L) {
    return APE::File::open(L);
}

template<>
const UserdataMetatable APE::File::base::metatable = {
    "TagLib::APE::File", /* name */
    File__index, /* indextable */
    NULL, /* indexfunc */
};

#include "../shared/userdata.tcc"
template class DerivedUserdata<TagLib::APE::File, LuaTagLib::File>;

#endif
