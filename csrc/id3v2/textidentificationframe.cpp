#include "textidentificationframe.h"

#include "../tbytevector.h"
#include "../tstring.h"
#include "../tstringlist.h"
#include "../tpropertymap.h"
#include "../tmap.h"

#if LTAGLIB_HAS_USERTEXTIDENTIFICATIONFRAME
#if LTAGLIB_ATLEAST(LTAGLIB_1_5)
#include "id3v2tag.h"
#endif
#endif

#define T ID3v2::TextIdentificationFrame
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
        case 2: {
            f = new TT(ByteVector::looseValue(L, 1), String::Type::checkValue(L,2));
            break;
        }
        default: break;
    }

    if(f == NULL) return luaL_error(L, "invalid arguments");
    T::pushPtr(L, f);
    return 1;
}

static int Frame_setText(lua_State* L) {
    int args = lua_gettop(L);
    TT* f = T::checkPtr(L, 1);

    switch(args) {
        case 2: {
            if(lua_type(L, 2) == LUA_TTABLE) {
                f->setText(StringList::checkValue(L, 2));
            } else {
                f->setText(String::checkValue(L, 2));
            }
            break;
        }
        default: return luaL_error(L, "invalid arguments");
    }
    lua_settop(L,1);
    return 1;
}

static int Frame_textEncoding(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    String::Type::pushValue(L, f->textEncoding());
    return 1;
}

static int Frame_setTextEncoding(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    f->setTextEncoding(String::Type::checkValue(L,2));
    lua_settop(L,1);
    return 1;
}

static int Frame_fieldList(lua_State* L) {
    TT* f = T::checkPtr(L, 1);
    StringList::pushValue(L, f->fieldList());
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
    { "setText", Frame_setText },
    { "textEncoding", Frame_textEncoding },
    { "setTextEncoding", Frame_setTextEncoding },
    { "fieldList", Frame_fieldList },
#if LTAGLIB_HAS_PROPERTYMAP
    { "asProperties", Frame_asProperties },
#endif
    { NULL, NULL }
};

#if LTAGLIB_ATLEAST(LTAGLIB_1_8)
static int Frame_static_involvedPeopleMap(lua_State* L) {
    ValueMap< TagLib::ID3v2::KeyConversionMap, String, String >::pushValue(L, TT::involvedPeopleMap());
    return 1;
}
template<>
const char* ValueMap< TagLib::ID3v2::KeyConversionMap, String, String >::base::__name = "TagLib::ID3v2::KeyConversionMap";

static int Frame_static_createTIPLFrame(lua_State* L) {
    TT* f = TT::createTIPLFrame(PropertyMap::checkValue(L,1));
    if(f != NULL) {
        T::pushPtr(L, f);
        return 1;
    }
    return 0;
}

static int Frame_static_createTMCLFrame(lua_State* L) {
    TT* f = TT::createTMCLFrame(PropertyMap::checkValue(L,1));
    if(f != NULL) {
        T::pushPtr(L, f);
        return 1;
    }
    return 0;
}

#endif

static const luaL_Reg Frame__static[] = {
#if LTAGLIB_ATLEAST(LTAGLIB_1_8)
    { "involvedPeopleMap", Frame_static_involvedPeopleMap },
    { "createTIPLFrame", Frame_static_createTIPLFrame },
    { "createTMCLFrame", Frame_static_createTMCLFrame },
#endif
    { NULL, NULL }
};


LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_TextIdentificationFrame(lua_State* L) {
    return T::open(L);
}

template<>
const UserdataTable T::base::mod = {
    Frame__call,
    Frame__static,
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
template class DerivedUserdata<TagLib::ID3v2::TextIdentificationFrame, LuaTagLib::ID3v2::Frame>;

#if LTAGLIB_HAS_USERTEXTIDENTIFICATIONFRAME

#define T ID3v2::UserTextIdentificationFrame

static int UserFrame__call(lua_State* L) {
    int args = lua_gettop(L);
    TT* f = NULL;

    switch(args) {
        case 0: {
            f = new TT();
            break;
        }
        case 1: {
            if(String::Type::isValid(L, 1)) {
                f = new TT( String::Type::checkValue(L, 1) );
            } else {
                f = new TT( ByteVector::looseValue(L, 1) );
            }
            break;
        }
#if LTAGLIB_ATLEAST(LTAGLIB_1_8)
        case 2: {
            f = new TT(String::checkValue(L, 1), StringList::checkValue(L, 2));
            break;
        }
        case 3: {
            f = new TT(String::checkValue(L, 1), StringList::checkValue(L, 2), String::Type::checkValue(L, 3));
            break;
        }
#endif
        default: break;
    }

    if(f == NULL) return luaL_error(L, "invalid arguments");

    T::pushPtr(L, f);
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
    { "description", UserFrame_description },
    { "setDescription", UserFrame_setDescription },
    { NULL, NULL },
};


#if LTAGLIB_ATLEAST(LTAGLIB_1_5)
static int UserFrame_static_find(lua_State* L) {
    TT* f =
      TT::find(
        ID3v2::Tag::checkPtr(L, 1),
        String::checkValue(L, 2)
      );
    if(f == NULL) return 0;

    T::pushPtr(L, f, 1);
    return 1;
}
#endif

#if LTAGLIB_ATLEAST(LTAGLIB_2_0)
static int UserFrame_static_keyToTXXX(lua_State* L) {
    String::pushValue(
      L,
      TT::keyToTXXX(String::checkValue(L,1))
    );
    return 1;
}

static int UserFrame_static_txxxToKey(lua_State* L) {
    String::pushValue(
      L,
      TT::txxxToKey(String::checkValue(L,1))
    );
    return 1;
}
#endif

static const luaL_Reg UserFrame_static__index[] = {
#if LTAGLIB_ATLEAST(LTAGLIB_1_5)
    { "find", UserFrame_static_find },
#endif
#if LTAGLIB_ATLEAST(LTAGLIB_2_0)
    { "keyToTXXX", UserFrame_static_keyToTXXX },
    { "txxxToKey", UserFrame_static_txxxToKey },
#endif
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_UserTextIdentificationFrame(lua_State* L) {
    return T::open(L);
}

template<>
const UserdataTable T::base::mod = {
    UserFrame__call,
    UserFrame_static__index,
    NULL
};


template<>
const UserdataMetatable T::base::metatable = {
    NAME, /* name */
    UserFrame__index, /* indextable */
    NULL, /* indexfunc */
};

#undef T
template class DerivedUserdata<TagLib::ID3v2::UserTextIdentificationFrame, LuaTagLib::ID3v2::TextIdentificationFrame>;

#endif
