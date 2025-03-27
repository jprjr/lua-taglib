#include "trueaudiofile.h"

#if LTAGLIB_HAS_TRUEAUDIO_FILE

#include "trueaudioproperties.h"

#include "../tlist.h"
#include "../id3v1/id3v1tag.h"
#include "../id3v2/id3v2tag.h"
#include "../tiostream.h"

using namespace LuaTagLib;


static int File_ID3v1Tag(lua_State* L) {
    TagLib::TrueAudio::File* f = TrueAudio::File::checkPtr(L, 1);
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
        default: {
            return luaL_error(L, "invalid arguments");
        }
    }
    return 1;
}

static int File_ID3v2Tag(lua_State* L) {
    TagLib::TrueAudio::File* f = TrueAudio::File::checkPtr(L, 1);
    int args = lua_gettop(L);

    switch(args) {
        case 1: {
            ID3v2::Tag::pushPtr(L, f->ID3v2Tag(), 1);
            break;
        }
        case 2: {
            ID3v2::Tag::pushPtr(L, f->ID3v2Tag((bool) lua_toboolean(L, 2)), 1);
            break;
        }
        default: {
            return luaL_error(L, "invalid arguments");
        }
    }
    return 1;
}

static int File_strip(lua_State* L) {
    TagLib::TrueAudio::File* f = TrueAudio::File::checkPtr(L, 1);

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

static int File_audioProperties(lua_State* L) {
   TagLib::TrueAudio::File* f = TrueAudio::File::checkPtr(L, 1);
   TrueAudio::Properties::pushPtr(L, f->audioProperties(), 1);
   return 1;
}

#if LTAGLIB_ATLEAST(LTAGLIB_1_9)
static int File_hasID3v1Tag(lua_State* L) {
    lua_pushboolean(L, TrueAudio::File::checkPtr(L,1)->hasID3v1Tag());
    return 1;
}

static int File_hasID3v2Tag(lua_State* L) {
    lua_pushboolean(L, TrueAudio::File::checkPtr(L,1)->hasID3v2Tag());
    return 1;
}
#endif

static
const luaL_Reg File__index[] = {
    { "ID3v1Tag", File_ID3v1Tag },
    { "ID3v2Tag", File_ID3v2Tag },
    { "strip", File_strip },
    { "audioProperties", File_audioProperties },
#if LTAGLIB_ATLEAST(LTAGLIB_1_9)
    { "hasID3v1Tag", File_hasID3v1Tag},
    { "hasID3v2Tag", File_hasID3v2Tag},
#endif
    { NULL, NULL }
};

static int File__submodules(lua_State* L) {
    luaL_requiref(L, "TagLib.TrueAudio.File.TagTypes", luaopen_TagLib_TrueAudio_File_TagTypes, 0);
    lua_setfield(L, -2, "TagTypes");
    return 0;
}

LTAGLIB_PUBLIC
int luaopen_TagLib_TrueAudio_File_TagTypes(lua_State *L) {
    lua_newtable(L);

    lua_pushinteger(L, TagLib::TrueAudio::File::NoTags);
    lua_setfield(L, -2, "NoTags");

    lua_pushinteger(L, TagLib::TrueAudio::File::ID3v1);
    lua_setfield(L, -2, "ID3v1");

    lua_pushinteger(L, TagLib::TrueAudio::File::ID3v2);
    lua_setfield(L, -2, "ID3v2");

    lua_pushinteger(L, TagLib::TrueAudio::File::AllTags);
    lua_setfield(L, -2, "AllTags");

    return 1;
}

LTAGLIB_PUBLIC
int luaopen_TagLib_TrueAudio_File(lua_State *L) {
    return TrueAudio::File::open(L);
}

template<>
const UserdataTable TrueAudio::File::base::mod = {
    File__call<TrueAudio::File>,
    NULL,
    File__submodules,
};

template<>
const UserdataMetatable TrueAudio::File::base::metatable = {
    "TagLib::TrueAudio::File", /* name */
    File__index, /* indextable */
    NULL, /* indexfunc */
};

#undef T
#include "../shared/userdata.tcc"
template class LuaTagLib::DerivedUserdata<TagLib::TrueAudio::File, LuaTagLib::File>;

#endif
