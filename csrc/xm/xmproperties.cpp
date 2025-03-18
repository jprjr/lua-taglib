#include "xmproperties.h"

#if LTAGLIB_HAS_XM_PROPERTIES

#define T XM::Properties
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
            p = new TT(AudioProperties::ReadStyle::checkValue(L, 1));
            break;
        }
        default: break;
    }

    if(p == NULL) return luaL_error(L, "invalid arguments");
    T::pushPtr(L, p);
    return 1;
}

static int Properties_lengthInPatterns(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->lengthInPatterns());
    return 1;
}

static int Properties_version(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->version());
    return 1;
}

static int Properties_restartPosition(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->restartPosition());
    return 1;
}

static int Properties_patternCount(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->patternCount());
    return 1;
}

static int Properties_instrumentCount(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->instrumentCount());
    return 1;
}

static int Properties_sampleCount(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->sampleCount());
    return 1;
}

static int Properties_flags(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->flags());
    return 1;
}

static int Properties_tempo(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->tempo());
    return 1;
}

static int Properties_bpmSpeed(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->bpmSpeed());
    return 1;
}

static int Properties_setChannels(lua_State* L) {
    T::checkPtr(L,1)->setChannels(luaL_checkinteger(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Properties_setLengthInPatterns(lua_State* L) {
    T::checkPtr(L,1)->setLengthInPatterns(luaL_checkinteger(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Properties_setVersion(lua_State* L) {
    T::checkPtr(L,1)->setVersion(luaL_checkinteger(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Properties_setRestartPosition(lua_State* L) {
    T::checkPtr(L,1)->setRestartPosition(luaL_checkinteger(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Properties_setPatternCount(lua_State* L) {
    T::checkPtr(L,1)->setPatternCount(luaL_checkinteger(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Properties_setInstrumentCount(lua_State* L) {
    T::checkPtr(L,1)->setInstrumentCount(luaL_checkinteger(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Properties_setSampleCount(lua_State* L) {
    T::checkPtr(L,1)->setSampleCount(luaL_checkinteger(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Properties_setFlags(lua_State* L) {
    T::checkPtr(L,1)->setFlags(luaL_checkinteger(L, 2));
    lua_settop(L,1);
    return 1;
}


static int Properties_setTempo(lua_State* L) {
    T::checkPtr(L,1)->setTempo(luaL_checkinteger(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Properties_setBpmSpeed(lua_State* L) {
    T::checkPtr(L,1)->setBpmSpeed(luaL_checkinteger(L, 2));
    lua_settop(L,1);
    return 1;
}

static
const luaL_Reg Properties__index[] = {
    { "lengthInPatterns", Properties_lengthInPatterns },
    { "version", Properties_version },
    { "restartPosition", Properties_restartPosition },
    { "patternCount", Properties_patternCount },
    { "instrumentCount", Properties_instrumentCount },
    { "sampleCount", Properties_sampleCount },
    { "flags", Properties_flags },
    { "tempo", Properties_tempo },
    { "bpmSpeed", Properties_bpmSpeed },
    { "setChannels", Properties_setChannels },
    { "setLengthInPatterns", Properties_setLengthInPatterns },
    { "setVersion", Properties_setVersion },
    { "setRestartPosition", Properties_setRestartPosition },
    { "setPatternCount", Properties_setPatternCount },
    { "setInstrumentCount", Properties_setInstrumentCount },
    { "setSampleCount", Properties_setSampleCount },
    { "setFlags", Properties_setFlags },
    { "setTempo", Properties_setTempo },
    { "setBpmSpeed", Properties_setBpmSpeed },
    { NULL, NULL },
};

static int Properties__enums(lua_State* L) {
    lua_pushinteger(L, TT::LinearFreqTable);
    lua_setfield(L, -2, "LinearFreqTable");

    return 0;
}

LTAGLIB_PUBLIC
int luaopen_TagLib_XM_Properties(lua_State *L) {
    return T::open(L);
}

template<>
const UserdataTable T::base::mod = {
    Properties__call,
    NULL,
    Properties__enums,
};

template<>
const UserdataMetatable T::base::metatable = {
    NAME, /* name */
    Properties__index, /* indextable */
    NULL, /* indexfunc */
};

#undef T
#include "../shared/userdata.tcc"
template class DerivedUserdata<TagLib::XM::Properties, LuaTagLib::AudioProperties>;

#endif
