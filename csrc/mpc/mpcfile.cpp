#include "mpcfile.h"

#if LTAGLIB_HAS_MPC_FILE

#include "mpcproperties.h"

#include "../tlist.h"
#include "../id3v1/id3v1tag.h"
#include "../ape/apetag.h"
#include "../tiostream.h"

using namespace LuaTagLib;

static int File_ID3v1Tag(lua_State* L) {
    TagLib::MPC::File* f = MPC::File::checkPtr(L, 1);
    int args = lua_gettop(L);

    switch(args) {
        case 1: {
            ID3v1::Tag::pushPtr(L, f->ID3v1Tag(), 1);
            break;
        }
        case 2: {
            ID3v1::Tag::pushPtr(L, f->ID3v1Tag((bool) lua_toboolean(L, 2)), 1);
            break;
        }
        default: return luaL_error(L, "invalid arguments");
    }

    return 1;
}

static int File_APETag(lua_State* L) {
    TagLib::MPC::File* f = MPC::File::checkPtr(L, 1);
    int args = lua_gettop(L);

    switch(args) {
        case 1: {
            APE::Tag::pushPtr(L, f->APETag(), 1);
            break;
        }
        case 2: {
            APE::Tag::pushPtr(L, f->APETag((bool) lua_toboolean(L, 2)), 1);
            break;
        }
        default: {
            return luaL_error(L, "invalid arguments");
        }
    }
    return 1;
}

#if LTAGLIB_UNDER(LTAGLIB_1_12)
static int File_remove(lua_State* L) {
    TagLib::MPC::File* f = MPC::File::checkPtr(L, 1);

    switch(lua_gettop(L)) {
        case 1: {
            f->remove();
            break;
        }
        case 2: {
            f->remove(luaL_checkinteger(L, 2));
            break;
        }
        default: {
            return luaL_error(L, "invalid arguments");
        }
    }

    lua_settop(L,1);
    return 1;
}
#endif

#if LTAGLIB_ATLEAST(LTAGLIB_1_5)
static int File_strip(lua_State* L) {
    TagLib::MPC::File* f = MPC::File::checkPtr(L, 1);

    switch(lua_gettop(L)) {
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
#endif

static int File_audioProperties(lua_State* L) {
   TagLib::MPC::File* f = MPC::File::checkPtr(L, 1);
   MPC::Properties::pushPtr(L, f->audioProperties(), 1);
   return 1;
}

#if LTAGLIB_ATLEAST(LTAGLIB_1_9)
static int File_hasID3v1Tag(lua_State* L) {
    lua_pushboolean(L, MPC::File::checkPtr(L,1)->hasID3v1Tag());
    return 1;
}

static int File_hasAPETag(lua_State* L) {
    lua_pushboolean(L, MPC::File::checkPtr(L,1)->hasAPETag());
    return 1;
}
#endif

static
const luaL_Reg File__index[] = {
    { "ID3v1Tag", File_ID3v1Tag },
    { "APETag", File_APETag },
#if LTAGLIB_UNDER(LTAGLIB_1_12)
    { "remove", File_remove },
#endif
    { "audioProperties", File_audioProperties },
#if LTAGLIB_ATLEAST(LTAGLIB_1_5)
    { "strip", File_strip },
#endif
#if LTAGLIB_ATLEAST(LTAGLIB_1_9)
    { "hasID3v1Tag", File_hasID3v1Tag},
    { "hasAPETag", File_hasAPETag},
#endif
    { NULL, NULL }
};

static int File__submodules(lua_State* L) {
    luaL_requiref(L, "TagLib.MPC.File.TagTypes", luaopen_TagLib_MPC_File_TagTypes, 0);
    lua_setfield(L, -2, "TagTypes");
    return 0;
}

LTAGLIB_PUBLIC
int luaopen_TagLib_MPC_File_TagTypes(lua_State *L) {
    lua_newtable(L);

    lua_pushinteger(L, TagLib::MPC::File::NoTags);
    lua_setfield(L, -2, "NoTags");

    lua_pushinteger(L, TagLib::MPC::File::ID3v1);
    lua_setfield(L, -2, "ID3v1");

    lua_pushinteger(L, TagLib::MPC::File::ID3v2);
    lua_setfield(L, -2, "ID3v2");

    lua_pushinteger(L, TagLib::MPC::File::APE);
    lua_setfield(L, -2, "APE");

    lua_pushinteger(L, TagLib::MPC::File::AllTags);
    lua_setfield(L, -2, "AllTags");

    return 1;
}

LTAGLIB_PUBLIC
int luaopen_TagLib_MPC_File(lua_State *L) {
    return MPC::File::open(L);
}

template<>
const UserdataTable MPC::File::base::mod = {
    File__call<MPC::File>,
    NULL,
    File__submodules,
};

template<>
const UserdataMetatable MPC::File::base::metatable = {
    "TagLib::MPC::File", /* name */
    File__index, /* indextable */
    NULL, /* indexfunc */
};

#include "../shared/userdata.tcc"
template class DerivedUserdata<TagLib::MPC::File, LuaTagLib::File>;

#endif
