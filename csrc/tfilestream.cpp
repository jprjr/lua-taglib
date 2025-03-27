#include "tfilestream.h"

#if LTAGLIB_HAS_FILESTREAM

#include "tstring.h"

#if LTAGLIB_ATLEAST(LTAGLIB_1_12)
#include <cstdio>
#endif

using namespace LuaTagLib;

static int FileStream__call(lua_State* L) {
    TagLib::FileStream* f = NULL;
    int args = lua_gettop(L);
#if LTAGLIB_ATLEAST(LTAGLIB_1_12)
#if LUA_VERSION_NUM > 501
    luaL_Stream* fstream = NULL;
#else
    FILE** fstream = NULL;
#endif
#endif

    switch(args) {
        case 1: {
#if LTAGLIB_ATLEAST(LTAGLIB_1_12)
            if(lua_isinteger(L, 1)) {
                f = new TagLib::FileStream(lua_tointeger(L, 1));
            } else
#if LUA_VERSION_NUM > 501
            if( (fstream = (luaL_Stream*) luaL_testudata(L, 1, LUA_FILEHANDLE)) != NULL )
            {
                if(fstream->f != NULL) f = new TagLib::FileStream(fileno(fstream->f));
            }
#else
            if( (fstream = (FILE**) luaL_testudata(L, 1, LUA_FILEHANDLE)) != NULL )
            {
                if(*fstream != NULL) f = new TagLib::FileStream(fileno(*fstream));
            }
#endif
            else
#endif
            if(isstring(L, 1)) {
                f = new TagLib::FileStream(checkstring(L, 1));
                lua_pop(L, 1);
            }
            break;
        }
        case 2: {
#if LTAGLIB_ATLEAST(LTAGLIB_1_12)
            if(lua_isinteger(L, 1)) {
                f = new TagLib::FileStream(lua_tointeger(L, 1), lua_toboolean(L, 2));
            } else
#if LUA_VERSION_NUM > 501
            if( (fstream = (luaL_Stream*) luaL_testudata(L, 1, LUA_FILEHANDLE)) != NULL )
            {
                if(fstream->f != NULL) f = new TagLib::FileStream(fileno(fstream->f), lua_toboolean(L, 2));
            }
#else
            if( (fstream = (FILE**) luaL_testudata(L, 1, LUA_FILEHANDLE)) != NULL )
            {
                if(*fstream != NULL) f = new TagLib::FileStream(fileno(*fstream), lua_toboolean(L, 2));
            }
#endif
            else
#endif
            if(isstring(L,1)) {
                f = new TagLib::FileStream(checkstring(L, 1), lua_toboolean(L, 2));
                lua_pop(L, 1);
            }
            break;
        }
        default: break;
    }

    if(f == NULL) return luaL_error(L, "invalid arguments");
    FileStream::pushPtr(L, f);
    return 1;
}

LTAGLIB_PUBLIC
int luaopen_TagLib_FileStream(lua_State* L) {
    return FileStream::open(L);
}

static const luaL_Reg FileStream__index[] = {
    { NULL, NULL }
};

template<>
const UserdataTable FileStream::base::mod = {
    FileStream__call,
    NULL,
    NULL,
};

template<>
const UserdataMetatable FileStream::base::metatable = {
    "TagLib::FileStream",
    FileStream__index,
    NULL
};

#include "shared/userdata.tcc"
template class DerivedUserdata<TagLib::FileStream, LuaTagLib::IOStream>;

#endif

