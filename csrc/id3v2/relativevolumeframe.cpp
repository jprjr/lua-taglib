#include "relativevolumeframe.h"

#if LTAGLIB_HAS_RELATIVEVOLUMEFRAME

#include "../tbytevector.h"
#include "../tlist.h"

#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,5,0)
/* needed for identification/setIdentification */
#include "../tstring.h"
#endif

#define T ID3v2::RelativeVolumeFrame
#define TT TagLib::T
#define XSTR(s) STR(s)
#define STR(s) #s
#define NAME XSTR(TT)

using namespace LuaTagLib;

static int Frame__call(lua_State* L) {
    int args = lua_gettop(L);
    TT* f = NULL;

    switch(args) {
        /* it seems like the empty constructor is in
         * the headers starting with 1.2.0 but not
         * actually exported until 1.5.0 */
#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,5,0)
        case 0: {
            f = new TT();
            break;
        }
#endif
        case 1: {
            f = new TT(ByteVector::looseValue(L, 1));
            break;
        }
        default: break;
    }

    if(f == NULL) return luaL_error(L, "invalid arguments");
    T::pushPtr(L, f);
    return 1;
}

/* TODO create a proper subclass so we can __call,pushValue/checkValue on cheakPeakVolume */

static inline TT::PeakVolume checkPeakVolume(lua_State* L, int idx) {
    TT::PeakVolume peak;
    TagLib::ByteVector peakVolume;

    if(lua_type(L, idx) != LUA_TTABLE) {
        luaL_typeerror(L, idx, NAME "::PeakVolume");
        return peak;
    }

    if(lua_getfield(L, idx, "bitsRepresentingPeak") == LUA_TNIL) {
        lua_pop(L, 1);
        luaL_typeerror(L, idx, NAME "::PeakVolume");
        return peak;
    }
    peak.bitsRepresentingPeak = lua_tointeger(L, -1);
    lua_pop(L, 1);

    if(lua_getfield(L, idx, "peakVolume") == LUA_TNIL) {
        lua_pop(L, 1);
        luaL_typeerror(L, idx, NAME "::PeakVolume");
        return peak;
    }

    peak.peakVolume = ByteVector::looseValue(L, -1);
    lua_pop(L, 1);

    return peak;
}

static inline void pushPeakVolume(lua_State* L, const TT::PeakVolume& peak) {
    lua_newtable(L);
    lua_pushinteger(L, peak.bitsRepresentingPeak);
    lua_setfield(L, -2, "bitsRepresentingPeak");
    ByteVector::pushValue(L, peak.peakVolume);
    lua_setfield(L, -2, "peakVolume");
}

#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,4,0)
static int Frame_channels(lua_State* L) {
    ValueList< TagLib::List<TT::ChannelType>, T::ChannelType
    >::pushValue(L, T::checkPtr(L,1)->channels());
    return 1;
}
#endif

#if LTAGLIB_UNDER(LTAGLIB_1_12)
static int Frame_channelType(lua_State* L) {
    T::ChannelType::pushValue(L,
      T::checkPtr(L,1)->channelType()
    );
    return 1;
}

static int Frame_setChannelType(lua_State* L) {
    T::checkPtr(L,1)->setChannelType(
      T::ChannelType::checkValue(L, 2)
    );
    lua_settop(L,1);
    return 1;
}
#endif

static int Frame_volumeAdjustmentIndex(lua_State* L) {
    lua_pushinteger(L,
      T::checkPtr(L,1)->volumeAdjustmentIndex()
    );
    return 1;
}

static int Frame_setVolumeAdjustmentIndex(lua_State* L) {
    T::checkPtr(L,1)->setVolumeAdjustmentIndex(
      luaL_checkinteger(L, 2)
    );
    lua_settop(L,1);
    return 1;
}

static int Frame_volumeAdjustment(lua_State* L) {
    lua_pushnumber(L,
      T::checkPtr(L,1)->volumeAdjustment()
    );
    return 1;
}

static int Frame_setVolumeAdjustment(lua_State* L) {
    T::checkPtr(L,1)->setVolumeAdjustment(
      luaL_checknumber(L, 2)
    );
    lua_settop(L,1);
    return 1;
}

static int Frame_peakVolume(lua_State* L) {
    pushPeakVolume(L,
      T::checkPtr(L,1)->peakVolume()
    );
    return 1;
}

static int Frame_setPeakVolume(lua_State* L) {
    T::checkPtr(L,1)->setPeakVolume(
      checkPeakVolume(L, 2)
    );
    lua_settop(L,1);
    return 1;
}

#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,5,0)
static int Frame_identification(lua_State* L) {
    String::pushValue(L,
      T::checkPtr(L,1)->identification()
    );
    return 1;
}

static int Frame_setIdentification(lua_State* L) {
    T::checkPtr(L,1)->setIdentification(
      String::checkValue(L, 2)
    );
    lua_settop(L,1);
    return 1;
}
#endif

static const luaL_Reg Frame__index[] = {
#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,5,0)
    { "identification", Frame_identification },
    { "setIdentification", Frame_setIdentification },
#endif
#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,4,0)
    { "channels", Frame_channels },
#endif
#if LTAGLIB_UNDER(LTAGLIB_1_12)
    { "channelType", Frame_channelType },
    { "setChannelType", Frame_setChannelType },
#endif
    { "volumeAdjustmentIndex", Frame_volumeAdjustmentIndex },
    { "setVolumeAdjustmentIndex", Frame_setVolumeAdjustmentIndex },
    { "volumeAdjustment", Frame_volumeAdjustment },
    { "setVolumeAdjustment", Frame_setVolumeAdjustment },
    { "peakVolume", Frame_peakVolume },
    { "setPeakVolume", Frame_setPeakVolume },
    { NULL, NULL }
};

static int Frame__submodules(lua_State* L) {
    luaL_requiref(L, "TagLib.ID3v2.RelativeVolumeFrame.ChannelType",
      luaopen_TagLib_ID3v2_RelativeVolumeFrame_ChannelType, 0);
    lua_setfield(L, -2, "ChannelType");
    return 0;
}

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_RelativeVolumeFrame(lua_State* L) {
    return T::open(L);
}

#define E(x) { #x, sizeof(#x) - 1, TT::x }
static const T::ChannelType::enum_type channelTypes[] = {
    E(Other), E(MasterVolume), E(FrontRight), E(FrontLeft),
    E(BackRight), E(BackLeft), E(FrontCentre), E(BackCentre),
    E(Subwoofer)
};

LTAGLIB_PUBLIC int
luaopen_TagLib_ID3v2_RelativeVolumeFrame_ChannelType(lua_State* L) {
    return T::ChannelType::open(L);
}

template<>
const UserdataTable T::base::mod = {
    Frame__call,
    NULL,
    Frame__submodules,
};


template<>
const UserdataMetatable T::base::metatable = {
    NAME, /* name */
    Frame__index, /* indextable */
    NULL, /* indexfunc */
};

template<>
const T::ChannelType::enum_type* T::ChannelType::m_values = channelTypes;

template<>
const size_t T::ChannelType::m_len = sizeof(channelTypes) / sizeof(channelTypes[0]);

template<>
const char * ValueList< TagLib::List<TT::ChannelType>, T::ChannelType>::base::__name =
  NAME "::ChannelType";

#undef T
#include "../shared/enum.tcc"
template class LuaTagLib::Enum<TagLib::ID3v2::RelativeVolumeFrame::ChannelType>;

#include "../shared/userdata.tcc"
template class LuaTagLib::DerivedUserdata<TagLib::ID3v2::RelativeVolumeFrame, LuaTagLib::ID3v2::Frame>;

#endif
