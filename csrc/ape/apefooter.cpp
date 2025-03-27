#include "apefooter.h"

#if LTAGLIB_HAS_APE_FOOTER

#include "../tbytevector.h"

using namespace LuaTagLib;

static int Footer__call(lua_State* L) {
    int args = lua_gettop(L);
    TagLib::APE::Footer* f = NULL;

    switch(args) {
        case 0: {
            f = new TagLib::APE::Footer();
            break;
        }
        case 1: {
            f = new TagLib::APE::Footer(ByteVector::looseValue(L, 2));
            break;
        }
        default: break;
    }
    if(f == NULL) return luaL_error(L, "invalid arguments");
    APE::Footer::pushPtr(L, f);
    return 1;
}

static int Footer_version(lua_State* L) {
    TagLib::APE::Footer* f = APE::Footer::checkPtr(L, 1);
    lua_pushinteger(L, f->version());
    return 1;
}

static int Footer_headerPresent(lua_State* L) {
    TagLib::APE::Footer* f = APE::Footer::checkPtr(L, 1);
    lua_pushboolean(L, f->headerPresent());
    return 1;
}

static int Footer_footerPresent(lua_State* L) {
    TagLib::APE::Footer* f = APE::Footer::checkPtr(L, 1);
    lua_pushboolean(L, f->footerPresent());
    return 1;
}

static int Footer_isHeader(lua_State* L) {
    TagLib::APE::Footer* f = APE::Footer::checkPtr(L, 1);
    lua_pushboolean(L, f->isHeader());
    return 1;
}

static int Footer_setHeaderPresent(lua_State* L) {
    TagLib::APE::Footer* f = APE::Footer::checkPtr(L, 1);
    f->setHeaderPresent(lua_toboolean(L, 2));

    lua_settop(L,1);
    return 1;
}

static int Footer_itemCount(lua_State* L) {
    TagLib::APE::Footer* f = APE::Footer::checkPtr(L, 1);
    lua_pushinteger(L, f->itemCount());
    return 1;
}

static int Footer_setItemCount(lua_State* L) {
    TagLib::APE::Footer* f = APE::Footer::checkPtr(L, 1);
    f->setItemCount(luaL_checkinteger(L, 2));

    lua_settop(L,1);
    return 1;
}

static int Footer_tagSize(lua_State* L) {
    TagLib::APE::Footer* f = APE::Footer::checkPtr(L, 1);
    lua_pushinteger(L, f->tagSize());
    return 1;
}

static int Footer_completeTagSize(lua_State* L) {
    TagLib::APE::Footer* f = APE::Footer::checkPtr(L, 1);
    lua_pushinteger(L, f->completeTagSize());
    return 1;
}

static int Footer_setTagSize(lua_State* L) {
    TagLib::APE::Footer* f = APE::Footer::checkPtr(L, 1);
    f->setTagSize(luaL_checkinteger(L, 2));

    lua_settop(L,1);
    return 1;
}

static int Footer_setData(lua_State* L) {
    TagLib::APE::Footer* f = APE::Footer::checkPtr(L, 1);
    f->setData(ByteVector::looseValue(L, 2));

    lua_settop(L,1);
    return 1;
}

static int Footer_renderFooter(lua_State* L) {
    TagLib::APE::Footer* f = APE::Footer::checkPtr(L, 1);
    ByteVector::pushValue(L, f->renderFooter());
    return 1;
}

static int Footer_renderHeader(lua_State* L) {
    TagLib::APE::Footer* f = APE::Footer::checkPtr(L, 1);
    ByteVector::pushValue(L, f->renderHeader());
    return 1;
}

static
const luaL_Reg Footer__index[] = {
    { "version", Footer_version },
    { "headerPresent", Footer_headerPresent },
    { "footerPresent", Footer_footerPresent },
    { "isHeader", Footer_isHeader },
    { "setHeaderPresent", Footer_setHeaderPresent },
    { "itemCount", Footer_itemCount },
    { "setItemCount", Footer_setItemCount },
    { "tagSize", Footer_tagSize },
    { "completeTagSize", Footer_completeTagSize },
    { "setData", Footer_setData },
    { "setTagSize", Footer_setTagSize },
    { "renderFooter", Footer_renderFooter },
    { "renderHeader", Footer_renderHeader },
    { NULL, NULL }
};

static int Footer_static_size(lua_State* L) {
    lua_pushinteger(L, TagLib::APE::Footer::size());
    return 1;
}

static int Footer_static_fileIdentifier(lua_State* L) {
    ByteVector::pushValue(L, TagLib::APE::Footer::fileIdentifier());
    return 1;
}

static const luaL_Reg Footer_static__index[] = {
    { "size", Footer_static_size },
    { "fileIdentifier", Footer_static_fileIdentifier },
    { NULL, NULL }
};


LTAGLIB_PUBLIC
int luaopen_TagLib_APE_Footer(lua_State* L) {
    return APE::Footer::open(L);
}

template<>
const UserdataTable APE::Footer::base::mod = {
    Footer__call,
    Footer_static__index,
    NULL,
};

template<>
const UserdataMetatable APE::Footer::base::metatable = {
    "TagLib::APE::Footer", /* name */
    Footer__index, /* indextable */
    NULL, /* indexfunc */
};

#include "../shared/userdata.tcc"
template class LuaTagLib::BaseUserdata<TagLib::APE::Footer>;

#endif
