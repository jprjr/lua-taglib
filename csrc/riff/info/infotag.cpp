#include "infotag.h"

#if LTAGLIB_HAS_RIFF_INFO_TAG

#include "../../tbytevector.h"
#include "../../tstring.h"
#include "../../tmap.h"

#define T RIFF::Info::Tag
#define TT TagLib::T
#define XSTR(s) STR(s)
#define STR(s) #s
#define NAME XSTR(TT)

using namespace LuaTagLib;

static int Tag__call(lua_State* L) {
    int args = lua_gettop(L);
    TT* t;

    switch(args) {
        case 0: {
            t = new TT();
            break;
        }
        case 1: {
            t = new TT(ByteVector::looseValue(L, 1));
            break;
        }
        default: break;
    }

    if(t == NULL) return luaL_error(L, "invalid arguments");
    T::pushPtr(L, t);
    return 1;
}

typedef ValueMap<TagLib::RIFF::Info::FieldListMap, ByteVector,String> FieldListMap;
static int Tag_fieldListMap(lua_State* L) {
    FieldListMap::pushValue(L, T::checkPtr(L,1)->fieldListMap());
    return 1;
}

static int Tag_fieldText(lua_State* L) {
    String::pushValue(L,T::checkPtr(L,1)->fieldText(ByteVector::looseValue(L,2)));
    return 1;
}

static int Tag_setFieldText(lua_State* L) {
    T::checkPtr(L,1)->setFieldText(ByteVector::looseValue(L,2), String::checkValue(L, 3));
    lua_settop(L,1);
    return 1;
}

static int Tag_removeField(lua_State* L) {
    T::checkPtr(L,1)->removeField(ByteVector::looseValue(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Tag_render(lua_State* L) {
    ByteVector::pushValue(L, T::checkPtr(L,1)->render());
    return 1;
}

static
const luaL_Reg Tag__index[] = {
    { "fieldListMap", Tag_fieldListMap },
    { "fieldText", Tag_fieldText },
    { "setFieldText", Tag_setFieldText },
    { "removeField", Tag_removeField },
    { "render", Tag_render },
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_RIFF_Info_Tag(lua_State *L) {
    return T::open(L);
}

template<>
const UserdataTable T::base::mod = {
    Tag__call,
    NULL,
    NULL,
};


template<>
const UserdataMetatable RIFF::Info::Tag::base::metatable = {
    NAME, /* name */
    Tag__index, /* indextable */
    NULL, /* indexfunc */
};

template<>
const char* FieldListMap::base::__name = NAME "::FieldListMap";

#undef T
#include "../../shared/userdata.tcc"
template class DerivedUserdata<TagLib::RIFF::Info::Tag, LuaTagLib::Tag>;

#endif
