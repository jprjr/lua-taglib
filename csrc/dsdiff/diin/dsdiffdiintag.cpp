#include "dsdiffdiintag.h"

#if LTAGLIB_HAS_DSDIFF_DIIN_TAG

#include "../../tfile.h"
#include "../../tbytevector.h"

#define T DSDIFF::DIIN::Tag
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

static
const luaL_Reg Tag__index[] = {
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_DSDIFF_DIIN_Tag(lua_State *L) {
    return DSDIFF::DIIN::Tag::open(L);
}

template<>
const UserdataTable DSDIFF::DIIN::Tag::base::mod = {
    Tag__call,
    NULL,
    NULL,
};

template<>
const UserdataMetatable DSDIFF::DIIN::Tag::base::metatable = {
    NAME, /* name */
    Tag__index, /* indextable */
    NULL, /* indexfunc */
};

#undef T
#include "../../shared/userdata.tcc"
template class DerivedUserdata<TagLib::DSDIFF::DIIN::Tag, LuaTagLib::Tag>;

#endif
