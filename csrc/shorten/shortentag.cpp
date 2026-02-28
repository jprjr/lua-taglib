#include "shortentag.h"

using namespace LuaTagLib;

static int Tag__call(lua_State* L) {
    int args = lua_gettop(L);
    TagLib::Shorten::Tag* t = NULL;

    switch(args) {
        case 0: {
            t = new TagLib::Shorten::Tag();
            break;
        }
        default: break;
    }

    if(t == NULL) return luaL_error(L, "invalid arguments");
    Shorten::Tag::pushPtr(L, t);
    return 1;
}

LTAGLIB_PUBLIC
int luaopen_TagLib_Shorten_Tag(lua_State* L) {
    return Shorten::Tag::open(L);
}

template<>
const UserdataTable Shorten::Tag::base::mod = {
    Tag__call,
    NULL,
    NULL,
};

template<>
const UserdataMetatable Shorten::Tag::base::metatable = {
    "TagLib::Shorten::Tag", /* name */
    NULL, /* indextable */
    NULL, /* indexfunc */
};

#include "../shared/userdata.tcc"
template class LuaTagLib::DerivedUserdata<TagLib::Shorten::Tag, LuaTagLib::Tag>;

