#include "uniquefileidentifierframe.h"

#if LTAGLIB_HAS_UNIQUEFILEIDENTIFIERFRAME

#include "../tstring.h"
#include "../tbytevector.h"
#include "../tpropertymap.h"
#include "id3v2tag.h"

#define T ID3v2::UniqueFileIdentifierFrame
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
            f = new TT(ByteVector::looseValue(L, 1));
            break;
        }
        case 2: {
            f = new TT(checkstring(L,1), ByteVector::looseValue(L,2));
            lua_pop(L, 1);
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

static int Frame_identifier(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    ByteVector::pushValue(L, f->identifier());
    return 1;
}

static int Frame_setOwner(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    f->setOwner(String::checkValue(L,1));
    lua_settop(L,1);
    return 1;
}

static int Frame_setIdentifier(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    f->setIdentifier(ByteVector::looseValue(L,1));
    lua_settop(L,1);
    return 1;
}

#if LTAGLIB_ATLEAST(LTAGLIB_1_9)
static int Frame_asProperties(lua_State* L) {
    PropertyMap::pushValue(L, T::checkPtr(L,1)->asProperties());
    return 1;
}
#endif

static const luaL_Reg Frame__index[] = {
    { "owner", Frame_owner },
    { "identifier", Frame_identifier },
    { "setOwner", Frame_setOwner },
    { "setIdentifier", Frame_setIdentifier },
#if LTAGLIB_ATLEAST(LTAGLIB_1_9)
    { "asProperties", Frame_asProperties },
#endif
    { NULL, NULL }
};

#if LTAGLIB_ATLEAST(LTAGLIB_1_9)
static int Frame_static_findByOwner(lua_State* L) {
    TT* u = TT::findByOwner(ID3v2::Tag::checkPtr(L,1), String::checkValue(L, 2));
    if(u == NULL) return 0;

    T::pushPtr(L, u, 1);
    return 1;
}
#endif

static const luaL_Reg Frame__static[] = {
#if LTAGLIB_ATLEAST(LTAGLIB_1_9)
    { "findByOwner", Frame_static_findByOwner },
#endif
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_UniqueFileIdentifierFrame(lua_State* L) {
    return T::open(L);
}

template<>
const UserdataTable T::base::mod = {
    Frame__call,
    Frame__static,
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
template class LuaTagLib::DerivedUserdata<TagLib::ID3v2::UniqueFileIdentifierFrame, LuaTagLib::ID3v2::Frame>;

#endif
