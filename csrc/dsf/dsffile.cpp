#include "dsffile.h"

#if LTAGLIB_HAS_DSF_FILE

#include "dsfproperties.h"

#include "../tpropertymap.h"
#include "../id3v2/id3v2tag.h"
#include "../id3v2/id3v2.h"
#include "../tiostream.h"

#define T DSF::File
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
            ID3v2::Tag::pushPtr(L, f->tag(), 1);
            break;
        }
        default: {
            return luaL_error(L, "invalid arguments");
        }
    }
    return 1;
}

static int File_audioProperties(lua_State* L) {
    DSF::Properties::pushPtr(L, T::checkPtr(L,1)->audioProperties(), 1);
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
            lua_pushboolean(L, T::checkPtr(L,1)->save(ID3v2::Version::checkValue(L,2)));
            return 1;
        }
        default: break;
    }
    return luaL_error(L, "invalid arguments");
}

static
const luaL_Reg File__index[] = {
    { "tag", File_tag },
    { "audioProperties", File_audioProperties },
    { "save", File_save },
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_DSF_File(lua_State *L) {
    return DSF::File::open(L);
}

template<>
const UserdataTable DSF::File::base::mod = {
    File__call<DSF::File>,
    NULL,
    NULL,
};


template<>
const UserdataMetatable DSF::File::base::metatable = {
    NAME, /* name */
    File__index, /* indextable */
    NULL, /* indexfunc */
};

#undef T
#include "../shared/userdata.tcc"
template class DerivedUserdata<TagLib::DSF::File, LuaTagLib::File>;

#endif
