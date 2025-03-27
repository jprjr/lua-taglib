#include "vorbisproperties.h"

#include "vorbisfile.h"

#define T Ogg::Vorbis::Properties
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
            p = new TT(Ogg::Vorbis::File::checkPtr(L, 1));
            break;
        }
        case 2: {
            p = new TT(Ogg::Vorbis::File::checkPtr(L, 1), AudioProperties::ReadStyle::checkValue(L, 2));
            break;
        }
        default: break;
    }

    if(p == NULL) return luaL_error(L, "invalid arguments");
    T::pushPtr(L, p);
    return 1;
}

static int Properties_vorbisVersion(lua_State* L) {
    TT* ap = T::checkPtr(L, 1);
    lua_pushinteger(L, ap->vorbisVersion());
    return 1;
}

static int Properties_bitrateMaximum(lua_State* L) {
    TT* ap = T::checkPtr(L, 1);
    lua_pushinteger(L, ap->bitrateMaximum());
    return 1;
}

static int Properties_bitrateNominal(lua_State* L) {
    TT* ap = T::checkPtr(L, 1);
    lua_pushinteger(L, ap->bitrateNominal());
    return 1;
}

static int Properties_bitrateMinimum(lua_State* L) {
    TT* ap = T::checkPtr(L, 1);
    lua_pushinteger(L, ap->bitrateMinimum());
    return 1;
}

static
const luaL_Reg Properties__index[] = {
    { "vorbisVersion", Properties_vorbisVersion },
    { "bitrateMaximum", Properties_bitrateMaximum },
    { "bitrateNominal", Properties_bitrateNominal },
    { "bitrateMinimum", Properties_bitrateMinimum },
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_Ogg_Vorbis_Properties(lua_State *L) {
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
template class LuaTagLib::DerivedUserdata<TagLib::Ogg::Vorbis::Properties, LuaTagLib::AudioProperties>;
