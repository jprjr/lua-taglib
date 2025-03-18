#include "ownershipframe.h"

#if LTAGLIB_HAS_OWNERSHIPFRAME

#include "../tbytevector.h"
#include "../tstring.h"

#define T ID3v2::OwnershipFrame
#define TT TagLib::T
#define XSTR(s) STR(s)
#define STR(s) #s
#define NAME XSTR(TT)

using namespace LuaTagLib;

static int Frame__call(lua_State* L) {
    int args = lua_gettop(L);
    TT* f = NULL;

    switch(args) {
        case 1: {
            if(String::Type::isValid(L, 1)) {
                f = new TT(String::Type::checkValue(L, 1));
                break;
            }
            f = new TT(ByteVector::looseValue(L, 1));
            break;
        }
        default: break;
    }

    if(f == NULL) return luaL_error(L, "invalid arguments");
    T::pushPtr(L, f);
    return 1;
}


static int Frame_datePurchased(lua_State* L) {
    String::pushValue(L, T::checkPtr(L,1)->datePurchased());
    return 1;
}

static int Frame_setDatePurchased(lua_State* L) {
    T::checkPtr(L,1)->setDatePurchased(String::checkValue(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Frame_pricePaid(lua_State* L) {
    String::pushValue(L, T::checkPtr(L,1)->pricePaid());
    return 1;
}

static int Frame_setPricePaid(lua_State* L) {
    T::checkPtr(L,1)->setPricePaid(String::checkValue(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Frame_seller(lua_State* L) {
    String::pushValue(L, T::checkPtr(L,1)->seller());
    return 1;
}

static int Frame_setSeller(lua_State* L) {
    T::checkPtr(L,1)->setSeller(String::checkValue(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Frame_textEncoding(lua_State* L) {
    String::Type::pushValue(L, T::checkPtr(L,1)->textEncoding());
    return 1;
}

static int Frame_setTextEncoding(lua_State* L) {
    T::checkPtr(L,1)->setTextEncoding(String::Type::checkValue(L, 2));
    lua_settop(L,1);
    return 1;
}

static const luaL_Reg Frame__index[] = {
    { "datePurchased", Frame_datePurchased },
    { "setDatePurchased", Frame_setDatePurchased },
    { "pricePaid", Frame_pricePaid },
    { "setPricePaid", Frame_setPricePaid },
    { "seller", Frame_seller },
    { "setSeller", Frame_setSeller },
    { "textEncoding", Frame_textEncoding },
    { "setTextEncoding", Frame_setTextEncoding },
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_OwnershipFrame(lua_State* L) {
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
template class DerivedUserdata<TagLib::ID3v2::OwnershipFrame, LuaTagLib::ID3v2::Frame>;

#endif
