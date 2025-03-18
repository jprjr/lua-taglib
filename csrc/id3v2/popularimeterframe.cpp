#include "popularimeterframe.h"

#if LTAGLIB_HAS_POPULARIMETERFRAME

#include "../tbytevector.h"
#include "../tstring.h"

#define T ID3v2::PopularimeterFrame
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


static int Frame_email(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    String::pushValue(L, f->email());
    return 1;
}

static int Frame_setEmail(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    f->setEmail(String::checkValue(L,2));
    lua_settop(L,1);
    return 1;
}

static int Frame_rating(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    lua_pushinteger(L, f->rating());
    return 1;
}

static int Frame_setRating(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    f->setRating(luaL_checkinteger(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Frame_counter(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    lua_pushinteger(L, f->counter());
    return 1;
}

static int Frame_setCounter(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    f->setCounter(luaL_checkinteger(L, 2));
    lua_settop(L,1);
    return 1;
}

static const luaL_Reg Frame__index[] = {
    { "email", Frame_email },
    { "setEmail", Frame_setEmail },
    { "rating", Frame_rating },
    { "setRating", Frame_setRating },
    { "counter", Frame_counter },
    { "setCounter", Frame_setCounter },
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_PopularimeterFrame(lua_State* L) {
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
template class DerivedUserdata<TagLib::ID3v2::PopularimeterFrame, LuaTagLib::ID3v2::Frame>;

#endif
