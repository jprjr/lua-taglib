#include "matroskaproperties.h"
#include "matroskafile.h"
#include "../tstring.h"

#define T Matroska::Properties
#define TT TagLib::T
#define XSTR(s) STR(s)
#define STR(s) #s
#define NAME XSTR(TT)

using namespace LuaTagLib;

static int Properties__call(lua_State* L) {
    int args = lua_gettop(L);
    TT* p = NULL;

    switch(args) {
        case 1: {
            p = new TT(Matroska::File::checkPtr(L, 1));
            break;
        }
        case 2: {
            p = new TT(Matroska::File::checkPtr(L, 1), AudioProperties::ReadStyle::checkValue(L, 2));
            break;
        }
        default: break;
    }

    if(p == NULL) return luaL_error(L, "invalid arguments");
    T::pushPtr(L,p);
    return 1;
}

static int Properties_bitsPerSample(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->bitsPerSample());
    return 1;
}

static int Properties_docType(lua_State* L) {
    String::pushValue(L, T::checkPtr(L,1)->docType());
    return 1;
}

static int Properties_docTypeVersion(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->docTypeVersion());
    return 1;
}

static int Properties_codecName(lua_State* L) {
    String::pushValue(L, T::checkPtr(L,1)->codecName());
    return 1;
}

static int Properties_title(lua_State* L) {
    String::pushValue(L, T::checkPtr(L,1)->title());
    return 1;
}

static
const luaL_Reg Properties__index[] = {
    { "bitsPerSample", Properties_bitsPerSample },
    { "docType", Properties_docType },
    { "docTypeVersion", Properties_docTypeVersion },
    { "codecName", Properties_codecName },
    { "title", Properties_title },
    { NULL, NULL },
};

LTAGLIB_PUBLIC
int luaopen_TagLib_Matroska_Properties(lua_State *L) {
    return T::open(L);
}

template<>
const UserdataTable Matroska::Properties::base::mod = {
    Properties__call,
    NULL, /* __index */
    NULL, /* init */
};

template<>
const UserdataMetatable Matroska::Properties::base::metatable = {
    NAME, /* name */
    Properties__index, /* indextable */
    NULL, /* indexfunc */
};

#undef T
#include "../shared/userdata.tcc"
template class LuaTagLib::DerivedUserdata<TagLib::Matroska::Properties, LuaTagLib::AudioProperties>;

