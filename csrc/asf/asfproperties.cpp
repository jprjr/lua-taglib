#include "asfproperties.h"

#if LTAGLIB_HAS_ASF

#include "../tbytevector.h"

#if LTAGLIB_ATLEAST(LTAGLIB_1_10)
#include "../tstring.h"
#endif

using namespace LuaTagLib;

static int Properties__call(lua_State* L) {
    int args = lua_gettop(L);
    TagLib::ASF::Properties* p = NULL;

    switch(args) {
        case 0: {
            p = new TagLib::ASF::Properties();
            break;
        }
    }

    if(p == NULL) return luaL_error(L, "invalid arguments");
    ASF::Properties::pushPtr(L, p);
    return 1;
}

#if LTAGLIB_ATLEAST(LTAGLIB_1_8)
static int Properties_isEncrypted(lua_State* L) {
    lua_pushboolean(L,
      ASF::Properties::checkPtr(L,1)->isEncrypted()
    );
    return 1;
}
#endif

#if LTAGLIB_ATLEAST(LTAGLIB_1_10)
static int Properties_bitsPerSample(lua_State* L) {
    lua_pushinteger(L,
      ASF::Properties::checkPtr(L,1)->bitsPerSample()
    );
    return 1;
}

static int Properties_codec(lua_State* L) {
    ASF::Properties::Codec::pushValue(L,
      ASF::Properties::checkPtr(L,1)->codec()
    );
    return 1;
}

static int Properties_codecName(lua_State* L) {
    String::pushValue(L,
      ASF::Properties::checkPtr(L,1)->codecName()
    );
    return 1;
}

static int Properties_codecDescription(lua_State* L) {
    String::pushValue(L,
      ASF::Properties::checkPtr(L,1)->codecDescription()
    );
    return 1;
}
#endif

static
const luaL_Reg Properties__index[] = {
#if LTAGLIB_ATLEAST(LTAGLIB_1_8)
    { "isEncrypted", Properties_isEncrypted },
#endif
#if LTAGLIB_ATLEAST(LTAGLIB_1_10)
    { "bitsPerSample", Properties_bitsPerSample },
    { "codec", Properties_codec },
    { "codecName", Properties_codecName },
    { "codecDescription", Properties_codecDescription },
#endif
    { NULL, NULL },
};

static int Properties__submodules(lua_State* L) {
#if LTAGLIB_ATLEAST(LTAGLIB_1_10)
    luaL_requiref(L, "TagLib.ASF.Properties.Codec", luaopen_TagLib_ASF_Properties_Codec, 0);
    lua_setfield(L, -2, "Codec");
#else
    (void)L;
#endif
    return 0;
}

LTAGLIB_PUBLIC
int luaopen_TagLib_ASF_Properties(lua_State *L) {
    return ASF::Properties::open(L);
}

#if LTAGLIB_ATLEAST(LTAGLIB_1_10)
LTAGLIB_PUBLIC
int luaopen_TagLib_ASF_Properties_Codec(lua_State *L) {
    return ASF::Properties::Codec::open(L);
}
#endif

template<>
const UserdataTable ASF::Properties::base::mod = {
    Properties__call,
    NULL,
    Properties__submodules,
};

template<>
const UserdataMetatable ASF::Properties::base::metatable = {
    "TagLib::ASF::Properties", /* name */
    Properties__index, /* indextable */
    NULL, /* indexfunc */
};

#if LTAGLIB_ATLEAST(LTAGLIB_1_10)

#define E(x) { #x, sizeof(#x) - 1, TagLib::ASF::Properties::x }
static const ASF::Properties::Codec::enum_type asfCodec[] = {
    E(Unknown), E(WMA1), E(WMA2), E(WMA9Pro),
    E(WMA9Lossless)
};

template<>
const ASF::Properties::Codec::enum_type* ASF::Properties::Codec::m_values = asfCodec;

template<>
const size_t ASF::Properties::Codec::m_len = sizeof(asfCodec) / sizeof(asfCodec[0]);

#include "../shared/enum.tcc"
template class LuaTagLib::Enum<TagLib::ASF::Properties::Codec>;

#endif

#include "../shared/userdata.tcc"
template class LuaTagLib::DerivedUserdata<TagLib::ASF::Properties, LuaTagLib::AudioProperties>;

#endif
