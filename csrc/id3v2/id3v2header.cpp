#include "id3v2header.h"
#include "../tbytevector.h"

using namespace LuaTagLib;

static int Header__call(lua_State* L) {
    int args = lua_gettop(L);

    TagLib::ID3v2::Header* h = NULL;

    switch(args) {
        case 0: {
            h = new TagLib::ID3v2::Header();
            break;
        }
        case 1: {
            h = new TagLib::ID3v2::Header(ByteVector::looseValue(L, 1));
            break;
        }
        default: break;
    }

    if(h == NULL) return luaL_error(L, "invalid arguments");
    ID3v2::Header::pushPtr(L, h);
    return 1;
}

#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,5,0)
static int Header_setMajorVersion(lua_State* L) {
    TagLib::ID3v2::Header* h = ID3v2::Header::checkPtr(L, 1);
    h->setMajorVersion(luaL_checkinteger(L, 2));
    lua_settop(L,1);
    return 1;
}
#endif

static int Header_majorVersion(lua_State* L) {
    TagLib::ID3v2::Header* h = ID3v2::Header::checkPtr(L, 1);
    lua_pushinteger(L, h->majorVersion());
    return 1;
}

static int Header_revisionNumber(lua_State* L) {
    TagLib::ID3v2::Header* h = ID3v2::Header::checkPtr(L, 1);
    lua_pushinteger(L, h->revisionNumber());
    return 1;
}

static int Header_unsynchronisation(lua_State* L) {
    TagLib::ID3v2::Header* h = ID3v2::Header::checkPtr(L, 1);
    lua_pushboolean(L, h->unsynchronisation());
    return 1;
}

static int Header_extendedHeader(lua_State* L) {
    TagLib::ID3v2::Header* h = ID3v2::Header::checkPtr(L, 1);
    lua_pushboolean(L, h->extendedHeader());
    return 1;
}

static int Header_experimentalIndicator(lua_State* L) {
    TagLib::ID3v2::Header* h = ID3v2::Header::checkPtr(L, 1);
    lua_pushboolean(L, h->experimentalIndicator());
    return 1;
}

static int Header_footerPresent(lua_State* L) {
    TagLib::ID3v2::Header* h = ID3v2::Header::checkPtr(L, 1);
    lua_pushboolean(L, h->footerPresent());
    return 1;
}

static int Header_tagSize(lua_State* L) {
    TagLib::ID3v2::Header* h = ID3v2::Header::checkPtr(L, 1);
    lua_pushinteger(L, h->tagSize());
    return 1;
}

static int Header_completeTagSize(lua_State* L) {
    TagLib::ID3v2::Header* h = ID3v2::Header::checkPtr(L, 1);
    lua_pushinteger(L, h->completeTagSize());
    return 1;
}

static int Header_setTagSize(lua_State* L) {
    TagLib::ID3v2::Header* h = ID3v2::Header::checkPtr(L, 1);
    h->setTagSize(luaL_checkinteger(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Header_setData(lua_State* L) {
    TagLib::ID3v2::Header* h = ID3v2::Header::checkPtr(L, 1);
    h->setData(ByteVector::looseValue(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Header_render(lua_State* L) {
    TagLib::ID3v2::Header* h = ID3v2::Header::checkPtr(L, 1);
    ByteVector::pushValue(L, h->render());
    return 1;
}

static const luaL_Reg Header__index[] = {
#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,5,0)
    { "setMajorVersion", Header_setMajorVersion },
#endif
    { "majorVersion", Header_majorVersion },
    { "revisionNumber", Header_revisionNumber },
    { "unsynchronisation", Header_unsynchronisation },
    { "extendedHeader", Header_extendedHeader },
    { "experimentalIndicator", Header_experimentalIndicator },
    { "footerPresent", Header_footerPresent },
    { "tagSize", Header_tagSize },
    { "completeTagSize", Header_completeTagSize },
    { "setTagSize", Header_setTagSize },
    { "setData", Header_setData },
    { "render", Header_render },
    { NULL, NULL }
};

static int Header_static_size(lua_State* L) {
    lua_pushinteger(L, TagLib::ID3v2::Header::size());
    return 1;
}

static int Header_static_fileIdentifier(lua_State* L) {
    ByteVector::pushValue(L, TagLib::ID3v2::Header::fileIdentifier());
    return 1;
}

static const luaL_Reg Header_static_index[] = {
    { "size", Header_static_size },
    { "fileIdentifier", Header_static_fileIdentifier },
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_Header(lua_State* L) {
    return ID3v2::Header::open(L);
}

template<>
const UserdataTable ID3v2::Header::base::mod = {
    Header__call,
    Header_static_index,
    NULL,
};


template<>
const UserdataMetatable ID3v2::Header::base::metatable = {
    "TagLib::ID3v2::Header", /* name */
    Header__index, /* indextable */
    NULL, /* indexfunc */
};

#include "../shared/userdata.tcc"
template class BaseUserdata<TagLib::ID3v2::Header>;
