#include "id3v2tag.h"

#include "id3v2.h"
#include "id3v2header.h"
#include "id3v2footer.h"
#include "id3v2extendedheader.h"

#include "../tfile.h"
#include "../tstring.h"

using namespace LuaTagLib;

static int Tag__call(lua_State* L) {
    int args = lua_gettop(L);
    TagLib::ID3v2::Tag* t = NULL;

    switch(args) {
        case 0: {
            t = new TagLib::ID3v2::Tag();
            break;
        }
        case 2: {
            t = new TagLib::ID3v2::Tag(LuaTagLib::File::checkPtr(L,1), luaL_checkinteger(L, 2));
            break;
        }
        default: break;
    }

    if(t == NULL) return luaL_error(L, "invalid arguments");
    ID3v2::Tag::pushPtr(L, t);
    return 1;
}

#if LTAGLIB_UNDER(LTAGLIB_1_12)
static int Tag_footer(lua_State* L) {
    TagLib::ID3v2::Tag* tag = ID3v2::Tag::checkPtr(L, 1);
    ID3v2::Footer::pushPtr(L, tag->footer(), 1);
    return 1;
}
#endif

static int Tag_header(lua_State* L) {
    TagLib::ID3v2::Tag* tag = ID3v2::Tag::checkPtr(L, 1);
    ID3v2::Header::pushPtr(L, tag->header(), 1);
    return 1;
}

static int Tag_extendedHeader(lua_State* L) {
    TagLib::ID3v2::Tag* tag = ID3v2::Tag::checkPtr(L, 1);
    ID3v2::ExtendedHeader::pushPtr(L, tag->extendedHeader(), 1);
    return 1;
}

static int Tag_frameListMap(lua_State* L) {
    ID3v2::FrameListMap::pushRef(L, ID3v2::Tag::checkPtr(L, 1)->frameListMap(), 1);
    return 1;
}

static int Tag_frameList(lua_State* L) {
    int args = lua_gettop(L);
    TagLib::ID3v2::Tag* tag = ID3v2::Tag::checkPtr(L, 1);

   switch(args) {
#if LTAGLIB_ATLEAST(LTAGLIB_1_2)
       case 2: {
           ID3v2::FrameList::pushRef(L, tag->frameList(ByteVector::looseValue(L, 2)), 1);
           break;
       }
#endif
       case 1: {
           ID3v2::FrameList::pushRef(L, tag->frameList(), 1);
           break;
       }
       default: return luaL_error(L, "invalid arguments");
    }

    return 1;
}

static int Tag_addFrame(lua_State* L) {
    TagLib::ID3v2::Tag* tag = ID3v2::Tag::checkPtr(L, 1);
    TagLib::ID3v2::Frame* frame = ID3v2::Frame::checkPtr(L, 2);
    tag->addFrame(frame);
    ID3v2::Frame::unmanageRefs(L, 2);

    lua_settop(L,1);
    return 1;
}

static int Tag_removeFrame(lua_State* L) {
    TagLib::ID3v2::Tag* tag = ID3v2::Tag::checkPtr(L, 1);
    TagLib::ID3v2::Frame* frame = ID3v2::Frame::checkPtr(L, 2);
    tag->removeFrame(frame, true);
    ID3v2::Frame::unmanageRefs(L, 2);

    lua_settop(L,1);
    return 1;
}

static int Tag_removeFrames(lua_State* L) {
    TagLib::ID3v2::Tag* tag = ID3v2::Tag::checkPtr(L, 1);
    tag->removeFrames(ByteVector::looseValue(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Tag_render(lua_State* L) {
    int args = lua_gettop(L);
    TagLib::ID3v2::Tag* tag = ID3v2::Tag::checkPtr(L, 1);

    switch(args) {
#if LTAGLIB_ATLEAST(LTAGLIB_1_8)
        case 2: {
#if LTAGLIB_ATLEAST(LTAGLIB_1_12)
            ByteVector::pushValue(L, tag->render( ID3v2::Version::checkValue(L, 2) ));
#else
            ByteVector::pushValue(L, tag->render( luaL_checkinteger(L, 2) ));
#endif
            return 1;
        }
#endif
        case 1: {
            ByteVector::pushValue(L, tag->render());
            return 1;
        }
        default: break;
    }

    return luaL_error(L, "invalid arguments");
}

static const luaL_Reg Tag__index[] = {
#if LTAGLIB_UNDER(LTAGLIB_1_12)
    { "footer",         Tag_footer},
#endif
    { "header",         Tag_header},
    { "extendedHeader", Tag_extendedHeader},
    { "frameListMap",   Tag_frameListMap},
    { "frameList",      Tag_frameList},
    { "addFrame",       Tag_addFrame},
    { "removeFrame",    Tag_removeFrame},
    { "removeFrames",   Tag_removeFrames},
    { "render",         Tag_render},
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_Tag(lua_State* L) {
    return ID3v2::Tag::open(L);
}

template<>
const UserdataTable ID3v2::Tag::base::mod = {
    Tag__call,
    NULL,
    NULL,
};

template<>
const UserdataMetatable ID3v2::Tag::base::metatable = {
    "TagLib::ID3v2::Tag", /* name */
    Tag__index, /* indextable */
    NULL, /* indexfunc */
};

template<>
const char* ID3v2::FrameList::base::__name = "TagLib::ID3v2::FrameList";

template<>
const char* ID3v2::FrameListMap::base::__name = "TagLib::ID3v2::FrameListMap";

#include "../shared/userdata.tcc"
template class DerivedUserdata<TagLib::ID3v2::Tag, LuaTagLib::Tag>;
