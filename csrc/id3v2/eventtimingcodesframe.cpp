#include "eventtimingcodesframe.h"

#if LTAGLIB_HAS_EVENTTIMINGCODESFRAME

#include "../tbytevector.h"
#include "../tstring.h"
#include "../tlist.h"

#define T ID3v2::EventTimingCodesFrame
#define TT TagLib::T
#define XSTR(s) STR(s)
#define STR(s) #s
#define NAME XSTR(TT)

using namespace LuaTagLib;

static int Frame__call(lua_State* L) {
    int args = lua_gettop(L);
    TT* f = NULL;

    switch(args) {
        case 0: {
            f = new TT();
            break;
        }
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

static int Frame_timestampFormat(lua_State* L) {
    T::TimestampFormat::pushValue(L, T::checkPtr(L,1)->timestampFormat());
    return 1;
}

static int Frame_synchedEvents(lua_State* L) {
    TT::SynchedEventList list = T::checkPtr(L,1)->synchedEvents();

    int i = 0;
    lua_newtable(L);

#if LTAGLIB_ATLEAST(LTAGLIB_2_0)
    for(TT::SynchedEventList::ConstIterator it = list.cbegin();
        it != list.cend();
        ++it)
#else
    for(TT::SynchedEventList::ConstIterator it = list.begin();
        it != list.end();
        ++it)
#endif
    {
        lua_newtable(L);
        lua_pushinteger(L, it->time);
        lua_setfield(L, -2, "time");
        T::EventType::pushValue(L, it->type);
        lua_setfield(L, -2, "type");
        lua_rawseti(L, -2, ++i);
    }
    return 1;
}

static int Frame_setTimestampFormat(lua_State* L) {
    T::checkPtr(L,1)->setTimestampFormat(T::TimestampFormat::checkValue(L,2));
    lua_settop(L,1);
    return 1;
}

static int Frame_setSynchedEvents(lua_State* L) {
    TT* f = T::checkPtr(L,1);
    TT::SynchedEventList list = TT::SynchedEventList();

    unsigned int time;
    TT::EventType event;


    luaL_checktype(L,2,LUA_TTABLE);

    int i;

    for(i=1; ;++i) {
        lua_rawgeti(L, 2, i);
        if(lua_isnil(L, -1)) break;

        lua_getfield(L, -1, "time");
        time = luaL_checkinteger(L, -1);
        lua_pop(L, 1);
        lua_getfield(L, -1, "text");
        event = T::EventType::checkValue(L, -1);
        lua_pop(L, 1);

        list.append(TT::SynchedEvent(time,event));

        lua_pop(L,1);
    }
    lua_pop(L,1);

    f->setSynchedEvents(list);
    lua_settop(L,1);
    return 1;
}

static const luaL_Reg Frame__index[] = {
    { "timestampFormat", Frame_timestampFormat },
    { "synchedEvents", Frame_synchedEvents },
    { "setTimestampFormat", Frame_setTimestampFormat },
    { "setSynchedEvents", Frame_setSynchedEvents },
    { NULL, NULL }
};

static int Frame__submodules(lua_State* L) {
    luaL_requiref(L, "TagLib.ID3v2.EventTimingCodesFrame.EventType",
      luaopen_TagLib_ID3v2_EventTimingCodesFrame_EventType, 0);
    lua_setfield(L, -2, "EventType");
    luaL_requiref(L, "TagLib.ID3v2.EventTimingCodesFrame.TimestampFormat",
      luaopen_TagLib_ID3v2_EventTimingCodesFrame_TimestampFormat, 0);
    lua_setfield(L, -2, "TimestampFormat");
    return 0;
}

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_EventTimingCodesFrame(lua_State* L) {
    return T::open(L);
}

#define E(x) { #x, sizeof(#x) - 1, TT::x }
static const T::EventType::enum_type eventTypes[] = {
    E(Padding), E(EndOfInitialSilence), E(IntroStart), E(MainPartStart),
    E(OutroStart), E(OutroEnd), E(VerseStart), E(RefrainStart),
    E(InterludeStart), E(ThemeStart), E(VariationStart), E(KeyChange),
    E(TimeChange), E(MomentaryUnwantedNoise), E(SustainedNoise),
    E(SustainedNoiseEnd), E(IntroEnd), E(MainPartEnd), E(VerseEnd),
    E(RefrainEnd), E(ThemeEnd), E(Profanity), E(ProfanityEnd),
    E(NotPredefinedSynch0), E(NotPredefinedSynch1),
    E(NotPredefinedSynch2), E(NotPredefinedSynch3),
    E(NotPredefinedSynch4), E(NotPredefinedSynch5),
    E(NotPredefinedSynch6), E(NotPredefinedSynch7),
    E(NotPredefinedSynch8), E(NotPredefinedSynch9),
    E(NotPredefinedSynchA), E(NotPredefinedSynchB),
    E(NotPredefinedSynchC), E(NotPredefinedSynchD),
    E(NotPredefinedSynchE), E(NotPredefinedSynchF),
    E(AudioEnd), E(AudioFileEnds)
};

static const T::TimestampFormat::enum_type timestampFormats[] = {
    E(Unknown), E(AbsoluteMpegFrames), E(AbsoluteMilliseconds)
};

LTAGLIB_PUBLIC int
luaopen_TagLib_ID3v2_EventTimingCodesFrame_EventType(lua_State* L) {
    return T::EventType::open(L);
}

LTAGLIB_PUBLIC int
luaopen_TagLib_ID3v2_EventTimingCodesFrame_TimestampFormat(lua_State* L) {
    return T::TimestampFormat::open(L);
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
const T::EventType::enum_type* T::EventType::m_values = eventTypes;

template<>
const size_t T::EventType::m_len = sizeof(eventTypes) / sizeof(eventTypes[0]);

template<>
const T::TimestampFormat::enum_type* T::TimestampFormat::m_values = timestampFormats;

template<>
const size_t T::TimestampFormat::m_len = sizeof(timestampFormats) / sizeof(timestampFormats[0]);

#undef T

#include "../shared/enum.tcc"
template class Enum<TagLib::ID3v2::EventTimingCodesFrame::EventType>;
template class Enum<TagLib::ID3v2::EventTimingCodesFrame::TimestampFormat>;

#include "../shared/userdata.tcc"
template class DerivedUserdata<TagLib::ID3v2::EventTimingCodesFrame, LuaTagLib::ID3v2::Frame>;

#endif
