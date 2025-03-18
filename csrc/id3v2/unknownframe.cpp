#include "unknownframe.h"

#include "../tbytevector.h"

using namespace LuaTagLib;

static int Frame__call(lua_State* L) {
    int args = lua_gettop(L);
    TagLib::ID3v2::UnknownFrame* f = NULL;

    switch(args) {
        case 1: {
            f = new TagLib::ID3v2::UnknownFrame(ByteVector::looseValue(L, 1));
            break;
        }
        default: break;
    }

    if(f == NULL) return luaL_error(L, "invalid arguments");
    ID3v2::UnknownFrame::pushPtr(L,f);
    return 1;
}


static int Frame_data(lua_State* L) {
    TagLib::ID3v2::UnknownFrame* f = ID3v2::UnknownFrame::checkPtr(L, 1);
    ByteVector::pushValue(L, f->data());
    return 1;
}

static const luaL_Reg Frame__index[] = {
    { "data", Frame_data },
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_UnknownFrame(lua_State* L) {
    return ID3v2::UnknownFrame::open(L);
}

template<>
const UserdataTable ID3v2::UnknownFrame::base::mod = {
    Frame__call,
    NULL,
    NULL
};

template<>
const UserdataMetatable ID3v2::UnknownFrame::base::metatable = {
    "TagLib::ID3v2::UnknownFrame", /* name */
    Frame__index, /* indextable */
    NULL, /* indexfunc */
};

#include "../shared/userdata.tcc"
template class DerivedUserdata<TagLib::ID3v2::UnknownFrame, LuaTagLib::ID3v2::Frame>;
