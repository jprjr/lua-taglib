#include "dsfproperties.h"

#if LTAGLIB_HAS_DSF_PROPERTIES

#include "../tbytevector.h"

#define T DSF::Properties
#define TT TagLib::T
#define XSTR(s) STR(s)
#define STR(s) #s
#define NAME XSTR(TT)

using namespace LuaTagLib;

static int Properties__call(lua_State* L) {
    int args = lua_gettop(L);
    TT* p = NULL;

    switch(args) {
        case 2: {
            p = new TT(ByteVector::looseValue(L, 1), AudioProperties::ReadStyle::checkValue(L, 2));
            break;
        }
        default: break;
    }

    if(p == NULL) return luaL_error(L, "invalid arguments");
    T::pushPtr(L, p);
    return 1;
}

static int Properties_formatVersion(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->formatVersion());
    return 1;
}

static int Properties_formatID(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->formatID());
    return 1;
}

static int Properties_channelType(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->channelType());
    return 1;
}

static int Properties_bitsPerSample(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->bitsPerSample());
    return 1;
}

static int Properties_sampleCount(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->sampleCount());
    return 1;
}

static int Properties_blockSizePerChannel(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->blockSizePerChannel());
    return 1;
}

static
const luaL_Reg Properties__index[] = {
    { "formatVersion", Properties_formatVersion },
    { "formatID", Properties_formatID },
    { "channelType", Properties_channelType },
    { "bitsPerSample", Properties_bitsPerSample },
    { "sampleCount", Properties_sampleCount },
    { "blockSizePerChannel", Properties_blockSizePerChannel },
    { NULL, NULL },
};


LTAGLIB_PUBLIC
int luaopen_TagLib_DSF_Properties(lua_State *L) {
    return T::open(L);
}

template<>
const UserdataTable DSF::Properties::base::mod = {
    Properties__call,
    NULL,
    NULL,
};

template<>
const UserdataMetatable T::base::metatable = {
    NAME, /* name */
    Properties__index, /* indextable */
    NULL, /* indexfunc */
};

#undef T
#include "../shared/userdata.tcc"
template class LuaTagLib::DerivedUserdata<TagLib::DSF::Properties, LuaTagLib::AudioProperties>;

#endif
