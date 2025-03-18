#include "mpegproperties.h"

#include "mpegheader.h"
#include "mpegfile.h"

#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,5,0)
#include "xingheader.h"
#endif

using namespace LuaTagLib;

static int Properties__call(lua_State* L) {
    int args = lua_gettop(L);
    TagLib::MPEG::Properties* p = NULL;

    switch(args) {
        case 1: {
            p = new TagLib::MPEG::Properties(MPEG::File::checkPtr(L, 1));
            break;
        }
        case 2: {
            p = new TagLib::MPEG::Properties(MPEG::File::checkPtr(L, 1), AudioProperties::ReadStyle::checkValue(L, 2));
            break;
        }
        default: break;
    }

    if(p == NULL) return luaL_error(L, "invalid arguments");
    MPEG::Properties::pushPtr(L,p);
    return 1;
}

#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(2,0,0)
static int Properties_channelConfiguration(lua_State* L) {
    TagLib::MPEG::Properties* ap = MPEG::Properties::checkPtr(L, 1);
    MPEG::Header::ChannelConfiguration::pushValue(L, ap->channelConfiguration());
    return 1;
}

static int Properties_isADTS(lua_State* L) {
    TagLib::MPEG::Properties* ap = MPEG::Properties::checkPtr(L, 1);
    lua_pushboolean(L, ap->isADTS());
    return 1;
}
#endif

#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,5,0)
static int Properties_xingHeader(lua_State* L) {
    TagLib::MPEG::Properties* ap = MPEG::Properties::checkPtr(L, 1);
    /* TODO method of enforcing const pointers */
    MPEG::XingHeader::pushPtr(L, (TagLib::MPEG::XingHeader*) ap->xingHeader(), 1);
    return 1;
}
#endif

#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,5,0)
static int Properties_protectionEnabled(lua_State* L) {
    TagLib::MPEG::Properties* ap = MPEG::Properties::checkPtr(L, 1);
    lua_pushboolean(L, ap->protectionEnabled());
    return 1;
}
#endif

static int Properties_version(lua_State* L) {
    TagLib::MPEG::Properties* ap = MPEG::Properties::checkPtr(L, 1);
    MPEG::Header::Version::pushValue(L, ap->version());
    return 1;
}

static int Properties_layer(lua_State* L) {
    TagLib::MPEG::Properties* ap = MPEG::Properties::checkPtr(L, 1);
    lua_pushinteger(L, ap->layer());
    return 1;
}

static int Properties_channelMode(lua_State* L) {
    TagLib::MPEG::Properties* ap = MPEG::Properties::checkPtr(L, 1);
    MPEG::Header::ChannelMode::pushValue(L, ap->channelMode());
    return 1;
}

static int Properties_isCopyrighted(lua_State* L) {
    TagLib::MPEG::Properties* ap = MPEG::Properties::checkPtr(L, 1);
    lua_pushboolean(L, ap->isCopyrighted());
    return 1;
}

static int Properties_isOriginal(lua_State* L) {
    TagLib::MPEG::Properties* ap = MPEG::Properties::checkPtr(L, 1);
    lua_pushboolean(L, ap->isOriginal());
    return 1;
}

static
const luaL_Reg Properties__index[] = {
#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(2,0,0)
    { "channelConfiguration", Properties_channelConfiguration },
    { "isADTS", Properties_isADTS },
#endif
#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,5,0)
    { "xingHeader", Properties_xingHeader },
#endif
#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,5,0)
    { "protectionEnabled", Properties_protectionEnabled },
#endif
    { "version", Properties_version },
    { "layer", Properties_layer },
    { "channelMode", Properties_channelMode },
    { "isCopyrighted", Properties_isCopyrighted },
    { "isOriginal", Properties_isOriginal },
    { NULL, NULL },
};

LTAGLIB_PUBLIC
int luaopen_TagLib_MPEG_Properties(lua_State *L) {
    return MPEG::Properties::open(L);
}

template<>
const UserdataTable MPEG::Properties::base::mod = {
    Properties__call,
    NULL,
    NULL,
};

template<>
const UserdataMetatable MPEG::Properties::base::metatable = {
    "TagLib::MPEG::Properties", /* name */
    Properties__index, /* indextable */
    NULL, /* indexfunc */
};

#include "../shared/userdata.tcc"
template class DerivedUserdata<TagLib::MPEG::Properties, LuaTagLib::AudioProperties>;
