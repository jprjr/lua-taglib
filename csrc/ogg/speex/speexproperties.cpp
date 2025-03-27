#include "speexproperties.h"

#if LTAGLIB_HAS_SPEEXPROPERTIES

#include "speexfile.h"

#define T Ogg::Speex::Properties
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
            p = new TT(Ogg::Speex::File::checkPtr(L, 1));
            break;
        }
        case 2: {
            p = new TT(Ogg::Speex::File::checkPtr(L, 1), AudioProperties::ReadStyle::checkValue(L, 2));
            break;
        }
        default: break;
    }

    if(p == NULL) return luaL_error(L, "invalid arguments");
    T::pushPtr(L, p);
    return 1;
}

static int Properties_speexVersion(lua_State* L) {
    TT* ap = T::checkPtr(L, 1);
    lua_pushinteger(L, ap->speexVersion());
    return 1;
}

#if LTAGLIB_ATLEAST(LTAGLIB_1_10)
static int Properties_bitrateNominal(lua_State* L) {
    TT* ap = T::checkPtr(L, 1);
    lua_pushinteger(L, ap->bitrateNominal());
    return 1;
}
#endif

static
const luaL_Reg Properties__index[] = {
    { "speexVersion", Properties_speexVersion },
#if LTAGLIB_ATLEAST(LTAGLIB_1_10)
    { "bitrateNominal", Properties_bitrateNominal },
#endif
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_Ogg_Speex_Properties(lua_State *L) {
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
template class LuaTagLib::DerivedUserdata<TagLib::Ogg::Speex::Properties, LuaTagLib::AudioProperties>;

#endif
