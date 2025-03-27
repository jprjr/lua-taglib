#include "id3v2extendedheader.h"

#include "../tbytevector.h"

using namespace LuaTagLib;

static int ExtendedHeader__call(lua_State* L) {
    int args = lua_gettop(L);
    TagLib::ID3v2::ExtendedHeader* h = NULL;

    switch(args) {
        case 0: {
            h = new TagLib::ID3v2::ExtendedHeader();
            break;
        }
        default: break;
    }
    if(h == NULL) return luaL_error(L, "invalid arguments");

    ID3v2::ExtendedHeader::pushPtr(L, h);
    return 1;
}

static int ExtendedHeader_size(lua_State* L) {
    TagLib::ID3v2::ExtendedHeader* e = ID3v2::ExtendedHeader::checkPtr(L, 1);
    lua_pushinteger(L, e->size());
    return 1;
}

static int ExtendedHeader_setData(lua_State* L) {
    TagLib::ID3v2::ExtendedHeader* h = ID3v2::ExtendedHeader::checkPtr(L, 1);
    h->setData(ByteVector::looseValue(L, 2));
    return 1;
}

static const luaL_Reg ExtendedHeader__index[] = {
    { "size", ExtendedHeader_size },
    { "setData", ExtendedHeader_setData },
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_ExtendedHeader(lua_State* L) {
    return ID3v2::ExtendedHeader::open(L);
}

template<>
const UserdataTable ID3v2::ExtendedHeader::base::mod = {
    ExtendedHeader__call,
    NULL,
    NULL,
};

template<>
const UserdataMetatable ID3v2::ExtendedHeader::base::metatable = {
    "TagLib::ID3v2::ExtendedHeader", /* name */
    ExtendedHeader__index, /* indextable */
    NULL, /* indexfunc */
};

#include "../shared/userdata.tcc"
template class LuaTagLib::BaseUserdata<TagLib::ID3v2::ExtendedHeader>;
