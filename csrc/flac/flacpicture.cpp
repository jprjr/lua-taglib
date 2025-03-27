#include "flacpicture.h"

#if LTAGLIB_HAS_FLAC_PICTURE

#include "../tbytevector.h"
#include "../tstring.h"
#include "../tpicture.h"
#include "../tlist.h"

using namespace LuaTagLib;

static int Picture__call(lua_State* L) {
    int args = lua_gettop(L);
    TagLib::FLAC::Picture* f = NULL;

    switch(args) {
        case 0: {
            f = new TagLib::FLAC::Picture();
            break;
        }
        case 1: {
            f = new TagLib::FLAC::Picture(ByteVector::looseValue(L, 1));
            break;
        }
        default: break;
    }

    if(f == NULL) return luaL_error(L, "invalid arguments");
    FLAC::Picture::pushPtr(L, f);
    return 1;
}


static int Picture_type(lua_State* L) {
    TagLib::FLAC::Picture* f = FLAC::Picture::checkPtr(L, 1);
    FLAC::Picture::Type::pushValue(L, f->type());
    return 1;
}

static int Picture_setType(lua_State* L) {
    TagLib::FLAC::Picture* f = FLAC::Picture::checkPtr(L, 1);
    f->setType(FLAC::Picture::Type::checkValue(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Picture_mimeType(lua_State* L) {
    TagLib::FLAC::Picture* f = FLAC::Picture::checkPtr(L, 1);
    String::pushValue(L, f->mimeType());
    return 1;
}

static int Picture_setMimeType(lua_State* L) {
    TagLib::FLAC::Picture* f = FLAC::Picture::checkPtr(L, 1);
    f->setMimeType(String::checkValue(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Picture_description(lua_State* L) {
    TagLib::FLAC::Picture* f = FLAC::Picture::checkPtr(L, 1);
    String::pushValue(L, f->description());
    return 1;
}

static int Picture_setDescription(lua_State* L) {
    TagLib::FLAC::Picture* f = FLAC::Picture::checkPtr(L, 1);
    f->setDescription(String::checkValue(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Picture_width(lua_State* L) {
    TagLib::FLAC::Picture* pic = FLAC::Picture::checkPtr(L, 1);
    lua_pushinteger(L, pic->width());
    return 1;
}

static int Picture_setWidth(lua_State* L) {
    TagLib::FLAC::Picture* pic = FLAC::Picture::checkPtr(L, 1);
    pic->setWidth(luaL_checkinteger(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Picture_height(lua_State* L) {
    TagLib::FLAC::Picture* pic = FLAC::Picture::checkPtr(L, 1);
    lua_pushinteger(L, pic->height());
    return 1;
}

static int Picture_setHeight(lua_State* L) {
    TagLib::FLAC::Picture* pic = FLAC::Picture::checkPtr(L, 1);
    pic->setHeight(luaL_checkinteger(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Picture_colorDepth(lua_State* L) {
    TagLib::FLAC::Picture* pic = FLAC::Picture::checkPtr(L, 1);
    lua_pushinteger(L, pic->colorDepth());
    return 1;
}

static int Picture_setColorDepth(lua_State* L) {
    TagLib::FLAC::Picture* pic = FLAC::Picture::checkPtr(L, 1);
    pic->setColorDepth(luaL_checkinteger(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Picture_numColors(lua_State* L) {
    TagLib::FLAC::Picture* pic = FLAC::Picture::checkPtr(L, 1);
    lua_pushinteger(L, pic->numColors());
    return 1;
}

static int Picture_setNumColors(lua_State* L) {
    TagLib::FLAC::Picture* pic = FLAC::Picture::checkPtr(L, 1);
    pic->setNumColors(luaL_checkinteger(L, 2));
    lua_settop(L,1);
    return 1;
}


static int Picture_data(lua_State* L) {
    TagLib::FLAC::Picture* f = FLAC::Picture::checkPtr(L, 1);
    ByteVector::pushValue(L, f->data());
    return 1;
}

static int Picture_setData(lua_State* L) {
    TagLib::FLAC::Picture* f = FLAC::Picture::checkPtr(L, 1);
    f->setData(ByteVector::looseValue(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Picture_parse(lua_State* L) {
    TagLib::FLAC::Picture* pic = FLAC::Picture::checkPtr(L, 1);
    lua_pushboolean(L,pic->parse(ByteVector::looseValue(L, 2)));
    return 1;
}

static const luaL_Reg Picture__index[] = {
    { "type", Picture_type },
    { "setType", Picture_setType },
    { "mimeType", Picture_mimeType },
    { "setMimeType", Picture_setMimeType },
    { "description", Picture_description },
    { "setDescription", Picture_setDescription },
    { "width", Picture_width },
    { "setWidth", Picture_setWidth },
    { "height", Picture_height },
    { "setHeight", Picture_setHeight },
    { "colorDepth", Picture_colorDepth },
    { "setColorDepth", Picture_setColorDepth },
    { "numColors", Picture_numColors },
    { "setNumColors", Picture_setNumColors },
    { "data", Picture_data },
    { "setData", Picture_setData },
    { "parse", Picture_parse },
    { NULL, NULL }
};

static int Picture__submodules(lua_State* L) {
    luaL_requiref(L, "TagLib.FLAC.Picture.Type",
      luaopen_TagLib_FLAC_Picture_Type, 0);
    lua_setfield(L, -2, "Type");
    return 0;
}

LTAGLIB_PUBLIC
int luaopen_TagLib_FLAC_Picture(lua_State* L) {
    return FLAC::Picture::open(L);
}

LTAGLIB_PUBLIC
int luaopen_TagLib_FLAC_Picture_Type(lua_State* L) {
    return FLAC::Picture::Type::open(L);
}

static const FLAC::Picture::Type::enum_type enumValues[] = {
  LTAGLIB_PICTURE_ENUM(TagLib::FLAC::Picture)
};

template<>
const UserdataTable FLAC::Picture::base::mod = {
    Picture__call,
    NULL,
    Picture__submodules,
};

template<>
const UserdataMetatable FLAC::Picture::base::metatable = {
    "TagLib::FLAC::Picture", /* name */
    Picture__index, /* indextable */
    NULL, /* indexfunc */
};

template<>
const FLAC::Picture::Type::enum_type* FLAC::Picture::Type::m_values = enumValues;

template<>
const size_t FLAC::Picture::Type::m_len = sizeof(enumValues) / sizeof(enumValues[0]);

template<>
const char * PtrList< TagLib::List<TagLib::FLAC::Picture*>, FLAC::Picture>::base::__name = "TagLib::List<TagLib::FLAC::Picture *>";

#include "../shared/enum.tcc"
template class LuaTagLib::Enum<TagLib::FLAC::Picture::Type>;

#include "../shared/userdata.tcc"
template class LuaTagLib::DerivedUserdata<TagLib::FLAC::Picture, FLAC::MetadataBlock>;

#endif
