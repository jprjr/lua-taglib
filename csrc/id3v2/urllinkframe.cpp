#include "urllinkframe.h"

#if LTAGLIB_HAS_URLLINKFRAME

#include "../tbytevector.h"
#include "../tstring.h"
#include "../tpropertymap.h"

#if LTAGLIB_ATLEAST(LTAGLIB_1_8)
#include "id3v2tag.h"
#endif

#define T ID3v2::UrlLinkFrame
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


static int Frame_url(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    String::pushValue(L, f->url());
    return 1;
}

static int Frame_setUrl(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    f->setUrl(String::checkValue(L, 1));
    return 1;
}

static int Frame_setText(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    f->setText(String::checkValue(L, 1));
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
    { "url", Frame_url },
    { "setUrl", Frame_setUrl },
    { "setText", Frame_setText },
#if LTAGLIB_HAS_PROPERTYMAP
    { "asProperties", Frame_asProperties },
#endif
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_UrlLinkFrame(lua_State* L) {
    return T::open(L);
}

template<>
const UserdataTable T::base::mod = {
    Frame__call,
    NULL,
    NULL
};

template<>
const UserdataMetatable T::base::metatable = {
    NAME, /* name */
    Frame__index, /* indextable */
    NULL, /* indexfunc */
};

#undef T
#define T ID3v2::UserUrlLinkFrame

static int UserFrame__call(lua_State* L) {
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

static int UserFrame_textEncoding(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    String::Type::pushValue(L, f->textEncoding());
    return 1;
}

static int UserFrame_setTextEncoding(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    f->setTextEncoding(String::Type::checkValue(L, 2));
    lua_settop(L,1);
    return 1;
}

static int UserFrame_description(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    String::pushValue(L, f->description());
    return 1;
}

static int UserFrame_setDescription(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    f->setDescription(String::checkValue(L, 2));
    lua_settop(L,1);
    return 1;
}

static const luaL_Reg UserFrame__index[] = {
    { "textEncoding", UserFrame_textEncoding },
    { "setTextEncoding", UserFrame_setTextEncoding },
    { "description", UserFrame_description },
    { "setDescription", UserFrame_setDescription },
    { NULL, NULL }
};

#if LTAGLIB_ATLEAST(LTAGLIB_1_8)
static int UserFrame_static_find(lua_State* L) {
    TT* u = TT::find(ID3v2::Tag::checkPtr(L,1), String::checkValue(L,1));
    if(u == NULL) return 0;

    T::pushPtr(L, u, 1);
    return 1;
}
#endif

static const luaL_Reg UserFrame__static[] = {
#if LTAGLIB_ATLEAST(LTAGLIB_1_8)
    { "find", UserFrame_static_find },
#endif
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_UserUrlLinkFrame(lua_State* L) {
    return T::open(L);
}

template<>
const UserdataTable T::base::mod = {
    UserFrame__call,
    UserFrame__static,
    NULL
};

template<>
const UserdataMetatable T::base::metatable = {
    NAME, /* name */
    UserFrame__index, /* indextable */
    NULL, /* indexfunc */
};

#undef T
#include "../shared/userdata.tcc"
template class DerivedUserdata<TagLib::ID3v2::UrlLinkFrame, LuaTagLib::ID3v2::Frame>;
template class DerivedUserdata<TagLib::ID3v2::UserUrlLinkFrame, LuaTagLib::ID3v2::UrlLinkFrame>;

#endif
