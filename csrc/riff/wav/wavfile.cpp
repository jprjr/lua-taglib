#include "wavfile.h"

#if LTAGLIB_HAS_RIFF_WAV_FILE

#include "wavproperties.h"
#include "../../id3v2/id3v2tag.h"
#include "../info/infotag.h"
#include "../../tiostream.h"

#if LTAGLIB_ATLEAST(LTAGLIB_1_12)
#include "../../id3v2/id3v2.h"
#endif

#define T RIFF::WAV::File
#define TT TagLib::T
#define XSTR(s) STR(s)
#define STR(s) #s
#define NAME XSTR(TT)

using namespace LuaTagLib;

static int File_tag(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    int args = lua_gettop(L);

    switch(args) {
        case 1: {
#if LTAGLIB_ATLEAST(LTAGLIB_2_0)
            LuaTagLib::Tag::pushPtr(L, f->tag(), 1);
#else
            ID3v2::Tag::pushPtr(L, f->tag(), 1);
#endif
            break;
        }
        default: {
            return luaL_error(L, "invalid arguments");
        }
    }
    return 1;
}


#if LTAGLIB_ATLEAST(LTAGLIB_1_9)
static int File_hasID3v2Tag(lua_State* L) {
    lua_pushboolean(L, T::checkPtr(L,1)->hasID3v2Tag());
    return 1;
}

static int File_hasInfoTag(lua_State* L) {
    lua_pushboolean(L, T::checkPtr(L,1)->hasInfoTag());
    return 1;
}

static int File_ID3v2Tag(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    int args = lua_gettop(L);

    switch(args) {
        case 1: {
            ID3v2::Tag::pushPtr(L, f->ID3v2Tag(), 1);
            break;
        }
        default: {
            return luaL_error(L, "invalid arguments");
        }
    }
    return 1;
}

static int File_InfoTag(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    int args = lua_gettop(L);

    switch(args) {
        case 1: {
            RIFF::Info::Tag::pushPtr(L, f->InfoTag(), 1);
            break;
        }
        default: {
            return luaL_error(L, "invalid arguments");
        }
    }
    return 1;
}

static int File_save(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    int args = lua_gettop(L);
    bool saved = false;

    switch(args) {
        case 1: {
            saved = f->save();
            break;
        }
#if LTAGLIB_UNDER(LTAGLIB_1_12)
        case 2: {
            saved = f->save((TT::TagTypes) luaL_checkinteger(L, 2));
            break;
        }
        case 3: {
            saved = f->save((TT::TagTypes) luaL_checkinteger(L, 2), lua_toboolean(L, 3));
            break;
        }
        case 4: {
            saved = f->save((TT::TagTypes) luaL_checkinteger(L, 2), lua_toboolean(L, 3), luaL_checkinteger(L, 4));
            break;
        }
#else
        case 3: {
            saved = f->save((TT::TagTypes) luaL_checkinteger(L, 2), File::StripTags::checkValue(L, 3));
            break;
        }
        case 4: {
            saved = f->save((TT::TagTypes) luaL_checkinteger(L, 2), File::StripTags::checkValue(L,3), ID3v2::Version::checkValue(L, 4));
            break;
        }

#endif
        default: return luaL_error(L, "invalid arguments");
    }

    lua_pushboolean(L, saved);
    return 1;
}
#endif

static int File_audioProperties(lua_State* L) {
   TT* f = T::checkPtr(L, 1);
   RIFF::WAV::Properties::pushPtr(L, f->audioProperties(), 1);
   return 1;
}

#if LTAGLIB_ATLEAST(LTAGLIB_1_11)
static int File_strip(lua_State* L) {
    int args = lua_gettop(L);

    switch(args) {
        case 1: {
            T::checkPtr(L,1)->strip();
            break;
        }
        case 2: {
            T::checkPtr(L,1)->strip((TT::TagTypes)luaL_checkinteger(L,2));
            break;
        }
        default: return luaL_error(L, "invalid arguments");
    }
    lua_settop(L,1);
    return 1;
}
#endif

static
const luaL_Reg File__index[] = {
    { "tag", File_tag },
    { "audioProperties", File_audioProperties },
#if LTAGLIB_ATLEAST(LTAGLIB_1_9)
    { "hasID3v2Tag", File_hasID3v2Tag },
    { "hasInfoTag", File_hasInfoTag },
    { "ID3v2Tag", File_ID3v2Tag },
    { "InfoTag", File_InfoTag },
    { "save", File_save },
#endif
#if LTAGLIB_ATLEAST(LTAGLIB_1_11)
    { "strip", File_strip },
#endif
    { NULL, NULL }
};

static int File__submodules(lua_State* L) {
#if LTAGLIB_ATLEAST(LTAGLIB_1_9)
    luaL_requiref(L, "TagLib.RIFF.WAV.File.TagTypes", luaopen_TagLib_RIFF_WAV_File_TagTypes, 0);
    lua_setfield(L, -2, "TagTypes");
#else
    (void)L;
#endif
    return 0;
}

LTAGLIB_PUBLIC
int luaopen_TagLib_RIFF_WAV_File(lua_State *L) {
    return T::open(L);
}

#if LTAGLIB_ATLEAST(LTAGLIB_1_9)
LTAGLIB_PUBLIC
int luaopen_TagLib_RIFF_WAV_File_TagTypes(lua_State *L) {
    lua_newtable(L);

    lua_pushinteger(L, TagLib::RIFF::WAV::File::NoTags);
    lua_setfield(L, -2, "NoTags");

    lua_pushinteger(L, TagLib::RIFF::WAV::File::ID3v2);
    lua_setfield(L, -2, "ID3v2");

    lua_pushinteger(L, TagLib::RIFF::WAV::File::Info);
    lua_setfield(L, -2, "Info");

    lua_pushinteger(L, TagLib::RIFF::WAV::File::AllTags);
    lua_setfield(L, -2, "AllTags");

    return 1;
}
#endif

template<>
const UserdataTable T::base::mod = {
    File__call<T>,
    NULL,
    File__submodules,
};

template<>
const UserdataMetatable T::base::metatable = {
    NAME, /* name */
    File__index, /* indextable */
    NULL, /* indexfunc */
};

#undef T
#include "../../shared/userdata.tcc"
template class LuaTagLib::DerivedUserdata<TagLib::RIFF::WAV::File, LuaTagLib::File>;

#endif
