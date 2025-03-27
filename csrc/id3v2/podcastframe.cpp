#include "podcastframe.h"

#if LTAGLIB_HAS_PODCASTFRAME

#if LTAGLIB_ATLEAST(LTAGLIB_1_12)
#include "../tpropertymap.h"
#endif

#define T ID3v2::PodcastFrame
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
        default: break;
    }

    if(f == NULL) return luaL_error(L, "invalid arguments");
    T::pushPtr(L, f);
    return 1;
}

#if LTAGLIB_ATLEAST(LTAGLIB_1_12)
static int Frame_asProperties(lua_State* L) {
    PropertyMap::pushValue(L, T::checkPtr(L,1)->asProperties());
    return 1;
}
#endif

static const luaL_Reg Frame__index[] = {
#if LTAGLIB_ATLEAST(LTAGLIB_1_12)
    { "asProperties", Frame_asProperties },
#endif
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_PodcastFrame(lua_State* L) {
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
#include "../shared/userdata.tcc"
template class LuaTagLib::DerivedUserdata<TagLib::ID3v2::PodcastFrame, LuaTagLib::ID3v2::Frame>;

#endif
