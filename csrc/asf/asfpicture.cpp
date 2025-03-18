#include "asfpicture.h"

#if LTAGLIB_HAS_ASF_PICTURE

#include "../tbytevector.h"
#include "../tstring.h"
#include "../tpicture.h"

using namespace LuaTagLib;

static int Picture__call(lua_State* L) {
    int args = lua_gettop(L);
    TagLib::ASF::Picture* f = NULL;

    switch(args) {
        case 0: {
            f = new TagLib::ASF::Picture();
            break;
        }
        case 1: {
            f = new TagLib::ASF::Picture(ASF::Picture::checkValue(L, 1));
            break;
        }
        default: break;
    }

    if(f == NULL) return luaL_error(L, "invalid arguments");
    ASF::Picture::pushPtr(L, f);
    return 1;
}

static int Picture_isValid(lua_State* L) {
    TagLib::ASF::Picture* f = ASF::Picture::checkPtr(L, 1);
    lua_pushboolean(L, f->isValid());
    return 1;
}

static int Picture_type(lua_State* L) {
    TagLib::ASF::Picture* f = ASF::Picture::checkPtr(L, 1);
    ASF::Picture::Type::pushValue(L, f->type());
    return 1;
}

static int Picture_setType(lua_State* L) {
    TagLib::ASF::Picture* f = ASF::Picture::checkPtr(L, 1);
    f->setType(ASF::Picture::Type::checkValue(L, 2));

    lua_settop(L,1);
    return 1;
}

static int Picture_mimeType(lua_State* L) {
    TagLib::ASF::Picture* f = ASF::Picture::checkPtr(L, 1);
    String::pushValue(L, f->mimeType());
    return 1;
}

static int Picture_setMimeType(lua_State* L) {
    TagLib::ASF::Picture* f = ASF::Picture::checkPtr(L, 1);
    f->setMimeType(String::checkValue(L, 2));

    lua_settop(L,1);
    return 1;
}

static int Picture_description(lua_State* L) {
    TagLib::ASF::Picture* f = ASF::Picture::checkPtr(L, 1);
    String::pushValue(L, f->description());
    return 1;
}

static int Picture_setDescription(lua_State* L) {
    TagLib::ASF::Picture* f = ASF::Picture::checkPtr(L, 1);
    f->setDescription(String::checkValue(L, 2));

    lua_settop(L,1);
    return 1;
}


static int Picture_picture(lua_State* L) {
    TagLib::ASF::Picture* f = ASF::Picture::checkPtr(L, 1);
    ByteVector::pushValue(L, f->picture());
    return 1;
}

static int Picture_setPicture(lua_State* L) {
    TagLib::ASF::Picture* f = ASF::Picture::checkPtr(L, 1);
    f->setPicture(ByteVector::looseValue(L, 2));

    lua_settop(L,1);
    return 1;
}

static int Picture_render(lua_State* L) {
    TagLib::ASF::Picture* pic = ASF::Picture::checkPtr(L, 1);
    ByteVector::pushValue(L, pic->render());
    return 1;
}

static int Picture_dataSize(lua_State* L) {
    TagLib::ASF::Picture* pic = ASF::Picture::checkPtr(L, 1);
    lua_pushinteger(L, pic->dataSize());
    return 1;
}

#if LTAGLIB_ATLEAST(LTAGLIB_1_11)
static int Picture_swap(lua_State* L) {
    ASF::Picture::checkPtr(L,1)->swap(ASF::Picture::checkValue(L,2));
    lua_settop(L,1);
    return 1;
}
#endif

static const luaL_Reg Picture__index[] = {
    { "isValid", Picture_isValid },
    { "type", Picture_type },
    { "setType", Picture_setType },
    { "mimeType", Picture_mimeType },
    { "setMimeType", Picture_setMimeType },
    { "description", Picture_description },
    { "setDescription", Picture_setDescription },
    { "picture", Picture_picture },
    { "setPicture", Picture_setPicture },
    { "render", Picture_render },
    { "dataSize", Picture_dataSize },
#if LTAGLIB_ATLEAST(LTAGLIB_1_11)
    { "swap", Picture_swap },
#endif
    { NULL, NULL }
};

static int Picture__submodules(lua_State* L) {
    luaL_requiref(L, "TagLib.ASF.Picture.Type",
      luaopen_TagLib_ASF_Picture_Type, 0);
    lua_setfield(L, -2, "Type");
    return 0;
}

LTAGLIB_PUBLIC
int luaopen_TagLib_ASF_Picture(lua_State* L) {
    return ASF::Picture::open(L);
}

LTAGLIB_PUBLIC
int luaopen_TagLib_ASF_Picture_Type(lua_State* L) {
    return ASF::Picture::Type::open(L);
}

static const ASF::Picture::Type::enum_type enumValues[] = {
    LTAGLIB_PICTURE_ENUM(TagLib::ASF::Picture)
};

template<>
const UserdataTable ASF::Picture::base::mod = {
    Picture__call,
    NULL,
    Picture__submodules,
};

template<>
const UserdataMetatable ASF::Picture::base::metatable = {
    "TagLib::ASF::Picture", /* name */
    Picture__index, /* indextable */
    NULL, /* indexfunc */
};

template<>
const ASF::Picture::Type::enum_type* ASF::Picture::Type::m_values = enumValues;

template<>
const size_t ASF::Picture::Type::m_len = sizeof(enumValues) / sizeof(enumValues[0]);

#include "../shared/enum.tcc"
template class Enum<TagLib::ASF::Picture::Type>;

#include "../shared/userdata.tcc"
template class BaseUserdata<TagLib::ASF::Picture>;

#endif
