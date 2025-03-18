#include "commentsframe.h"

#include "../tbytevector.h"
#include "../tstring.h"
#include "../tpropertymap.h"
#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,5,0)
#include "id3v2tag.h"
#endif

#define T ID3v2::CommentsFrame
#define TT TagLib::T
#define XSTR(s) STR(s)
#define STR(s) #s
#define NAME XSTR(TT)

using namespace LuaTagLib;

static int Frame__call(lua_State* L) {
    int args = lua_gettop(L);
    TT* f = NULL;

    switch(args) {
        case 0: {
            f = new TT();
            break;
        }
        case 1: {
            if(String::Type::isValid(L,1)) {
                f = new TT(String::Type::checkValue(L, 1));
                break;
            }
            f = new TT(ByteVector::looseValue(L, 1));
            break;
        }
        default: break;
    }

    if(f == NULL) return luaL_error(L, "invalid arguments");

    T::pushPtr(L, f);
    return 1;
}


static int Frame_language(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    ByteVector::pushValue(L, f->language());
    return 1;
}

static int Frame_text(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    String::pushValue(L, f->text());
    return 1;
}

static int Frame_description(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    String::pushValue(L, f->description());
    return 1;
}

static int Frame_textEncoding(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    String::Type::pushValue(L, f->textEncoding());
    return 1;
}

static int Frame_setLanguage(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    f->setLanguage(ByteVector::looseValue(L,2));
    lua_settop(L,1);
    return 1;
}

static int Frame_setText(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    f->setText(String::checkValue(L,2));
    lua_settop(L,1);
    return 1;
}

static int Frame_setDescription(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    f->setDescription(String::checkValue(L,2));
    lua_settop(L,1);
    return 1;
}

static int Frame_setTextEncoding(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    f->setTextEncoding(String::Type::checkValue(L, 2));
    lua_settop(L,1);
    return 1;
}

#if LTAGLIB_HAS_PROPERTYMAP
static int Frame_asProperties(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    PropertyMap::pushValue(L, f->asProperties());
    return 1;
}
#endif

static const luaL_Reg Frame__index[] = {
    { "language", Frame_language },
    { "text", Frame_text },
    { "description", Frame_description },
    { "textEncoding", Frame_textEncoding },
    { "setLanguage", Frame_setLanguage },
    { "setText", Frame_setText },
    { "setDescription", Frame_setDescription },
    { "setTextEncoding", Frame_setTextEncoding },
#if LTAGLIB_HAS_PROPERTYMAP
    { "asProperties", Frame_asProperties },
#endif
    { NULL, NULL }
};

#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,5,0)
static int Frame_static_findByDescription(lua_State* L) {
    TT* f =
      TT::findByDescription(
        ID3v2::Tag::checkPtr(L, 1),
        String::checkValue(L, 2)
      );
    if(f == NULL) return 0;

    T::pushPtr(L, f, 1);
    return 1;
}
#endif

static const luaL_Reg Frame__static[] = {
#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,5,0)
    { "findByDescription", Frame_static_findByDescription },
#endif
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_CommentsFrame(lua_State* L) {
    return T::open(L);
}

template<>
const UserdataTable ID3v2::CommentsFrame::base::mod = {
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
template class DerivedUserdata<TagLib::ID3v2::CommentsFrame, LuaTagLib::ID3v2::Frame>;
