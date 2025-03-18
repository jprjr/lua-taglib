#include "apeproperties.h"

#if LTAGLIB_HAS_APE_PROPERTIES

#include "apefile.h"
#include "../tbytevector.h"

using namespace LuaTagLib;

static int Properties__call(lua_State* L) {
    int args = lua_gettop(L);
    TagLib::APE::Properties* p = NULL;

    switch(args) {
#if LTAGLIB_VERSION < LTAGLIB_VERSION_NUM(1,10,0)
        case 1: {
            p = TagLib::APE::Properties(APE::File::checkPtr(L, 1));
            break;
        }
#endif
        case 2: {
#if LTAGLIB_VERSION < LTAGLIB_VERSION_NUM(1,10,0)
            p = new TagLib::APE::Properties(APE::File::checkPtr(L, 1), AudioProperties::ReadStyle::checkValue(L, 2));
#else
            p = new TagLib::APE::Properties(APE::File::checkPtr(L, 1), luaL_checkinteger(L, 2));
#endif
            break;
        }
#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,10,0)
        case 3: {
            p = new TagLib::APE::Properties(APE::File::checkPtr(L, 1), luaL_checkinteger(L, 2), AudioProperties::ReadStyle::checkValue(L, 3));
            break;
        }
#endif
        default: break;
    }

    if(p == NULL) return luaL_error(L, "invalid arguments");
    APE::Properties::pushPtr(L, p);
    return 1;
}

#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,8,0)
static int Properties_sampleFrames(lua_State* L) {
    TagLib::APE::Properties* ap = APE::Properties::checkPtr(L, 1);
    lua_pushinteger(L, ap->sampleFrames());
    return 1;
}
#endif

static int Properties_bitsPerSample(lua_State* L) {
    TagLib::APE::Properties* ap = APE::Properties::checkPtr(L, 1);
    lua_pushinteger(L, ap->bitsPerSample());
    return 1;
}

static int Properties_version(lua_State* L) {
    TagLib::APE::Properties* ap = APE::Properties::checkPtr(L, 1);
    lua_pushinteger(L, ap->version());
    return 1;
}

static
const luaL_Reg Properties__index[] = {
#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,8,0)
    { "sampleFrames", Properties_sampleFrames },
#endif
    { "bitsPerSample", Properties_bitsPerSample },
    { "version", Properties_version },
    { NULL, NULL }
};


LTAGLIB_PUBLIC
int luaopen_TagLib_APE_Properties(lua_State *L) {
    return APE::Properties::open(L);
}

template<>
const UserdataTable APE::Properties::base::mod = {
    Properties__call,
    NULL,
    NULL,
};

template<>
const UserdataMetatable APE::Properties::base::metatable = {
    "TagLib::APE::Properties", /* name */
    Properties__index, /* indextable */
    NULL, /* indexfunc */
};

#include "../shared/userdata.tcc"
template class DerivedUserdata<TagLib::APE::Properties, LuaTagLib::AudioProperties>;

#endif
