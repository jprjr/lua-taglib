#include "tag.h"

#include "tstring.h"
#include "tstringlist.h"
#include "tpropertymap.h"
#include "tvariant.h"

using namespace LuaTagLib;

#if LTAGLIB_HAS_PROPERTYMAP
static int Tag_properties(lua_State* L) {
    TagLib::Tag* tag = Tag::checkPtr(L, 1);
    PropertyMap::pushValue(L, tag->properties());
    return 1;
}

static int Tag_removeUnsupportedProperties(lua_State* L) {
    TagLib::Tag* tag = Tag::checkPtr(L, 1);
    tag->removeUnsupportedProperties(StringList::checkValue(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Tag_setProperties(lua_State* L) {
    TagLib::Tag* tag = Tag::checkPtr(L, 1);

    lua_pushvalue(L, 1);
    PropertyMap::pushValue(L, tag->setProperties(PropertyMap::checkValue(L, 2)));
    return 2;
}
#endif

#if LTAGLIB_HAS_VARIANT
static int Tag_complexPropertyKeys(lua_State* L) {
    TagLib::Tag* tag = Tag::checkPtr(L, 1);

    StringList::pushValue(L, tag->complexPropertyKeys());
    return 1;
}

static int Tag_complexProperties(lua_State* L) {
    TagLib::Tag* tag = Tag::checkPtr(L, 1);

    VariantMapList::pushValue(L, tag->complexProperties(String::checkValue(L, 2)));
    return 1;
}

static int Tag_setComplexProperties(lua_State* L) {
    TagLib::Tag* tag = Tag::checkPtr(L, 1);
    lua_pushvalue(L, 1);
    lua_pushboolean(L, tag->setComplexProperties(String::checkValue(L, 2), VariantMapList::checkValue(L, 3)));
    return 2;
}
#endif

static int Tag_title(lua_State* L) {
    TagLib::Tag* tag = Tag::checkPtr(L, 1);

    String::pushValue(L, tag->title());
    return 1;
}

static int Tag_artist(lua_State* L) {
    TagLib::Tag* tag = Tag::checkPtr(L, 1);

    String::pushValue(L, tag->artist());
    return 1;
}

static int Tag_album(lua_State* L) {
    TagLib::Tag* tag = Tag::checkPtr(L, 1);

    String::pushValue(L, tag->album());
    return 1;
}

static int Tag_comment(lua_State* L) {
    TagLib::Tag* tag = Tag::checkPtr(L, 1);

    String::pushValue(L, tag->comment());
    return 1;
}

static int Tag_genre(lua_State* L) {
    TagLib::Tag* tag = Tag::checkPtr(L, 1);

    String::pushValue(L, tag->genre());
    return 1;
}

static int Tag_year(lua_State* L) {
    TagLib::Tag* tag = Tag::checkPtr(L, 1);

    lua_pushinteger(L,tag->year());
    return 1;
}

static int Tag_track(lua_State* L) {
    TagLib::Tag* tag = Tag::checkPtr(L, 1);

    lua_pushinteger(L,tag->track());
    return 1;
}

static int Tag_setTitle(lua_State* L) {
    TagLib::Tag* tag = Tag::checkPtr(L, 1);
    tag->setTitle(String::optValue(L, 2));

    lua_settop(L,1);
    return 1;
}

static int Tag_setArtist(lua_State* L) {
    TagLib::Tag* tag = Tag::checkPtr(L, 1);
    tag->setArtist(String::optValue(L, 2));

    lua_settop(L,1);
    return 1;
}

static int Tag_setAlbum(lua_State* L) {
    TagLib::Tag* tag = Tag::checkPtr(L, 1);
    tag->setAlbum(String::optValue(L, 2));

    lua_settop(L,1);
    return 1;
}

static int Tag_setComment(lua_State* L) {
    TagLib::Tag* tag = Tag::checkPtr(L, 1);
    tag->setComment(String::optValue(L, 2));

    lua_settop(L,1);
    return 1;
}

static int Tag_setGenre(lua_State* L) {
    TagLib::Tag* tag = Tag::checkPtr(L, 1);
    tag->setGenre(String::optValue(L, 2));

    lua_settop(L,1);
    return 1;
}

static int Tag_setYear(lua_State* L) {
    TagLib::Tag* tag = Tag::checkPtr(L, 1);
    tag->setYear(luaL_optinteger(L,2,0));

    lua_settop(L,1);
    return 1;
}

static int Tag_setTrack(lua_State* L) {
    TagLib::Tag* tag = Tag::checkPtr(L, 1);
    tag->setTrack(luaL_optinteger(L,2,0));

    lua_settop(L,1);
    return 1;
}

static int Tag_isEmpty(lua_State* L) {
    TagLib::Tag* tag = Tag::checkPtr(L, 1);
    lua_pushboolean(L,tag->isEmpty());

    return 1;
}

static const luaL_Reg Tag__index[] = {
#if LTAGLIB_HAS_PROPERTYMAP
    { "properties", Tag_properties },
    { "setProperties", Tag_setProperties },
    { "removeUnsupportedProperties", Tag_removeUnsupportedProperties },
#endif
#if LTAGLIB_HAS_VARIANT
    { "complexPropertyKeys", Tag_complexPropertyKeys },
    { "complexProperties", Tag_complexProperties },
    { "setComplexProperties", Tag_setComplexProperties },
#endif

    { "title",   Tag_title },
    { "artist",  Tag_artist },
    { "album",   Tag_album },
    { "comment", Tag_comment },
    { "genre",   Tag_genre },
    { "year",    Tag_year },
    { "track",   Tag_track },

    { "setTitle",   Tag_setTitle },
    { "setArtist",  Tag_setArtist },
    { "setAlbum",   Tag_setAlbum },
    { "setComment", Tag_setComment },
    { "setGenre",   Tag_setGenre },
    { "setYear",    Tag_setYear },
    { "setTrack",   Tag_setTrack },

    { "isEmpty", Tag_isEmpty },

    { NULL, NULL }
};

static int Tag_static_duplicate(lua_State* L) {
    int args = lua_gettop(L);

    switch(args) {
        case 2: {
            TagLib::Tag::duplicate(
              Tag::checkPtr(L, 1),
              Tag::checkPtr(L, 2));
            break;
        }
        case 3: {
            TagLib::Tag::duplicate(
              Tag::checkPtr(L, 1),
              Tag::checkPtr(L, 2),
              lua_toboolean(L, 3));
            break;
        }
        default: return luaL_error(L, "invalid arguments");
    }
    return 0;
}

#if LTAGLIB_ATLEAST(LTAGLIB_2_0)
static int Tag_static_joinTagValues(lua_State* L) {
    String::pushValue(L,
      TagLib::Tag::joinTagValues(StringList::checkValue(L,1))
    );
    return 1;
}
#endif

static const luaL_Reg Tag_static__index[] = {
    { "duplicate", Tag_static_duplicate },
#if LTAGLIB_ATLEAST(LTAGLIB_2_0)
    { "joinTagValues", Tag_static_joinTagValues },
#endif
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_Tag(lua_State* L) {
    return Tag::open(L);
}

template<>
const UserdataTable Tag::base::mod = {
    NULL, /* __call */
    Tag_static__index,
    NULL,
};

template<>
const UserdataMetatable Tag::base::metatable = {
    "TagLib::Tag",
    Tag__index, /* indextable */
    NULL,
};

#include "shared/userdata.tcc"
template class BaseUserdata<TagLib::Tag>;
