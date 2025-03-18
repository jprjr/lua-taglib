#include "chapterframe.h"

#if LTAGLIB_HAS_CHAPTERFRAME

#include "../tbytevector.h"
#include "../tstring.h"
#include "../tlist.h"
#include "../tpropertymap.h"
#include "id3v2header.h"
#include "id3v2tag.h"

#define T ID3v2::ChapterFrame
#define TT TagLib::T
#define XSTR(s) STR(s)
#define STR(s) #s
#define NAME XSTR(TT)

using namespace LuaTagLib;

static int Frame__call(lua_State* L) {
    int args = lua_gettop(L);
    TT* f = NULL;

    switch(args) {
        case 2: {
            f = new TT(ID3v2::Header::checkPtr(L,1), ByteVector::looseValue(L,2));
            break;
        }
        case 5: {
            f = new TT(
              ByteVector::looseValue(L,1),
              luaL_checkinteger(L, 2), luaL_checkinteger(L, 3),
              luaL_checkinteger(L, 4), luaL_checkinteger(L, 5));
            break;
        }
        case 6: {
            f = new TT(
              ByteVector::looseValue(L,1),
              luaL_checkinteger(L, 2), luaL_checkinteger(L, 3),
              luaL_checkinteger(L, 4), luaL_checkinteger(L, 5),
              PtrList<TagLib::ID3v2::FrameList, ID3v2::Frame>::checkPtr(L,6));
            ID3v2::Frame::unmanageListRefs(L, 6);
            break;
        }
        default: break;
    }

    if(f == NULL) return luaL_error(L, "invalid arguments");
    T::pushPtr(L, f);
    return 1;
}


static int Frame_elementID(lua_State* L) {
    ByteVector::pushValue(L, T::checkPtr(L,1)->elementID());
    return 1;
}

static int Frame_startTime(lua_State* L) {
    lua_pushinteger(L,T::checkPtr(L,1)->startTime());
    return 1;
}

static int Frame_endTime(lua_State* L) {
    lua_pushinteger(L,T::checkPtr(L,1)->endTime());
    return 1;
}

static int Frame_startOffset(lua_State* L) {
    lua_pushinteger(L,T::checkPtr(L,1)->startOffset());
    return 1;
}

static int Frame_endOffset(lua_State* L) {
    lua_pushinteger(L,T::checkPtr(L,1)->endOffset());
    return 1;
}

static int Frame_setElementID(lua_State* L) {
    T::checkPtr(L,1)->setElementID(ByteVector::looseValue(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Frame_setStartTime(lua_State* L) {
    T::checkPtr(L,1)->setStartTime(luaL_checkinteger(L,2));
    lua_settop(L,1);
    return 1;
}

static int Frame_setEndTime(lua_State* L) {
    T::checkPtr(L,1)->setEndTime(luaL_checkinteger(L,2));
    lua_settop(L,1);
    return 1;
}

static int Frame_setStartOffset(lua_State* L) {
    T::checkPtr(L,1)->setStartOffset(luaL_checkinteger(L,2));
    lua_settop(L,1);
    return 1;
}

static int Frame_setEndOffset(lua_State* L) {
    T::checkPtr(L,1)->setEndOffset(luaL_checkinteger(L,2));
    lua_settop(L,1);
    return 1;
}

static int Frame_embeddedFrameListMap(lua_State* L) {
    ID3v2::FrameListMap::pushRef(L,T::checkPtr(L,1)->embeddedFrameListMap(),1);
    return 1;
}

static int Frame_embeddedFrameList(lua_State* L) {
    int args = lua_gettop(L);

    switch(args) {
        case 1: {
            ID3v2::FrameList::pushRef(L,T::checkPtr(L,1)->embeddedFrameList(),1);
            break;
        }
        case 2: {
            ID3v2::FrameList::pushRef(L,T::checkPtr(L,1)->embeddedFrameList(
              ByteVector::looseValue(L,2)
            ), 1);
            break;
        }
        default: return luaL_error(L,"invalid arguments");
    }
    return 1;
}

static int Frame_addEmbeddedFrame(lua_State* L) {
    T::checkPtr(L,1)->addEmbeddedFrame(ID3v2::Frame::checkPtr(L,2));
    ID3v2::Frame::unmanageRefs(L, 2);
    lua_settop(L,1);
    return 1;
}

static int Frame_removeEmbeddedFrame(lua_State* L) {
    int args = lua_gettop(L);
    bool del = false;

    switch(args) {
        case 2: {
            T::checkPtr(L,1)->removeEmbeddedFrame(ID3v2::Frame::checkPtr(L,2));
            break;
        }
        case 3: {
            del = lua_toboolean(L,3);
            T::checkPtr(L,1)->removeEmbeddedFrame(ID3v2::Frame::checkPtr(L,2), del);
            if(del) ID3v2::Frame::unmanageRefs(L, 2);
            break;
        }
        default: return luaL_error(L, "invalid arguments");
    }
    lua_settop(L,1);
    return 1;
}

static int Frame_removeEmbeddedFrames(lua_State* L) {
    T::checkPtr(L,1)->removeEmbeddedFrames(ByteVector::looseValue(L,2));
    lua_settop(L,1);
    return 1;
}

static int Frame_asProperties(lua_State* L) {
    PropertyMap::pushValue(L, T::checkPtr(L,1)->asProperties());
    return 1;
}

static const luaL_Reg Frame__index[] = {
    { "elementID", Frame_elementID },
    { "startTime", Frame_startTime },
    { "endTime", Frame_endTime },
    { "startOffset", Frame_startOffset },
    { "endOffset", Frame_endOffset },
    { "setElementID", Frame_setElementID },
    { "setStartTime", Frame_setStartTime },
    { "setEndTime", Frame_setEndTime },
    { "setStartOffset", Frame_setStartOffset },
    { "setEndOffset", Frame_setEndOffset },
    { "embeddedFrameListMap", Frame_embeddedFrameListMap },
    { "embeddedFrameList", Frame_embeddedFrameList },
    { "addEmbeddedFrame", Frame_addEmbeddedFrame },
    { "removeEmbeddedFrame", Frame_removeEmbeddedFrame },
    { "removeEmbeddedFrames", Frame_removeEmbeddedFrames },
    { "asProperties", Frame_asProperties },
    { NULL, NULL }
};

static int Frame_static_findByElementID(lua_State* L) {
    TT* f = TT::findByElementID(ID3v2::Tag::checkPtr(L,1), ByteVector::looseValue(L, 2));
    if(f == NULL) return 0;
    T::pushPtr(L, f, 1);
    return 1;
}

static const luaL_Reg Frame__static[] = {
    { "findByElementID", Frame_static_findByElementID },
    { NULL, NULL },
};

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_ChapterFrame(lua_State* L) {
    return T::open(L);
}

template<>
const UserdataMetatable T::base::metatable = {
    NAME, /* name */
    Frame__index, /* indextable */
    NULL, /* indexfunc */
};

template<>
const UserdataTable ID3v2::ChapterFrame::base::mod = {
    Frame__call,
    Frame__static,
    NULL
};

#undef T
#include "../shared/userdata.tcc"
template class DerivedUserdata<TagLib::ID3v2::ChapterFrame, LuaTagLib::ID3v2::Frame>;

#endif
