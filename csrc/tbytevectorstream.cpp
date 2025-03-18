#include "tbytevectorstream.h"

#if LTAGLIB_HAS_BYTEVECTORSTREAM

#include "tbytevector.h"

using namespace LuaTagLib;

static int ByteVectorStream__call(lua_State* L) {
    TagLib::ByteVectorStream* b = NULL;
    int args = lua_gettop(L);

    switch(args) {
        case 1: {
            b = new TagLib::ByteVectorStream(ByteVector::looseValue(L, 1));
            break;
        }
        default: break;
    }

    if(b == NULL) return luaL_error(L, "invalid arguments");
    ByteVectorStream::pushPtr(L, b);
    return 1;
}

LTAGLIB_PUBLIC
int luaopen_TagLib_ByteVectorStream(lua_State* L) {
    return ByteVectorStream::open(L);
}

static int ByteVectorStream_data(lua_State* L) {
    ByteVector::pushValue(L,
      *(ByteVectorStream::checkPtr(L, 1)->data())
    );
    return 1;
}

static const luaL_Reg ByteVectorStream__index[] = {
    { "data", ByteVectorStream_data },
    { NULL, NULL }
};

template<>
const UserdataTable ByteVectorStream::base::mod = {
    ByteVectorStream__call,
    NULL,
    NULL,
};

template<>
const UserdataMetatable ByteVectorStream::base::metatable = {
    "TagLib::ByteVectorStream",
    ByteVectorStream__index,
    NULL
};

#include "shared/userdata.tcc"
template class DerivedUserdata<TagLib::ByteVectorStream, LuaTagLib::IOStream>;

#endif
