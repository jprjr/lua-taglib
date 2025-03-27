#include "id3v2frame.h"

#include "../tbytevector.h"
#include "../tstring.h"
#include "../tstringlist.h"

#include "id3v2header.h"

#define T ID3v2::Frame
#define TT TagLib::T

using namespace LuaTagLib;

static int Frame_frameID(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    ByteVector::pushValue(L, f->frameID());
    return 1;
}

static int Frame_size(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    lua_pushinteger(L, f->size());
    return 1;
}

static int Frame_setData(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    f->setData(ByteVector::looseValue(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Frame_setText(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    f->setText(String::checkValue(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Frame_toString(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    String::pushValue(L, f->toString());
    return 1;
}

static int Frame_render(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    ByteVector::pushValue(L, f->render());
    return 1;
}

#if LTAGLIB_HAS_ID3V2_FRAME_HEADER
static int Frame_header(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    T::Header::pushPtr(L, f->header(), 1);
    return 1;
}

static int Frame_headerSize(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    lua_pushinteger(L, f->headerSize());
    return 1;
}

#endif

#if LTAGLIB_ATLEAST(LTAGLIB_2_0)
static int Frame_toStringList(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    StringList::pushValue(L, f->toStringList());
    return 1;
}
#endif

static const luaL_Reg Frame__index[] = {
    { "frameID", Frame_frameID },
    { "size", Frame_size },
#if LTAGLIB_HAS_ID3V2_FRAME_HEADER
    { "headerSize", Frame_headerSize },
    { "header", Frame_header },
#endif
    { "setData", Frame_setData },
    { "setText", Frame_setText },
    { "toString", Frame_toString },
    { "render", Frame_render },
#if LTAGLIB_ATLEAST(LTAGLIB_2_0)
    { "toStringList", Frame_toStringList },
#endif
    { NULL, NULL }
};


#if LTAGLIB_UNDER(LTAGLIB_2_0)
static int Frame_static_headerSize(lua_State* L) {
    lua_pushinteger(L, TT::headerSize());
    return 1;
}
#endif

static int Frame_static_textDelimiter(lua_State* L) {
    ByteVector::pushValue(L, TT::textDelimiter(String::Type::checkValue(L, 1)));
    return 1;
}

#if LTAGLIB_ATLEAST(LTAGLIB_1_8) && LTAGLIB_UNDER(LTAGLIB_2_0)
static int Frame_static_createTextualFrame(lua_State* L) {
    T::pushPtr(L, TT::createTextualFrame(
      String::checkValue(L,1),
      String::checkValue(L,2)));
    return 1;
}
#endif

#if LTAGLIB_ATLEAST(LTAGLIB_2_0)
static int Frame_static_keyToFrameID(lua_State* L) {
    ByteVector::pushValue(
      L,
      TT::keyToFrameID(String::checkValue(L,1))
    );
    return 1;
}

static int Frame_static_frameIDToKey(lua_State* L) {
    String::pushValue(
      L,
      TT::frameIDToKey(ByteVector::looseValue(L,1))
    );
    return 1;
}
#endif

static const luaL_Reg Frame_static__index[] = {
#if LTAGLIB_UNDER(LTAGLIB_2_0)
    { "headerSize", Frame_static_headerSize },
#endif
    { "textDelimiter", Frame_static_textDelimiter },
#if LTAGLIB_ATLEAST(LTAGLIB_1_8) && LTAGLIB_UNDER(LTAGLIB_2_0)
    { "createTextualFrame", Frame_static_createTextualFrame },
#endif
#if LTAGLIB_ATLEAST(LTAGLIB_2_0)
    { "keyToFrameID", Frame_static_keyToFrameID },
    { "frameIDToKey", Frame_static_frameIDToKey },
#endif
    { NULL, NULL }
};

static int Frame__submodules(lua_State* L) {
#if LTAGLIB_ATLEAST(LTAGLIB_2_0)
    String::pushValue(L, TT::instrumentPrefix);
    lua_setfield(L, -2, "instrumentPrefix");

    String::pushValue(L, TT::commentPrefix);
    lua_setfield(L, -2, "commentPrefix");

    String::pushValue(L, TT::lyricsPrefix);
    lua_setfield(L, -2, "lyricsPrefix");

    String::pushValue(L, TT::urlPrefix);
    lua_setfield(L, -2, "urlPrefix");
#endif
#if LTAGLIB_HAS_ID3V2_FRAME_HEADER
    luaL_requiref(L, "TagLib.ID3v2.Frame.Header", luaopen_TagLib_ID3v2_Frame_Header, 0);
    lua_setfield(L, -2, "Header");
#else
    (void)L;
#endif
    return 0;
}

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_Frame(lua_State* L) {
    return T::open(L);
}

template<>
const UserdataTable T::base::mod = {
    NULL,
    Frame_static__index,
    Frame__submodules,
};


template<>
const UserdataMetatable ID3v2::Frame::base::metatable = {
    "TagLib::ID3v2::Frame", /* name */
    Frame__index, /* indextable */
    NULL, /* indexfunc */
};

#undef T
#include "../shared/userdata.tcc"
template class LuaTagLib::BaseUserdata<TagLib::ID3v2::Frame>;

#define T ID3v2::Frame

#if LTAGLIB_HAS_ID3V2_FRAME_HEADER

static int Header__call(lua_State* L) {
    int args = lua_gettop(L);
    TT::Header* h = NULL;

    switch(args) {
        case 1: {
            h = new TT::Header(ByteVector::looseValue(L, 1));
            break;
        }
        case 2: {
            h = new TT::Header(ByteVector::looseValue(L, 1), luaL_checkinteger(L, 2));
            break;
        }
        default: break;
    }

    if(h == NULL) return luaL_error(L,"invalid arguments");

    T::Header::pushPtr(L, h);
    return 1;
}


static int Header_setData(lua_State* L) {
    TT::Header* h = T::Header::checkPtr(L, 1);
    int args = lua_gettop(L);

    switch(args) {
        case 2: {
            h->setData(ByteVector::looseValue(L, 2));
            break;
        }
        case 3: {
            h->setData(ByteVector::looseValue(L, 2), luaL_checkinteger(L, 3));
            break;
        }
        default: {
            return luaL_error(L, "invalid arguments");
        }
    }
    lua_settop(L,1);
    return 1;
}

static int Header_frameID(lua_State* L) {
    TT::Header* h = T::Header::checkPtr(L, 1);
    ByteVector::pushValue(L, h->frameID());
    return 1;
}

static int Header_setFrameID(lua_State* L) {
    TT::Header* h = T::Header::checkPtr(L, 1);
    h->setFrameID(ByteVector::looseValue(L,2));
    lua_settop(L,1);
    return 1;
}

static int Header_frameSize(lua_State* L) {
    TT::Header* h = T::Header::checkPtr(L, 1);
    lua_pushinteger(L, h->frameSize());
    return 1;
}

static int Header_setFrameSize(lua_State* L) {
    TT::Header* h = T::Header::checkPtr(L, 1);
    h->setFrameSize(luaL_checkinteger(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Header_version(lua_State* L) {
    TT::Header* h = T::Header::checkPtr(L, 1);
    lua_pushinteger(L, h->version());
    return 1;
}

static int Header_setVersion(lua_State* L) {
    TT::Header* h = T::Header::checkPtr(L, 1);
    h->setVersion(luaL_checkinteger(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Header_size(lua_State* L) {
    TT::Header* h = T::Header::checkPtr(L, 1);
    lua_pushinteger(L, h->size());
    return 1;
}

static int Header_tagAlterPreservation(lua_State* L) {
    TT::Header* h = T::Header::checkPtr(L, 1);
    lua_pushboolean(L, h->tagAlterPreservation());
    return 1;
}

static int Header_setTagAlterPreservation(lua_State* L) {
    TT::Header* h = T::Header::checkPtr(L, 1);
    h->setTagAlterPreservation(lua_toboolean(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Header_fileAlterPreservation(lua_State* L) {
    TT::Header* h = T::Header::checkPtr(L, 1);
    lua_pushboolean(L, h->fileAlterPreservation());
    return 1;
}

static int Header_readOnly(lua_State* L) {
    TT::Header* h = T::Header::checkPtr(L, 1);
    lua_pushboolean(L, h->readOnly());
    return 1;
}

static int Header_groupingIdentity(lua_State* L) {
    TT::Header* h = T::Header::checkPtr(L, 1);
    lua_pushboolean(L, h->groupingIdentity());
    return 1;
}

static int Header_compression(lua_State* L) {
    TT::Header* h = T::Header::checkPtr(L, 1);
    lua_pushboolean(L, h->compression());
    return 1;
}

static int Header_encryption(lua_State* L) {
    TT::Header* h = T::Header::checkPtr(L, 1);
    lua_pushboolean(L, h->encryption());
    return 1;
}

static int Header_unsynchronisation(lua_State* L) {
    TT::Header* h = T::Header::checkPtr(L, 1);
    lua_pushboolean(L, h->unsynchronisation());
    return 1;
}

static int Header_dataLengthIndicator(lua_State* L) {
    TT::Header* h = T::Header::checkPtr(L, 1);
    lua_pushboolean(L, h->dataLengthIndicator());
    return 1;
}

static int Header_render(lua_State* L) {
    TT::Header* h = T::Header::checkPtr(L, 1);
    ByteVector::pushValue(L, h->render());
    return 1;
}

static const luaL_Reg Header__index[] = {
    { "setData", Header_setData },
    { "frameID", Header_frameID },
    { "setFrameID", Header_setFrameID },
    { "frameSize", Header_frameSize },
    { "setFrameSize", Header_setFrameSize },
    { "version", Header_version },
    { "setVersion", Header_setVersion },
    { "size", Header_size },
    { "tagAlterPreservation", Header_tagAlterPreservation },
    { "setTagAlterPreservation", Header_setTagAlterPreservation },
    { "fileAlterPreservation", Header_fileAlterPreservation },
    { "readOnly", Header_readOnly },
    { "groupingIdentity", Header_groupingIdentity },
    { "compression", Header_compression },
    { "encryption", Header_encryption },
    { "unsynchronisation", Header_unsynchronisation },
    { "dataLengthIndicator", Header_dataLengthIndicator },
    { "render", Header_render },
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_Frame_Header(lua_State* L) {
    return T::Header::open(L);
}

template<>
const UserdataTable T::Header::base::mod = {
    Header__call,
    NULL,
    NULL,
};


template<>
const UserdataMetatable T::Header::base::metatable = {
    "TagLib::ID3v2::Frame::Header", /* name */
    Header__index, /* indextable */
    NULL, /* indexfunc */
};

template class LuaTagLib::BaseUserdata<TagLib::ID3v2::Frame::Header>;

#endif
