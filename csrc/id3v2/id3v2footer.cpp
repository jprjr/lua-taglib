#include "id3v2footer.h"
#include "id3v2header.h"
#include "../tbytevector.h"

using namespace LuaTagLib;

static int Footer__call(lua_State* L) {
    int args = lua_gettop(L);

    TagLib::ID3v2::Footer* h = NULL;

    switch(args) {
        case 0: {
            h = new TagLib::ID3v2::Footer();
            break;
        }
        default: break;
    }

    if(h == NULL) return luaL_error(L, "invalid arguments");
    ID3v2::Footer::pushPtr(L, h);
    return 1;
}

static int Footer_render(lua_State* L) {
    TagLib::ID3v2::Footer* f = ID3v2::Footer::checkPtr(L, 1);
    TagLib::ID3v2::Header* h = ID3v2::Header::checkPtr(L, 2);
    ByteVector::pushValue(L, f->render(h));
    return 1;
}

static const luaL_Reg Footer__index[] = {
    { "render", Footer_render },
    { NULL, NULL }
};

static int Footer_static_size(lua_State* L) {
    lua_pushinteger(L, TagLib::ID3v2::Footer::size());
    return 1;
}

static const luaL_Reg Footer_static_index[] = {
    { "size", Footer_static_size },
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_Footer(lua_State* L) {
    return ID3v2::Footer::open(L);
}

template<>
const UserdataTable ID3v2::Footer::base::mod = {
    Footer__call,
    Footer_static_index,
    NULL,
};

template<>
const UserdataMetatable ID3v2::Footer::base::metatable = {
    "TagLib::ID3v2::Footer", /* name */
    Footer__index, /* indextable */
    NULL, /* indexfunc */
};

#include "../shared/userdata.tcc"
template class LuaTagLib::BaseUserdata<TagLib::ID3v2::Footer>;
