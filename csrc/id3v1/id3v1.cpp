#include "id3v1.h"
#include "id3v1tag.h"
#include "../tstring.h"
#include "../tstringlist.h"
#include "../tmap.h"
#include "../shared/integer.h"

#include <id3v1genres.h>

using namespace LuaTagLib;

static int
luaTagLib_ID3v1_genreList(lua_State* L) {
    StringList::pushValue(L, TagLib::ID3v1::genreList());
    return 1;
}

static int
luaTagLib_ID3v1_genre(lua_State* L) {
    String::pushValue(L, TagLib::ID3v1::genre(luaL_checkinteger(L, 1)));
    return 1;
}

static int
luaTagLib_ID3v1_genreIndex(lua_State* L) {
    lua_pushinteger(L, TagLib::ID3v1::genreIndex(String::checkValue(L, 1)));
    return 1;
}

static int
luaTagLib_ID3v1_genreMap(lua_State* L) {
    ValueMap<TagLib::ID3v1::GenreMap, String, Integer>::pushValue(L, TagLib::ID3v1::genreMap());

    return 1;
}

static const luaL_Reg methods_static[] = {
    { "genreList", luaTagLib_ID3v1_genreList },
    { "genre", luaTagLib_ID3v1_genre },
    { "genreIndex", luaTagLib_ID3v1_genreIndex },
    { "genreMap", luaTagLib_ID3v1_genreMap },
    { NULL, NULL },
};

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v1(lua_State* L) {
    lua_newtable(L);

    luaL_requiref(L, "TagLib.ID3v1.Tag", luaopen_TagLib_ID3v1_Tag, 0);
    lua_setfield(L,-2,"Tag");

    luaL_setfuncs(L, methods_static, 0);

    return 1;
}

template<>
const char* ValueMap<TagLib::ID3v1::GenreMap, String, Integer>::base::__name = "TagLib::ID3v1::GenreMap";
