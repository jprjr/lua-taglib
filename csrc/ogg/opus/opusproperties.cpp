#include "opusproperties.h"

#if LTAGLIB_HAS_OPUSPROPERTIES

#include "opusfile.h"

#define T Ogg::Opus::Properties
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
            p = new TT(Ogg::Opus::File::checkPtr(L, 1));
            break;
        }
        case 2: {
            p = new TT(Ogg::Opus::File::checkPtr(L, 1), AudioProperties::ReadStyle::checkValue(L, 2));
            break;
        }
        default: break;
    }

    if(p == NULL) return luaL_error(L, "invalid arguments");
    T::pushPtr(L, p);
    return 1;
}

static int Properties_inputSampleRate(lua_State* L) {
    TT* ap = T::checkPtr(L, 1);
    lua_pushinteger(L, ap->inputSampleRate());
    return 1;
}

static int Properties_opusVersion(lua_State* L) {
    TT* ap = T::checkPtr(L, 1);
    lua_pushinteger(L, ap->opusVersion());
    return 1;
}

static
const luaL_Reg Properties__index[] = {
    { "inputSampleRate", Properties_inputSampleRate },
    { "opusVersion", Properties_opusVersion },
    { NULL, NULL },
};


LTAGLIB_PUBLIC
int luaopen_TagLib_Ogg_Opus_Properties(lua_State *L) {
    return T::open(L);
}

template<>
const UserdataTable T::base::mod = {
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
#include "../../shared/userdata.tcc"
template class DerivedUserdata<TagLib::Ogg::Opus::Properties, LuaTagLib::AudioProperties>;

#endif
