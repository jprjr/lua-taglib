#include "itproperties.h"

#if LTAGLIB_HAS_IT_PROPERTIES

#define T IT::Properties
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

static int Properties_instrumentCount(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->instrumentCount());
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

static int Properties_version(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->version());
    return 1;
}

static int Properties_compatibleVersion(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->compatibleVersion());
    return 1;
}

static int Properties_flags(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->flags());
    return 1;
}

static int Properties_special(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->special());
    return 1;
}

static int Properties_globalVolume(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->globalVolume());
    return 1;
}

static int Properties_mixVolume(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->mixVolume());
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

static int Properties_panningSeparation(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->panningSeparation());
    return 1;
}

static int Properties_pitchWheelDepth(lua_State* L) {
    lua_pushinteger(L, T::checkPtr(L,1)->pitchWheelDepth());
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

static int Properties_setPatternCount(lua_State* L) {
    T::checkPtr(L,1)->setPatternCount(luaL_checkinteger(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Properties_setVersion(lua_State* L) {
    T::checkPtr(L,1)->setVersion(luaL_checkinteger(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Properties_setCompatibleVersion(lua_State* L) {
    T::checkPtr(L,1)->setCompatibleVersion(luaL_checkinteger(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Properties_setFlags(lua_State* L) {
    T::checkPtr(L,1)->setFlags(luaL_checkinteger(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Properties_setSpecial(lua_State* L) {
    T::checkPtr(L,1)->setSpecial(luaL_checkinteger(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Properties_setGlobalVolume(lua_State* L) {
    T::checkPtr(L,1)->setGlobalVolume(luaL_checkinteger(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Properties_setMixVolume(lua_State* L) {
    T::checkPtr(L,1)->setMixVolume(luaL_checkinteger(L, 2));
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

static int Properties_setPanningSeparation(lua_State* L) {
    T::checkPtr(L,1)->setPanningSeparation(luaL_checkinteger(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Properties_setPitchWheelDepth(lua_State* L) {
    T::checkPtr(L,1)->setPitchWheelDepth(luaL_checkinteger(L, 2));
    lua_settop(L,1);
    return 1;
}

static
const luaL_Reg Properties__index[] = {
    { "lengthInPatterns", Properties_lengthInPatterns },
    { "stereo", Properties_stereo },
    { "instrumentCount", Properties_instrumentCount },
    { "sampleCount", Properties_sampleCount },
    { "patternCount", Properties_patternCount },
    { "version", Properties_version },
    { "compatibleVersion", Properties_compatibleVersion },
    { "flags", Properties_flags },
    { "special", Properties_special },
    { "globalVolume", Properties_globalVolume },
    { "mixVolume", Properties_mixVolume },
    { "tempo", Properties_tempo },
    { "bpmSpeed", Properties_bpmSpeed },
    { "panningSeparation", Properties_panningSeparation },
    { "pitchWheelDepth", Properties_pitchWheelDepth },
    { "setChannels", Properties_setChannels },
    { "setLengthInPatterns", Properties_setLengthInPatterns },
    { "setInstrumentCount", Properties_setInstrumentCount },
    { "setSampleCount", Properties_setSampleCount },
    { "setPatternCount", Properties_setPatternCount },
    { "setVersion", Properties_setVersion },
    { "setCompatibleVersion", Properties_setCompatibleVersion },
    { "setFlags", Properties_setFlags },
    { "setSpecial", Properties_setSpecial },
    { "setGlobalVolume", Properties_setGlobalVolume },
    { "setMixVolume", Properties_setMixVolume },
    { "setTempo", Properties_setTempo },
    { "setBpmSpeed", Properties_setBpmSpeed },
    { "setPanningSeparation", Properties_setPanningSeparation },
    { "setPitchWheelDepth", Properties_setPitchWheelDepth },
    { NULL, NULL },
};

static int Properties__enums(lua_State* L) {
    lua_pushinteger(L, TT::Stereo);
    lua_setfield(L, -2, "Stereo");

    lua_pushinteger(L, TT::Vol0MixOptimizations);
    lua_setfield(L, -2, "Vol0MixOptimizations");

    lua_pushinteger(L, TT::UseInstruments);
    lua_setfield(L, -2, "UseInstruments");

    lua_pushinteger(L, TT::LinearSlides);
    lua_setfield(L, -2, "LinearSlides");

    lua_pushinteger(L, TT::OldEffects);
    lua_setfield(L, -2, "OldEffects");

    lua_pushinteger(L, TT::LinkEffects);
    lua_setfield(L, -2, "LinkEffects");

    lua_pushinteger(L, TT::UseMidiPitchController);
    lua_setfield(L, -2, "UseMidiPitchController");

    lua_pushinteger(L, TT::RequestEmbeddedMidiConf);
    lua_setfield(L, -2, "RequestEmbeddedMidiConf");

    lua_pushinteger(L, TT::MessageAttached);
    lua_setfield(L, -2, "MessageAttached");

    lua_pushinteger(L, TT::MidiConfEmbedded);
    lua_setfield(L, -2, "MidiConfEmbedded");
    return 0;
}


LTAGLIB_PUBLIC
int luaopen_TagLib_IT_Properties(lua_State *L) {
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
template class LuaTagLib::DerivedUserdata<TagLib::IT::Properties, LuaTagLib::AudioProperties>;

#endif
