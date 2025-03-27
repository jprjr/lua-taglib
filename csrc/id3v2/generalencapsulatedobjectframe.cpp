#include "generalencapsulatedobjectframe.h"

#if LTAGLIB_HAS_GENERALENCAPSULATEDOBJECTFRAME

#include "../tbytevector.h"
#include "../tstring.h"

#define T ID3v2::GeneralEncapsulatedObjectFrame
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
    TT* f = T::checkPtr(L, 1);
    String::Type::pushValue(L, f->textEncoding());
    return 1;
}

static int Frame_setTextEncoding(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    f->setTextEncoding(String::Type::checkValue(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Frame_mimeType(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    String::pushValue(L, f->mimeType());
    return 1;
}

static int Frame_setMimeType(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    f->setMimeType(String::checkValue(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Frame_fileName(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    String::pushValue(L, f->fileName());
    return 1;
}

static int Frame_setFileName(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    f->setFileName(String::checkValue(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Frame_description(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    String::pushValue(L, f->description());
    return 1;
}

static int Frame_setDescription(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    f->setDescription(String::checkValue(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Frame_object(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    ByteVector::pushValue(L, f->object());
    return 1;
}

static int Frame_setObject(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    f->setObject(ByteVector::looseValue(L, 2));
    lua_settop(L,1);
    return 1;
}

static const luaL_Reg Frame__index[] = {
    { "textEncoding", Frame_textEncoding },
    { "setTextEncoding", Frame_setTextEncoding },
    { "mimeType", Frame_mimeType },
    { "setMimeType", Frame_setMimeType },
    { "fileName", Frame_fileName },
    { "setFileName", Frame_setFileName },
    { "description", Frame_description },
    { "setDescription", Frame_setDescription },
    { "object", Frame_object },
    { "setObject", Frame_setObject },
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_GeneralEncapsulatedObjectFrame(lua_State* L) {
    return T::open(L);
}

template<>
const UserdataTable T::base::mod = {
    Frame__call,
    NULL,
    NULL,
};

template<>
const UserdataMetatable T::base::metatable = {
    NAME, /* name */
    Frame__index, /* indextable */
    NULL, /* indexfunc */
};

#undef T
#include "../shared/userdata.tcc"
template class LuaTagLib::DerivedUserdata<TagLib::ID3v2::GeneralEncapsulatedObjectFrame, LuaTagLib::ID3v2::Frame>;

#endif
