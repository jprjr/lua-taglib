#include "modtag.h"

#if LTAGLIB_HAS_MOD_TAG

#include "../tstring.h"

#define T Mod::Tag
#define TT TagLib::T
#define XSTR(s) STR(s)
#define STR(s) #s
#define NAME XSTR(TT)

using namespace LuaTagLib;

static int Tag__call(lua_State* L) {
    int args = lua_gettop(L);
    TT* t = NULL;

    switch(args) {
        case 0: {
            t = new TT();
            break;
        }
        default: break;
    }

    if(t == NULL) return luaL_error(L, "invalid arguments");
    T::pushPtr(L, t);
    return 1;
}

static int Tag_trackerName(lua_State* L) {
    String::pushValue(L, T::checkPtr(L,1)->trackerName());
    return 1;
}

static int Tag_setTrackerName(lua_State* L) {
    T::checkPtr(L,1)->setTrackerName(String::checkValue(L,2));
    lua_settop(L,1);
    return 1;
}

static const luaL_Reg Tag__index[] = {
    { "trackerName", Tag_trackerName },
    { "setTrackerName", Tag_setTrackerName },
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_Mod_Tag(lua_State* L) {
    return T::open(L);
}

template<>
const UserdataTable T::base::mod = {
    Tag__call,
    NULL,
    NULL
};

template<>
const UserdataMetatable Mod::Tag::base::metatable = {
    NAME, /* name */
    Tag__index, /* indextable */
    NULL, /* indexfunc */
};

#undef T
#include "../shared/userdata.tcc"
template class LuaTagLib::DerivedUserdata<TagLib::Mod::Tag, LuaTagLib::Tag>;

#endif

