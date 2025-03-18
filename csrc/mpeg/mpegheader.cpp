#include "mpegheader.h"

#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,11,0)
#include "mpegfile.h"
#endif

#if LTAGLIB_VERSION < LTAGLIB_VERSION_NUM(2,0,0)
#include "../tbytevector.h"
#endif

using namespace LuaTagLib;

static int Header__call(lua_State* L) {
    int args = lua_gettop(L);
    TagLib::MPEG::Header* h = NULL;

    switch(args) {
#if LTAGLIB_VERSION < LTAGLIB_VERSION_NUM(1,12,0)
        case 1: {
            h = new TagLib::MPEG::Header(ByteVector::looseValue(L, 1));
            break;
        }
#endif
#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,11,0)
        case 2: {
            h = new TagLib::MPEG::Header(MPEG::File::checkPtr(L, 1), luaL_checkinteger(L, 2));
            break;
        }
        case 3: {
            h = new TagLib::MPEG::Header(MPEG::File::checkPtr(L, 1), luaL_checkinteger(L, 2), (bool) lua_toboolean(L, 3));
            break;
        }
#endif
        default: break;
    }
    if(h == NULL) return luaL_error(L, "invalid arguments");
    MPEG::Header::pushPtr(L, h);
    return 1;
}

#if LTAGLIB_HAS_MPEG_HEADER_CHANNELCONFIGURATION
static int Header_channelConfiguration(lua_State* L) {
    TagLib::MPEG::Header* h = MPEG::Header::checkPtr(L, 1);
    MPEG::Header::ChannelConfiguration::pushValue(L, h->channelConfiguration());
    return 1;
}
#endif

#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(2,0,0)
static int Header_isADTS(lua_State* L) {
    TagLib::MPEG::Header* h = MPEG::Header::checkPtr(L, 1);
    lua_pushboolean(L, h->isADTS());
    return 1;
}
#endif

#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,5,0)
static int Header_samplesPerFrame(lua_State* L) {
    TagLib::MPEG::Header* h = MPEG::Header::checkPtr(L, 1);
    lua_pushinteger(L, h->samplesPerFrame());
    return 1;
}
#endif

static int Header_isValid(lua_State* L) {
    TagLib::MPEG::Header* h = MPEG::Header::checkPtr(L, 1);
    lua_pushboolean(L, h->isValid());
    return 1;
}

static int Header_version(lua_State* L) {
    TagLib::MPEG::Header* h = MPEG::Header::checkPtr(L, 1);
    MPEG::Header::Version::pushValue(L, h->version());
    return 1;
}

static int Header_layer(lua_State* L) {
    TagLib::MPEG::Header* h = MPEG::Header::checkPtr(L, 1);
    lua_pushinteger(L, h->layer());
    return 1;
}

static int Header_protectionEnabled(lua_State* L) {
    TagLib::MPEG::Header* h = MPEG::Header::checkPtr(L, 1);
    lua_pushboolean(L, h->protectionEnabled());
    return 1;
}

static int Header_bitrate(lua_State* L) {
    TagLib::MPEG::Header* h = MPEG::Header::checkPtr(L, 1);
    lua_pushinteger(L, h->bitrate());
    return 1;
}

static int Header_sampleRate(lua_State* L) {
    TagLib::MPEG::Header* h = MPEG::Header::checkPtr(L, 1);
    lua_pushinteger(L, h->sampleRate());
    return 1;
}

static int Header_isPadded(lua_State* L) {
    TagLib::MPEG::Header* h = MPEG::Header::checkPtr(L, 1);
    lua_pushboolean(L, h->isPadded());
    return 1;
}

static int Header_channelMode(lua_State* L) {
    TagLib::MPEG::Header* h = MPEG::Header::checkPtr(L, 1);
    MPEG::Header::ChannelMode::pushValue(L, h->channelMode());
    return 1;
}

static int Header_isCopyrighted(lua_State* L) {
    TagLib::MPEG::Header* h = MPEG::Header::checkPtr(L, 1);
    lua_pushboolean(L, h->isCopyrighted());
    return 1;
}

static int Header_isOriginal(lua_State* L) {
    TagLib::MPEG::Header* h = MPEG::Header::checkPtr(L, 1);
    lua_pushboolean(L, h->isOriginal());
    return 1;
}

static int Header_frameLength(lua_State* L) {
    TagLib::MPEG::Header* h = MPEG::Header::checkPtr(L, 1);
    lua_pushinteger(L, h->frameLength());
    return 1;
}

static
const luaL_Reg Header__index[] = {
#if LTAGLIB_HAS_MPEG_HEADER_CHANNELCONFIGURATION
    { "channelConfiguration", Header_channelConfiguration },
#endif
#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(2,0,0)
    { "isADTS", Header_isADTS },
#endif
#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,5,0)
    { "samplesPerFrame", Header_samplesPerFrame },
#endif
    { "isValid", Header_isValid },
    { "version", Header_version },
    { "layer", Header_layer },
    { "protectionEnabled", Header_protectionEnabled },
    { "bitrate", Header_bitrate },
    { "sampleRate", Header_sampleRate },
    { "isPadded", Header_isPadded },
    { "channelMode", Header_channelMode },
    { "isCopyrighted", Header_isCopyrighted },
    { "isOriginal", Header_isOriginal },
    { "frameLength", Header_frameLength },
    { NULL, NULL }
};

#define E(x) { #x, sizeof(#x) - 1, TagLib::MPEG::Header::x }

static const MPEG::Header::Version::enum_type versionTypes[] = {
    E(Version1), E(Version2), E(Version2_5)
#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(2,0,0)
    , E(Version4)
#endif
};

static const MPEG::Header::ChannelMode::enum_type channelModes[] = {
    E(Stereo), E(JointStereo), E(DualChannel), E(SingleChannel)
};

#if LTAGLIB_HAS_MPEG_HEADER_CHANNELCONFIGURATION
static const MPEG::Header::ChannelConfiguration::enum_type channelConfigurations[] = {
      E(Custom),
      E(FrontCenter),
      E(FrontLeftRight),
      E(FrontCenterLeftRight),
      E(FrontCenterLeftRightBackCenter),
      E(FrontCenterLeftRightBackLeftRight),
      E(FrontCenterLeftRightBackLeftRightLFE),
      E(FrontCenterLeftRightSideLeftRightBackLeftRightLFE)
};

#endif

LTAGLIB_PUBLIC
int luaopen_TagLib_MPEG_Header_Version(lua_State* L) {
    MPEG::Header::Version::open(L);
    return 1;
}

LTAGLIB_PUBLIC
int luaopen_TagLib_MPEG_Header_ChannelMode(lua_State* L) {
    MPEG::Header::ChannelMode::open(L);
    return 1;
}

#if LTAGLIB_HAS_MPEG_HEADER_CHANNELCONFIGURATION

LTAGLIB_PUBLIC
int luaopen_TagLib_MPEG_Header_ChannelConfiguration(lua_State* L) {
    MPEG::Header::ChannelConfiguration::open(L);
    return 1;

}

#endif

static int Header__submodules(lua_State* L) {
    luaL_requiref(L, "TagLib.MPEG.Header.Version", luaopen_TagLib_MPEG_Header_Version, 0);
    lua_setfield(L, -2, "Version");

    luaL_requiref(L, "TagLib.MPEG.Header.ChannelMode", luaopen_TagLib_MPEG_Header_ChannelMode, 0);
    lua_setfield(L, -2, "ChannelMode");

#if LTAGLIB_HAS_MPEG_HEADER_CHANNELCONFIGURATION
    luaL_requiref(L, "TagLib.MPEG.Header.ChannelConfiguration", luaopen_TagLib_MPEG_Header_ChannelConfiguration, 0);
    lua_setfield(L, -2, "ChannelConfiguration");
#endif
    return 0;
}

LTAGLIB_PUBLIC
int luaopen_TagLib_MPEG_Header(lua_State* L) {
    return MPEG::Header::open(L);
}

template<>
const UserdataTable MPEG::Header::base::mod = {
    Header__call, /* call */
    NULL,
    Header__submodules, /* init */
};


template<>
const UserdataMetatable MPEG::Header::base::metatable = {
    "TagLib::MPEG::Header", /* name */
    Header__index, /* indextable */
    NULL, /* indexfunc */
};

template<>
const MPEG::Header::Version::enum_type*
MPEG::Header::Version::m_values = versionTypes;

template<>
const size_t MPEG::Header::Version::m_len = sizeof(versionTypes) / sizeof(versionTypes[0]);

template<>
const MPEG::Header::ChannelMode::enum_type*
MPEG::Header::ChannelMode::m_values = channelModes;

template<>
const size_t MPEG::Header::ChannelMode::m_len = sizeof(channelModes) / sizeof(channelModes[0]);

#if LTAGLIB_HAS_MPEG_HEADER_CHANNELCONFIGURATION

template<>
const MPEG::Header::ChannelConfiguration::enum_type*
MPEG::Header::ChannelConfiguration::m_values = channelConfigurations;

template<>
const size_t MPEG::Header::ChannelConfiguration::m_len = sizeof(channelConfigurations) / sizeof(channelConfigurations[0]);

#endif

#include "../shared/enum.tcc"
template class Enum<TagLib::MPEG::Header::Version>;
template class Enum<TagLib::MPEG::Header::ChannelMode>;
#if LTAGLIB_HAS_MPEG_HEADER_CHANNELCONFIGURATION
template class Enum<TagLib::MPEG::Header::ChannelConfiguration>;
#endif

#include "../shared/userdata.tcc"
template class BaseUserdata<TagLib::MPEG::Header>;
