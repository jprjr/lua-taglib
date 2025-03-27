#include "tableofcontentsframe.h"

#if LTAGLIB_HAS_TABLEOFCONTENTSFRAME

#include "../tbytevector.h"
#include "../tstring.h"
#include "../tlist.h"
#include "../tpropertymap.h"
#include "../tbytevectorlist.h"
#include "id3v2header.h"
#include "id3v2tag.h"

#define T ID3v2::TableOfContentsFrame
#define TT TagLib::T
#define XSTR(s) STR(s)
#define STR(s) #s
#define NAME XSTR(TT)

using namespace LuaTagLib;

static int Frame__call(lua_State* L) {
    int args = lua_gettop(L);
    TT* f = NULL;

    switch(args) {
        case 1: {
            f = new TT(ByteVector::looseValue(L,1));
            break;
        }
        case 2: {
            if(ID3v2::Header::isValid(L, 1)) {
                f = new TT(ID3v2::Header::checkPtr(L,1), ByteVector::looseValue(L,2));
                break;
            }
            f = new TT(ByteVector::looseValue(L,1), ByteVectorList::looseValue(L, 2));
            break;
        }
        case 3: {
            f = new TT(
              ByteVector::looseValue(L,1),
              ByteVectorList::looseValue(L, 2),
              PtrList<TagLib::ID3v2::FrameList, ID3v2::Frame>::checkPtr(L,3));
            ID3v2::Frame::unmanageListRefs(L, 3);
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

static int Frame_isTopLevel(lua_State* L) {
    lua_pushboolean(L, T::checkPtr(L,1)->isTopLevel());
    return 1;
}

static int Frame_isOrdered(lua_State* L) {
    lua_pushboolean(L, T::checkPtr(L,1)->isTopLevel());
    return 1;
}

static int Frame_entryCount(lua_State* L) {
    lua_pushinteger(L,T::checkPtr(L,1)->entryCount());
    return 1;
}

static int Frame_childElements(lua_State* L) {
    ByteVectorList::pushValue(L, T::checkPtr(L,1)->childElements());
    return 1;
}


static int Frame_setElementID(lua_State* L) {
    T::checkPtr(L,1)->setElementID(ByteVector::looseValue(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Frame_setIsTopLevel(lua_State* L) {
    T::checkPtr(L,1)->setIsTopLevel(lua_toboolean(L,2));
    lua_settop(L,1);
    return 1;
}

static int Frame_setIsOrdered(lua_State* L) {
    T::checkPtr(L,1)->setIsOrdered(lua_toboolean(L,2));
    lua_settop(L,1);
    return 1;
}

static int Frame_setChildElements(lua_State* L) {
    T::checkPtr(L,1)->setChildElements(ByteVectorList::looseValue(L,2));
    lua_settop(L,1);
    return 1;
}

static int Frame_addChildElement(lua_State* L) {
    T::checkPtr(L,1)->addChildElement(ByteVector::looseValue(L,2));
    lua_settop(L,1);
    return 1;
}

static int Frame_removeChildElement(lua_State* L) {
    T::checkPtr(L,1)->removeChildElement(ByteVector::looseValue(L,2));
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
    { "isTopLevel", Frame_isTopLevel },
    { "isOrdered", Frame_isOrdered },
    { "entryCount", Frame_entryCount },
    { "childElements", Frame_childElements },
    { "setElementID", Frame_setElementID },
    { "setIsTopLevel", Frame_setIsTopLevel },
    { "setIsOrdered", Frame_setIsOrdered },
    { "setChildElements", Frame_setChildElements },
    { "addChildElement", Frame_addChildElement },
    { "removeChildElement", Frame_removeChildElement },
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

static int Frame_static_findTopLevel(lua_State* L) {
    TT* f = TT::findTopLevel(ID3v2::Tag::checkPtr(L,1));
    if(f == NULL) return 0;
    T::pushPtr(L, f, 1);
    return 1;
}

static const luaL_Reg Frame__static[] = {
    { "findByElementID", Frame_static_findByElementID },
    { "findTopLevel", Frame_static_findTopLevel },
    { NULL, NULL },
};

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_TableOfContentsFrame(lua_State* L) {
    return T::open(L);
}

template<>
const UserdataTable T::base::mod = {
    Frame__call,
    Frame__static,
    NULL
};

template<>
const UserdataMetatable T::base::metatable = {
    NAME, /* name */
    Frame__index, /* indextable */
    NULL, /* indexfunc */
};

#undef T
#include "../shared/userdata.tcc"
template class LuaTagLib::DerivedUserdata<TagLib::ID3v2::TableOfContentsFrame, LuaTagLib::ID3v2::Frame>;

#endif

