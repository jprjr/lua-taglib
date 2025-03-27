#include "id3v1tag.h"

#include "../tfile.h"
#include "../tbytevector.h"

using namespace LuaTagLib;

static int Tag__call(lua_State* L) {
    int args = lua_gettop(L);
    TagLib::ID3v1::Tag* t;

    switch(args) {
        case 0: {
            t = new TagLib::ID3v1::Tag();
            break;
        }
        case 2: {
            t = new TagLib::ID3v1::Tag(File::checkPtr(L, 1), luaL_checkinteger(L, 2));
            break;
        }
        default: break;
    }

    if(t == NULL) return luaL_error(L, "invalid arguments");

    ID3v1::Tag::pushPtr(L, t);
    return 1;
}

#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,9,0)
static int Tag_genreNumber(lua_State* L) {
    TagLib::ID3v1::Tag* tag = ID3v1::Tag::checkPtr(L, 1);
    lua_pushinteger(L, tag->genreNumber());
    return 1;
}

static int Tag_setGenreNumber(lua_State* L) {
    TagLib::ID3v1::Tag* tag = ID3v1::Tag::checkPtr(L, 1);
    tag->setGenreNumber(luaL_checkinteger(L, 1));
    lua_settop(L,1);
    return 1;
}
#endif

static int Tag_render(lua_State* L) {
    TagLib::ID3v1::Tag* tag = ID3v1::Tag::checkPtr(L, 1);
    ByteVector::pushValue(L, tag->render());
    return 1;
}

static
const luaL_Reg Tag__index[] = {
#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,9,0)
    { "genreNumber", Tag_genreNumber },
    { "setGenreNumber", Tag_setGenreNumber },
#endif
    { "render", Tag_render },
    { NULL, NULL }
};

static int Tag_static_fileIdentifier(lua_State* L) {
    ByteVector::pushValue(L, TagLib::ID3v1::Tag::fileIdentifier());
    return 1;
}

static const luaL_Reg Tag_static_index[] = {
    { "fileIdentifier", Tag_static_fileIdentifier },
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v1_Tag(lua_State *L) {
    return ID3v1::Tag::open(L);
}

template<>
const UserdataTable ID3v1::Tag::base::mod = {
    Tag__call,
    Tag_static_index,
    NULL,
};

template<>
const UserdataMetatable ID3v1::Tag::base::metatable = {
    "TagLib::ID3v1::Tag", /* name */
    Tag__index, /* indextable */
    NULL, /* indexfunc */
};

#include "../shared/userdata.tcc"
template class LuaTagLib::DerivedUserdata<TagLib::ID3v1::Tag, LuaTagLib::Tag>;
