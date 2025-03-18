#include "mpegfile.h"

#include "mpegproperties.h"
#include "../id3v2/id3v2.h"
#include "../id3v2/id3v2tag.h"
#include "../id3v1/id3v1tag.h"
#include "../ape/apetag.h"
#include "../tiostream.h"

#define T MPEG::File
#define TT TagLib::T

using namespace LuaTagLib;

static int MPEGFile__call(lua_State* L) {
    int args = lua_gettop(L);
    TT* f = NULL;

    switch(args) {
        case 1: {
#if LTAGLIB_HAS_IOSTREAM
            if(IOStream::isValid(L, 1)) {
#if LTAGLIB_UNDER(LTAGLIB_2_0)
                f = new TT(IOStream::checkPtr(L, 1), NULL);
#else
                f = new TT(IOStream::checkPtr(L, 1));
#endif
                break;
            }
#endif
            f = new TT(checkstring(L, 1));
            lua_pop(L, 1);
            break;
        }
        case 2: {
#if LTAGLIB_HAS_IOSTREAM
            if(IOStream::isValid(L, 1)) {
#if LTAGLIB_UNDER(LTAGLIB_2_0)
                f = new TT(IOStream::checkPtr(L, 1), NULL, lua_toboolean(L,2));
#else
                f = new TT(IOStream::checkPtr(L, 1), lua_toboolean(L,2));
#endif
                break;
            }
#endif
            f = new TT(checkstring(L, 1), lua_toboolean(L, 2));
            lua_pop(L, 1);
            break;
        }
        case 3: {
#if LTAGLIB_HAS_IOSTREAM
            if(IOStream::isValid(L, 1)) {
#if LTAGLIB_UNDER(LTAGLIB_2_0)
                f = new TT(IOStream::checkPtr(L, 1), NULL, lua_toboolean(L,2), AudioProperties::ReadStyle::checkValue(L, 3));
#else
                f = new TT(IOStream::checkPtr(L, 1), lua_toboolean(L,2), AudioProperties::ReadStyle::checkValue(L, 3));
#endif
                break;
            }
#endif
            f = new TT(checkstring(L, 1), lua_toboolean(L, 2), AudioProperties::ReadStyle::checkValue(L, 3));
            lua_pop(L, 1);
            break;
        }
        default: break;
    }

    if(f == NULL) return luaL_error(L, "invalid arguments");
    T::pushPtr(L, f);
    return 1;
}

#if LTAGLIB_HAS_APE_TAG
static int File_APETag(lua_State* L) {
    TagLib::MPEG::File* f = MPEG::File::checkPtr(L, 1);
    int args = lua_gettop(L);

    switch(args) {
        case 1: {
            APE::Tag::pushPtr(L, f->APETag(), 1);
            break;
        }
        case 2: {
            APE::Tag::pushPtr(L, f->APETag(lua_toboolean(L, 2)), 1);
            break;
        }
        default: {
            return luaL_error(L, "invalid arguments");
        }
    }
    return 1;
}
#endif

#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,9,0)
static int File_hasID3v1Tag(lua_State* L) {
    TagLib::MPEG::File* f = MPEG::File::checkPtr(L, 1);
    lua_pushboolean(L, f->hasID3v1Tag());
    return 1;
}

static int File_hasID3v2Tag(lua_State* L) {
    TagLib::MPEG::File* f = MPEG::File::checkPtr(L, 1);
    lua_pushboolean(L, f->hasID3v2Tag());
    return 1;
}

static int File_hasAPETag(lua_State* L) {
    TagLib::MPEG::File* f = MPEG::File::checkPtr(L, 1);
    lua_pushboolean(L, f->hasAPETag());
    return 1;
}
#endif

static int File_audioProperties(lua_State* L) {
    TagLib::MPEG::File* f = MPEG::File::checkPtr(L, 1);
    MPEG::Properties::pushPtr(L, f->audioProperties(), 1);
    return 1;
}

static int File_save(lua_State* L) {
    int args = lua_gettop(L);
    TagLib::MPEG::File* f = MPEG::File::checkPtr(L, 1);

    /* version 1.0+ - has save(), save(int tags), returns void */
    /* version 1.2.0+ - return value changes from void to bool */
    /* version 1.4.0+ - adds save(int tags, bool stripOthers) */
    /* version 1.8.0+ - adds save(int tags, bool stripOthers, int id3v2Version) */
    /* version 1.9.0+ - adds save(int tags, bool stripOthers, int id3v2Version, bool duplicateTags) */
    /* version 1.12.0+ - deprecates v1.4, v1.8, v1.9 calls, adds
     *                   save(int tags, enum StripTags, (opt) enum ID3v2Version, (opt) enum DuplicateTags) */
    /* version 2.0+ - removes deprecated functions */

    switch(args) {
#if LTAGLIB_UNDER(LTAGLIB_1_2)
        case 1: {
            f->save();
            return 0;
        }
        case 2: {
            f->save(luaL_checkinteger(L,2));
            return 0;
        }
#else /* next two should be valid for all versions of taglib */
        case 1: {
            lua_pushboolean(L,f->save());
            return 1;
        }
        case 2: {
            lua_pushboolean(L, f->save(luaL_checkinteger(L,2)));
            return 1;
        }
/* next are the calls introduced in 1.4+ but deprecated in 1.12 */
#if LTAGLIB_UNDER(LTAGLIB_1_12)
#if LTAGLIB_ATLEAST(LTAGLIB_1_4)
        case 3: {
            lua_pushboolean(L, f->save(luaL_checkinteger(L,2), lua_toboolean(L,3)));
            return 1;
        }
#if LTAGLIB_ATLEAST(LTAGLIB_1_8)
        case 4: {
            lua_pushboolean(L, f->save(luaL_checkinteger(L,2), lua_toboolean(L,3), luaL_checkinteger(L,4)));
            return 1;
        }
#if LTAGLIB_ATLEAST(LTAGLIB_1_9)
        case 5: {
            lua_pushboolean(L, f->save(luaL_checkinteger(L,2), lua_toboolean(L,3), luaL_checkinteger(L,4), lua_toboolean(L,5)));
            return 1;
        }
#endif /* taglib <= 1.9 */
#endif /* taglib <= 1.8 */
#endif /* taglib <= 1.4 */
#else /* taglib >= 1.12 */
        case 3: {
            lua_pushboolean(L, f->save(luaL_checkinteger(L, 2), MPEG::File::StripTags::checkValue(L, 3)));
            return 1;
        }
        case 4: {
             lua_pushboolean(L, f->save(luaL_checkinteger(L, 2), MPEG::File::StripTags::checkValue(L, 3), ID3v2::Version::checkValue(L, 4)));
             return 1;
        }
        case 5: {
            lua_pushboolean(L, f->save(luaL_checkinteger(L, 2), MPEG::File::StripTags::checkValue(L, 3), ID3v2::Version::checkValue(L, 4), MPEG::File::DuplicateTags::checkValue(L, 5)));
            return 1;

        }
#endif /* end of 1.12+ */
#endif /* end of 1.2+ */
        default: break;
    }
    return luaL_error(L,"invalid arguments");
}

static int File_ID3v2Tag(lua_State* L) {
    TagLib::MPEG::File* f = MPEG::File::checkPtr(L, 1);
    int args = lua_gettop(L);

    switch(args) {
        case 1: {
            ID3v2::Tag::pushPtr(L, f->ID3v2Tag(), 1);
            break;
        }
        case 2: {
            ID3v2::Tag::pushPtr(L, f->ID3v2Tag(lua_toboolean(L, 2)), 1);
            break;
        }
        default: {
            return luaL_error(L, "invalid arguments");
        }
    }
    return 1;
}

static int File_ID3v1Tag(lua_State* L) {
    TagLib::MPEG::File* f = MPEG::File::checkPtr(L, 1);
    int args = lua_gettop(L);

    switch(args) {
        case 1: {
            ID3v1::Tag::pushPtr(L, f->ID3v1Tag(), 1);
            break;
        }
        case 2: {
            ID3v1::Tag::pushPtr(L, f->ID3v1Tag(lua_toboolean(L, 2)), 1);
            break;
        }
        default: {
            return luaL_error(L, "invalid arguments");
        }
    }
    return 1;
}

static int File_strip(lua_State* L) {
    int args = lua_gettop(L);
    TagLib::MPEG::File* f = MPEG::File::checkPtr(L, 1);

    switch(args) {
        case 1: {
            f->strip();
            break;
        }
        case 2: {
            f->strip(luaL_checkinteger(L, 2));
            break;
        }
#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,2,0)
        case 3: {
            f->strip(luaL_checkinteger(L, 2), (bool) lua_toboolean(L, 3));
            break;
        }
#endif
        default: {
            return luaL_error(L, "invalid arguments");
        }
    }

    lua_settop(L,1);
    return 1;
}

static int File_firstFrameOffset(lua_State* L) {
    TagLib::MPEG::File* f = MPEG::File::checkPtr(L, 1);
    lua_pushinteger(L, f->firstFrameOffset());
    return 1;
}

static int File_nextFrameOffset(lua_State* L) {
    TagLib::MPEG::File* f = MPEG::File::checkPtr(L, 1);
    lua_pushinteger(L, f->nextFrameOffset(luaL_checkinteger(L, 2)));
    return 1;
}

static int File_previousFrameOffset(lua_State* L) {
    TagLib::MPEG::File* f = MPEG::File::checkPtr(L, 1);
    lua_pushinteger(L, f->previousFrameOffset(luaL_checkinteger(L,2)));
    return 1;
}

static int File_lastFrameOffset(lua_State* L) {
    TagLib::MPEG::File* f = MPEG::File::checkPtr(L, 1);
    lua_pushinteger(L, f->lastFrameOffset());
    return 1;
}

static const luaL_Reg File__index[] = {
#if LTAGLIB_HAS_APE_TAG
    { "APETag", File_APETag },
#endif
#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,9,0)
    { "hasAPETag", File_hasAPETag },
    { "hasID3v1Tag", File_hasID3v1Tag },
    { "hasID3v2Tag", File_hasID3v2Tag },
#endif
    { "audioProperties", File_audioProperties },
    { "save", File_save },
    { "strip", File_strip },
    { "ID3v1Tag", File_ID3v1Tag },
    { "ID3v2Tag", File_ID3v2Tag },
    { "firstFrameOffset", File_firstFrameOffset },
    { "nextFrameOffset", File_nextFrameOffset },
    { "previousFrameOffset", File_previousFrameOffset },
    { "lastFrameOffset", File_lastFrameOffset },
    { NULL, NULL }
};

static int File__submodules(lua_State* L) {
    luaL_requiref(L, "TagLib.MPEG.File.TagTypes", luaopen_TagLib_MPEG_File_TagTypes, 0);
    lua_setfield(L, -2, "TagTypes");
    return 0;
}

LTAGLIB_PUBLIC
int luaopen_TagLib_MPEG_File_TagTypes(lua_State *L) {
    lua_newtable(L);

    lua_pushinteger(L, TagLib::MPEG::File::NoTags);
    lua_setfield(L, -2, "NoTags");

    lua_pushinteger(L, TagLib::MPEG::File::ID3v1);
    lua_setfield(L, -2, "ID3v1");

    lua_pushinteger(L, TagLib::MPEG::File::ID3v2);
    lua_setfield(L, -2, "ID3v2");

#if LTAGLIB_HAS_APE_TAG
    lua_pushinteger(L, TagLib::MPEG::File::APE);
    lua_setfield(L, -2, "APE");
#endif

    lua_pushinteger(L, TagLib::MPEG::File::AllTags);
    lua_setfield(L, -2, "AllTags");

    return 1;
}

LTAGLIB_PUBLIC
int luaopen_TagLib_MPEG_File(lua_State *L) {
    return MPEG::File::open(L);
}

template<>
const UserdataTable MPEG::File::base::mod = {
    MPEGFile__call,
    NULL,
    File__submodules,
};

template<>
const UserdataMetatable MPEG::File::base::metatable = {
    "TagLib::MPEG::File", /* name */
    File__index, /* indextable */
    NULL, /* indexfunc */
};

#undef T
#include "../shared/userdata.tcc"
template class DerivedUserdata<TagLib::MPEG::File, LuaTagLib::File>;
