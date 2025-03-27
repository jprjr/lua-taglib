#include "s3mproperties.h"

#if LTAGLIB_HAS_S3M_PROPERTIES

#define T S3M::Properties
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

static int Properties_stereo(lua_State* L) {
    lua_pushboolean(L, T::checkPtr(L,1)->stereo());
    return 1;
}

static int Properties_sampleCount(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->sampleCount());
    return 1;
}

static int Properties_patternCount(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->patternCount());
    return 1;
}

static int Properties_flags(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->flags());
    return 1;
}

static int Properties_trackerVersion(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->trackerVersion());
    return 1;
}

static int Properties_fileFormatVersion(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->fileFormatVersion());
    return 1;
}


static int Properties_globalVolume(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->globalVolume());
    return 1;
}

static int Properties_masterVolume(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->masterVolume());
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

static int Properties_setStereo(lua_State* L) {
    T::checkPtr(L,1)->setStereo(lua_toboolean(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Properties_setSampleCount(lua_State* L) {
    T::checkPtr(L,1)->setSampleCount(luaL_checkinteger(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Properties_setPatternCount(lua_State* L) {
    T::checkPtr(L,1)->setPatternCount(luaL_checkinteger(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Properties_setFlags(lua_State* L) {
    T::checkPtr(L,1)->setFlags(luaL_checkinteger(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Properties_setTrackerVersion(lua_State* L) {
    T::checkPtr(L,1)->setTrackerVersion(luaL_checkinteger(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Properties_setFileFormatVersion(lua_State* L) {
    T::checkPtr(L,1)->setFileFormatVersion(luaL_checkinteger(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Properties_setGlobalVolume(lua_State* L) {
    T::checkPtr(L,1)->setGlobalVolume(luaL_checkinteger(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Properties_setMasterVolume(lua_State* L) {
    T::checkPtr(L,1)->setMasterVolume(luaL_checkinteger(L, 2));
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
    { "stereo", Properties_stereo },
    { "sampleCount", Properties_sampleCount },
    { "patternCount", Properties_patternCount },
    { "flags", Properties_flags },
    { "trackerVersion", Properties_trackerVersion },
    { "fileFormatVersion", Properties_fileFormatVersion },
    { "globalVolume", Properties_globalVolume },
    { "masterVolume", Properties_masterVolume },
    { "tempo", Properties_tempo },
    { "bpmSpeed", Properties_bpmSpeed },
    { "setChannels", Properties_setChannels },
    { "setLengthInPatterns", Properties_setLengthInPatterns },
    { "setStereo", Properties_setStereo },
    { "setSampleCount", Properties_setSampleCount },
    { "setPatternCount", Properties_setPatternCount },
    { "setFlags", Properties_setFlags },
    { "setTrackerVersion", Properties_setTrackerVersion },
    { "setFileFormatVersion", Properties_setFileFormatVersion },
    { "setGlobalVolume", Properties_setGlobalVolume },
    { "setMasterVolume", Properties_setMasterVolume },
    { "setTempo", Properties_setTempo },
    { "setBpmSpeed", Properties_setBpmSpeed },
    { NULL, NULL },
};

static int Properties__enums(lua_State* L) {
    lua_pushinteger(L, TT::ST2Vibrato);
    lua_setfield(L, -2, "ST2Vibrato");

    lua_pushinteger(L, TT::ST2Tempo);
    lua_setfield(L, -2, "ST2Tempo");

    lua_pushinteger(L, TT::AmigaSlides);
    lua_setfield(L, -2, "AmigaSlides");

    lua_pushinteger(L, TT::Vol0MixOptimizations);
    lua_setfield(L, -2, "Vol0MixOptimizations");

    lua_pushinteger(L, TT::AmigaLimits);
    lua_setfield(L, -2, "AmigaLimits");

    lua_pushinteger(L, TT::EnableFilter);
    lua_setfield(L, -2, "EnableFilter");

    lua_pushinteger(L, TT::CustomData);
    lua_setfield(L, -2, "CustomData");

    return 0;
}

LTAGLIB_PUBLIC
int luaopen_TagLib_S3M_Properties(lua_State *L) {
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
template class LuaTagLib::DerivedUserdata<TagLib::S3M::Properties, LuaTagLib::AudioProperties>;

#endif
