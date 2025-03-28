#include "synchronizedlyricsframe.h"

#if LTAGLIB_HAS_SYNCHRONIZEDLYRICSFRAME

#include "../tbytevector.h"
#include "../tstring.h"
#include "../tlist.h"

#define T ID3v2::SynchronizedLyricsFrame
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
            if(String::Type::isValid(L, 1)) {
                f = new TT(String::Type::checkValue(L, 1));
                break;
            }
            f = new TT(ByteVector::looseValue(L, 1));
            break;
        }
        default: break;
    }

    if(f == NULL) return luaL_error(L, "invalid arguments");
    T::pushPtr(L, f);
    return 1;
}

static int Frame_textEncoding(lua_State* L) {
    String::Type::pushValue(L, T::checkPtr(L,1)->textEncoding());
    return 1;
}

static int Frame_language(lua_State* L) {
    ByteVector::pushValue(L, T::checkPtr(L,1)->language());
    return 1;
}

static int Frame_timestampFormat(lua_State* L) {
    T::TimestampFormat::pushValue(L, T::checkPtr(L,1)->timestampFormat());
    return 1;
}

static int Frame_type(lua_State* L) {
    T::Type::pushValue(L, T::checkPtr(L,1)->type());
    return 1;
}

static int Frame_description(lua_State* L) {
    String::pushValue(L, T::checkPtr(L,1)->description());
    return 1;
}

static int Frame_synchedText(lua_State* L) {
    TT::SynchedTextList list(T::checkPtr(L,1)->synchedText());

    int i = 0;
    lua_newtable(L);

#if LTAGLIB_ATLEAST(LTAGLIB_2_0)
    for(TT::SynchedTextList::ConstIterator it = list.cbegin();
        it != list.cend();
        ++it)
#else
    for(TT::SynchedTextList::ConstIterator it = list.begin();
        it != list.end();
        ++it)
#endif
    {
        lua_newtable(L);
        lua_pushinteger(L, it->time);
        lua_setfield(L, -2, "time");
        String::pushValue(L, it->text);
        lua_setfield(L, -2, "text");
        lua_rawseti(L, -2, ++i);
    }
    return 1;
}

static int Frame_setTextEncoding(lua_State* L) {
    T::checkPtr(L,1)->setTextEncoding(String::Type::checkValue(L,2));
    lua_settop(L,1);
    return 1;
}

static int Frame_setLanguage(lua_State* L) {
    T::checkPtr(L,1)->setLanguage(ByteVector::looseValue(L,2));
    lua_settop(L,1);
    return 1;
}

static int Frame_setTimestampFormat(lua_State* L) {
    T::checkPtr(L,1)->setTimestampFormat(T::TimestampFormat::checkValue(L,2));
    lua_settop(L,1);
    return 1;
}

static int Frame_setType(lua_State* L) {
    T::checkPtr(L,1)->setType(T::Type::checkValue(L,2));
    lua_settop(L,1);
    return 1;
}

static int Frame_setDescription(lua_State* L) {
    T::checkPtr(L,1)->setDescription(String::checkValue(L,2));
    lua_settop(L,1);
    return 1;
}

static int Frame_setSynchedText(lua_State* L) {
    TT* f = T::checkPtr(L,1);
    TT::SynchedTextList list = TT::SynchedTextList();

    unsigned int time;
    TagLib::String text;


    luaL_checktype(L,2,LUA_TTABLE);

    int i;

    for(i=1; ;++i) {
        lua_rawgeti(L, 2, i);
        if(lua_isnil(L, -1)) break;

        lua_getfield(L, -1, "time");
        time = luaL_checkinteger(L, -1);
        lua_pop(L, 1);
        lua_getfield(L, -1, "text");
        text = String::checkValue(L, -1);
        lua_pop(L, 1);

        list.append(TT::SynchedText(time,text));

        lua_pop(L,1);
    }
    lua_pop(L,1);

    f->setSynchedText(list);
    lua_settop(L,1);
    return 1;
}

static const luaL_Reg Frame__index[] = {
    { "textEncoding", Frame_textEncoding },
    { "language", Frame_language },
    { "timestampFormat", Frame_timestampFormat },
    { "type", Frame_type },
    { "description", Frame_description },
    { "synchedText", Frame_synchedText },
    { "setTextEncoding", Frame_setTextEncoding },
    { "setLanguage", Frame_setLanguage },
    { "setTimestampFormat", Frame_setTimestampFormat },
    { "setType", Frame_setType },
    { "setDescription", Frame_setDescription },
    { "setSynchedText", Frame_setSynchedText },
    { NULL, NULL }
};

static int Frame__submodules(lua_State* L) {
    luaL_requiref(L, "TagLib.ID3v2.SynchronizedLyricsFrame.Type",
      luaopen_TagLib_ID3v2_SynchronizedLyricsFrame_Type, 0);
    lua_setfield(L, -2, "Type");
    luaL_requiref(L, "TagLib.ID3v2.SynchronizedLyricsFrame.TimestampFormat",
      luaopen_TagLib_ID3v2_SynchronizedLyricsFrame_TimestampFormat, 0);
    lua_setfield(L, -2, "TimestampFormat");
    return 0;
}

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_SynchronizedLyricsFrame(lua_State* L) {
    return T::open(L);
}

#define E(x) { #x, sizeof(#x) - 1, TT::x }
static const T::Type::enum_type lyricTypes[] = {
    E(Other), E(Lyrics), E(TextTranscription), E(Movement),
    E(Events), E(Chord), E(Trivia), E(WebpageUrls), E(ImageUrls)
};

static const T::TimestampFormat::enum_type timestampFormats[] = {
    E(Unknown), E(AbsoluteMpegFrames), E(AbsoluteMilliseconds)
};

LTAGLIB_PUBLIC int
luaopen_TagLib_ID3v2_SynchronizedLyricsFrame_Type(lua_State* L) {
    return T::Type::open(L);
}

LTAGLIB_PUBLIC int
luaopen_TagLib_ID3v2_SynchronizedLyricsFrame_TimestampFormat(lua_State* L) {
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
const T::Type::enum_type* T::Type::m_values = lyricTypes;

template<>
const size_t T::Type::m_len = sizeof(lyricTypes) / sizeof(lyricTypes[0]);

template<>
const T::TimestampFormat::enum_type* T::TimestampFormat::m_values = timestampFormats;

template<>
const size_t T::TimestampFormat::m_len = sizeof(timestampFormats) / sizeof(timestampFormats[0]);

#undef T
#include "../shared/enum.tcc"
template class LuaTagLib::Enum<TagLib::ID3v2::SynchronizedLyricsFrame::Type>;
template class LuaTagLib::Enum<TagLib::ID3v2::SynchronizedLyricsFrame::TimestampFormat>;

#include "../shared/userdata.tcc"
template class LuaTagLib::DerivedUserdata<TagLib::ID3v2::SynchronizedLyricsFrame, LuaTagLib::ID3v2::Frame>;

#endif
