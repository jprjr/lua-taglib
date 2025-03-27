#include "attachedpictureframe.h"

#if LTAGLIB_HAS_ATTACHEDPICTUREFRAME

#include "../tbytevector.h"
#include "../tstring.h"
#include "../tpicture.h"

using namespace LuaTagLib;

static int Frame__call(lua_State* L) {
    int args = lua_gettop(L);
    TagLib::ID3v2::AttachedPictureFrame* f = NULL;

    switch(args) {
        case 0: {
            f = new TagLib::ID3v2::AttachedPictureFrame();
            break;
        }
        case 1: {
            f = new TagLib::ID3v2::AttachedPictureFrame(ByteVector::looseValue(L, 1));
            break;
        }
        default: break;
    }

    if(f == NULL) return luaL_error(L, "invalid arguments");

    ID3v2::AttachedPictureFrame::pushPtr(L, f);
    return 1;
}


static int Frame_type(lua_State* L) {
    TagLib::ID3v2::AttachedPictureFrame* f = ID3v2::AttachedPictureFrame::checkPtr(L, 1);
    ID3v2::AttachedPictureFrame::Type::pushValue(L, f->type());
    return 1;
}

static int Frame_setType(lua_State* L) {
    TagLib::ID3v2::AttachedPictureFrame* f = ID3v2::AttachedPictureFrame::checkPtr(L, 1);
    f->setType(ID3v2::AttachedPictureFrame::Type::checkValue(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Frame_textEncoding(lua_State* L) {
    TagLib::ID3v2::AttachedPictureFrame* f = ID3v2::AttachedPictureFrame::checkPtr(L, 1);
    String::Type::pushValue(L, f->textEncoding());
    return 1;
}

static int Frame_setTextEncoding(lua_State* L) {
    TagLib::ID3v2::AttachedPictureFrame* f = ID3v2::AttachedPictureFrame::checkPtr(L, 1);
    f->setTextEncoding(String::Type::checkValue(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Frame_mimeType(lua_State* L) {
    TagLib::ID3v2::AttachedPictureFrame* f = ID3v2::AttachedPictureFrame::checkPtr(L, 1);
    String::pushValue(L, f->mimeType());
    return 1;
}

static int Frame_setMimeType(lua_State* L) {
    TagLib::ID3v2::AttachedPictureFrame* f = ID3v2::AttachedPictureFrame::checkPtr(L, 1);
    f->setMimeType(String::checkValue(L, 2));
    lua_settop(L,1);
    return 1;
}

#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,4,0)
static int Frame_description(lua_State* L) {
    TagLib::ID3v2::AttachedPictureFrame* f = ID3v2::AttachedPictureFrame::checkPtr(L, 1);
    String::pushValue(L, f->description());
    return 1;
}

static int Frame_setDescription(lua_State* L) {
    TagLib::ID3v2::AttachedPictureFrame* f = ID3v2::AttachedPictureFrame::checkPtr(L, 1);
    f->setDescription(String::checkValue(L, 2));
    lua_settop(L,1);
    return 1;
}
#endif

static int Frame_picture(lua_State* L) {
    TagLib::ID3v2::AttachedPictureFrame* f = ID3v2::AttachedPictureFrame::checkPtr(L, 1);
    ByteVector::pushValue(L, f->picture());
    return 1;
}

static int Frame_setPicture(lua_State* L) {
    TagLib::ID3v2::AttachedPictureFrame* f = ID3v2::AttachedPictureFrame::checkPtr(L, 1);
    f->setPicture(ByteVector::looseValue(L, 2));
    lua_settop(L,1);
    return 1;
}

static const luaL_Reg Frame__index[] = {
    { "type", Frame_type },
    { "setType", Frame_setType },
    { "textEncoding", Frame_textEncoding },
    { "setTextEncoding", Frame_setTextEncoding },
    { "mimeType", Frame_mimeType },
    { "setMimeType", Frame_setMimeType },
#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,4,0)
    { "description", Frame_description },
    { "setDescription", Frame_setDescription },
#endif
    { "picture", Frame_picture },
    { "setPicture", Frame_setPicture },
    { NULL, NULL }
};

static int Frame__submodules(lua_State* L) {
    luaL_requiref(L, "TagLib.ID3v2.AttachedPictureFrame.Type",
      luaopen_TagLib_ID3v2_AttachedPictureFrame_Type, 0);
    lua_setfield(L, -2, "Type");
    return 0;
}

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_AttachedPictureFrame(lua_State* L) {
    return ID3v2::AttachedPictureFrame::open(L);
}

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_AttachedPictureFrame_Type(lua_State* L) {
    return ID3v2::AttachedPictureFrame::Type::open(L);
}

template<>
const UserdataTable ID3v2::AttachedPictureFrame::base::mod = {
    Frame__call,
    NULL,
    Frame__submodules,
};

static const ID3v2::AttachedPictureFrame::Type::enum_type enumValues[] = {
  LTAGLIB_PICTURE_ENUM(TagLib::ID3v2::AttachedPictureFrame)
};

template<>
const UserdataMetatable ID3v2::AttachedPictureFrame::base::metatable = {
    "TagLib::ID3v2::AttachedPictureFrame",
    Frame__index,
    NULL,
};

template<>
const ID3v2::AttachedPictureFrame::Type::enum_type* ID3v2::AttachedPictureFrame::Type::m_values = enumValues;

template<>
const size_t ID3v2::AttachedPictureFrame::Type::m_len = sizeof(enumValues) / sizeof(enumValues[0]);

#undef T
#include "../shared/enum.tcc"
template class LuaTagLib::Enum<TagLib::ID3v2::AttachedPictureFrame::Type>;

#include "../shared/userdata.tcc"
template class LuaTagLib::DerivedUserdata<TagLib::ID3v2::AttachedPictureFrame, LuaTagLib::ID3v2::Frame>;

#endif
