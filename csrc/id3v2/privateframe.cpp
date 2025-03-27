#include "privateframe.h"

#if LTAGLIB_HAS_PRIVATEFRAME

#include "../tbytevector.h"
#include "../tstring.h"

#define T ID3v2::PrivateFrame
#define TT TagLib::T
#define XSTR(s) STR(s)
#define STR(s) #s
#define NAME XSTR(TT)

using namespace LuaTagLib;

static int Frame__call(lua_State* L) {
    int args = lua_gettop(L);
    TT* f = NULL;

    switch(args) {
        case 0: {
            f = new TT();
            break;
        }
        case 1: {
            f = new TT(ByteVector::looseValue(L, 1));
            break;
        }
        default: break;
    }

    if(f == NULL) return luaL_error(L, "invalid arguments");
    T::pushPtr(L, f);
    return 1;
}


static int Frame_owner(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    String::pushValue(L, f->owner());
    return 1;
}

static int Frame_data(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    ByteVector::pushValue(L, f->data());
    return 1;
}

static int Frame_setOwner(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    f->setOwner(String::checkValue(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Frame_setData(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    f->setData(ByteVector::looseValue(L, 2));
    lua_settop(L,1);
    return 1;
}

static const luaL_Reg Frame__index[] = {
    { "owner", Frame_owner },
    { "setOwner", Frame_setOwner },
    { "data", Frame_data },
    { "setData", Frame_setData },
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_PrivateFrame(lua_State* L) {
    return T::open(L);
}

template<>
const UserdataTable T::base::mod = {
    Frame__call,
    NULL,
    NULL
};

template<>
const UserdataMetatable T::base::metatable = {
    NAME, /* name */
    Frame__index, /* indextable */
    NULL, /* indexfunc */
};

#undef T
#include "../shared/userdata.tcc"
template class LuaTagLib::DerivedUserdata<TagLib::ID3v2::PrivateFrame, LuaTagLib::ID3v2::Frame>;

#endif
