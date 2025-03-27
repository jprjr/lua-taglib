#include "dsdifffile.h"

#if LTAGLIB_HAS_DSDIFF_FILE

#include "dsdiffproperties.h"

#include "../tpropertymap.h"
#include "../id3v2/id3v2tag.h"
#include "../id3v2/id3v2.h"
#include "diin/dsdiffdiintag.h"
#include "../tiostream.h"

#define T DSDIFF::File
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
            LuaTagLib::Tag::pushPtr(L, f->tag(), 1);
            break;
        }
        default: {
            return luaL_error(L, "invalid arguments");
        }
    }
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

static int File_DIINTag(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    int args = lua_gettop(L);

    switch(args) {
        case 1: {
            DSDIFF::DIIN::Tag::pushPtr(L, f->DIINTag(), 1);
            break;
        }
        default: {
            return luaL_error(L, "invalid arguments");
        }
    }
    return 1;
}

static int File_audioProperties(lua_State* L) {
    DSDIFF::Properties::pushPtr(L, T::checkPtr(L,1)->audioProperties(), 1);
    return 1;
}

static int File_save(lua_State* L) {
    int args = lua_gettop(L);
    switch(args) {
        case 1: {
            lua_pushboolean(L, T::checkPtr(L,1)->save());
            return 1;
        }
        case 2: {
            lua_pushboolean(L, T::checkPtr(L,1)->save(
              luaL_checkinteger(L,2)
            ));
            return 1;
        }
        default: break;
    }
    return luaL_error(L, "invalid arguments");
}

static int File_strip(lua_State* L) {
    int args = lua_gettop(L);
    switch(args) {
        case 1: {
            T::checkPtr(L,1)->strip();
            break;
        }
        case 2: {
            T::checkPtr(L,1)->strip(
              luaL_checkinteger(L,2)
            );
            break;
        }
        default: return luaL_error(L,"invalid arguments");
    }

    lua_settop(L,1);
    return 1;
}

static int File_hasID3v2Tag(lua_State* L) {
    lua_pushboolean(L, T::checkPtr(L,1)->hasID3v2Tag());
    return 1;
}

static int File_hasDIINTag(lua_State* L) {
    lua_pushboolean(L, T::checkPtr(L,1)->hasDIINTag());
    return 1;
}

static
const luaL_Reg File__index[] = {
    { "tag", File_tag },
    { "ID3v2Tag", File_ID3v2Tag },
    { "DIINTag", File_DIINTag },
    { "audioProperties", File_audioProperties },
    { "save", File_save },
    { "strip", File_strip },
    { "hasID3v2Tag", File_hasID3v2Tag },
    { "hasDIINTag", File_hasDIINTag },
    { NULL, NULL }
};

static int File__submodules(lua_State* L) {
    luaL_requiref(L, "TagLib.DSDIFF.File.TagTypes", luaopen_TagLib_DSDIFF_File_TagTypes, 0);
    lua_setfield(L, -2, "TagTypes");
    return 0;
}

LTAGLIB_PUBLIC
int luaopen_TagLib_DSDIFF_File(lua_State *L) {
    return DSDIFF::File::open(L);
}

LTAGLIB_PUBLIC
int luaopen_TagLib_DSDIFF_File_TagTypes(lua_State* L) {
    lua_newtable(L);

    lua_pushinteger(L, TT::NoTags);
    lua_setfield(L, -2, "NoTags");

    lua_pushinteger(L, TT::DIIN);
    lua_setfield(L, -2, "DIIN");

    lua_pushinteger(L, TT::ID3v2);
    lua_setfield(L, -2, "ID3v2");

    lua_pushinteger(L, TT::AllTags);
    lua_setfield(L, -2, "AllTags");

    return 1;
}

template<>
const UserdataTable DSDIFF::File::base::mod = {
    File__call<DSDIFF::File>,
    NULL,
    File__submodules,
};

template<>
const UserdataMetatable DSDIFF::File::base::metatable = {
    NAME, /* name */
    File__index, /* indextable */
    NULL, /* indexfunc */
};

#undef T
#include "../shared/userdata.tcc"
template class LuaTagLib::DerivedUserdata<TagLib::DSDIFF::File, LuaTagLib::File>;

#endif
