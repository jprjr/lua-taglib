#include "audioproperties.h"

using namespace LuaTagLib;

#if LTAGLIB_ATLEAST(LTAGLIB_1_10)
static int AudioProperties_lengthInSeconds(lua_State* L) {
    TagLib::AudioProperties* props = AudioProperties::checkPtr(L, 1);

    lua_pushinteger(L, props->lengthInSeconds());
    return 1;
}

static int AudioProperties_lengthInMilliseconds(lua_State* L) {
    TagLib::AudioProperties* props = AudioProperties::checkPtr(L, 1);

    lua_pushinteger(L, props->lengthInMilliseconds());
    return 1;
}
#endif

#if LTAGLIB_UNDER(LTAGLIB_2_0)
static int AudioProperties_length(lua_State* L) {
    TagLib::AudioProperties* props = AudioProperties::checkPtr(L, 1);

    lua_pushinteger(L, props->length());
    return 1;
}
#endif

static int AudioProperties_bitrate(lua_State* L) {
    TagLib::AudioProperties* props = AudioProperties::checkPtr(L, 1);

    lua_pushinteger(L, props->bitrate());
    return 1;
}

static int AudioProperties_sampleRate(lua_State* L) {
    TagLib::AudioProperties* props = AudioProperties::checkPtr(L, 1);

    lua_pushinteger(L, props->sampleRate());
    return 1;
}

static int AudioProperties_channels(lua_State* L) {
    TagLib::AudioProperties* props = AudioProperties::checkPtr(L, 1);

    lua_pushinteger(L, props->channels());
    return 1;
}

const luaL_Reg AudioProperties__index[] = {
#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,10,0)
    { "lengthInSeconds", AudioProperties_lengthInSeconds },
    { "lengthInMilliseconds", AudioProperties_lengthInMilliseconds },
#endif
#if LTAGLIB_VERSION < LTAGLIB_VERSION_NUM(2,0,0)
    { "length", AudioProperties_length },
#endif
    { "bitrate", AudioProperties_bitrate },
    { "sampleRate", AudioProperties_sampleRate },
    { "channels", AudioProperties_channels },
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_AudioProperties(lua_State *L) {
    AudioProperties::open(L);

    luaL_requiref(L, "TagLib.AudioProperties.ReadStyle", luaopen_TagLib_AudioProperties_ReadStyle, 0);
    lua_setfield(L, -2, "ReadStyle");

    return 1;
}

#define E(x) { #x, sizeof(#x) - 1, TagLib::AudioProperties::x }

static const AudioProperties::ReadStyle::enum_type readStyles[] = {
    E(Fast),
    E(Average),
    E(Accurate)
};

template<>
const AudioProperties::ReadStyle::enum_type* AudioProperties::ReadStyle::m_values = readStyles;

template<>
const size_t AudioProperties::ReadStyle::m_len = sizeof(readStyles) / sizeof(readStyles[0]);

LTAGLIB_PUBLIC
int luaopen_TagLib_AudioProperties_ReadStyle(lua_State *L) {
    return AudioProperties::ReadStyle::open(L);
}

template<>
const UserdataTable AudioProperties::base::mod = {
    NULL,
    NULL,
    NULL,
};

template<>
const UserdataMetatable AudioProperties::base::metatable = {
    "TagLib::AudioProperties", /* name */
    AudioProperties__index, /* indextable */
    NULL, /* indexfunc */
};

#include "shared/enum.tcc"
template class Enum<TagLib::AudioProperties::ReadStyle>;

#include "shared/userdata.tcc"
template class BaseUserdata<TagLib::AudioProperties>;
