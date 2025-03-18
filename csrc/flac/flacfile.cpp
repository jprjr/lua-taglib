#include "flacfile.h"
#include "flacpicture.h"
#include "flacproperties.h"

#include "../tlist.h"
#include "../id3v1/id3v1tag.h"
#include "../id3v2/id3v2tag.h"
#include "../ogg/xiphcomment.h"
#include "../tiostream.h"

#if LTAGLIB_ATLEAST(LTAGLIB_1_8) && LTAGLIB_UNDER(LTAGLIB_1_12)
/* needed for streamInfoData() */
#include "../tbytevector.h"
#endif

#define T FLAC::File
#define TT TagLib::T

using namespace LuaTagLib;

static int FLACFile__call(lua_State* L) {
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

#if LTAGLIB_ATLEAST(LTAGLIB_1_7)
static int File_pictureList(lua_State* L) {
    TagLib::FLAC::File* f = FLAC::File::checkPtr(L, 1);
    PtrList< TagLib::List<TagLib::FLAC::Picture*>, FLAC::Picture>::pushPtr(L, f->pictureList(), 1);
    return 1;
}

static int File_removePictures(lua_State* L) {
    TagLib::FLAC::File* f = FLAC::File::checkPtr(L, 1);
    f->removePictures();
    lua_settop(L,1);
    return 1;
}

static int File_addPicture(lua_State* L) {
    TagLib::FLAC::File* f = FLAC::File::checkPtr(L, 1);
    TagLib::FLAC::Picture* pic = FLAC::Picture::checkPtr(L, 2);
    f->addPicture(pic);
    lua_settop(L,1);
    return 1;
}
#endif

#if LTAGLIB_ATLEAST(LTAGLIB_1_8)
static int File_removePicture(lua_State* L) {
    TagLib::FLAC::File* f = FLAC::File::checkPtr(L, 1);
    int args = lua_gettop(L);
    switch(args) {
        case 2: {
            f->removePicture(FLAC::Picture::checkPtr(L, 2));
            break;
        }
        case 3: {
            f->removePicture(FLAC::Picture::checkPtr(L, 2), lua_toboolean(L, 3));
            break;
        }
        default: {
            return luaL_error(L, "invalid arguments");
        }
    }

    lua_settop(L,1);
    return 1;
}

#if LTAGLIB_UNDER(LTAGLIB_1_12)
static int File_streamInfoData(lua_State* L) {
   TagLib::FLAC::File* f = FLAC::File::checkPtr(L, 1);
   ByteVector::pushValue(L, f->streamInfoData());
   return 1;
}
#endif

#endif

#if LTAGLIB_ATLEAST(LTAGLIB_1_2)
static int File_ID3v2Tag(lua_State* L) {
    TagLib::FLAC::File* f = FLAC::File::checkPtr(L, 1);
    int args = lua_gettop(L);

    switch(args) {
        case 1: {
            ID3v2::Tag::pushPtr(L, f->ID3v2Tag(), 1);
            break;
        }
        case 2: {
            ID3v2::Tag::pushPtr(L, f->ID3v2Tag((bool) lua_toboolean(L, 2)), 1);
            break;
        }
        default: {
            return luaL_error(L, "invalid arguments");
        }
    }
    return 1;
}

static int File_ID3v1Tag(lua_State* L) {
    TagLib::FLAC::File* f = FLAC::File::checkPtr(L, 1);
    int args = lua_gettop(L);

    switch(args) {
        case 1: {
            ID3v1::Tag::pushPtr(L, f->ID3v1Tag(), 1);
            break;
        }
        case 2: {
            ID3v1::Tag::pushPtr(L, f->ID3v1Tag((bool) lua_toboolean(L, 2)), 1);
            break;
        }
        default: {
            return luaL_error(L, "invalid arguments");
        }
    }
    return 1;
}

static int File_xiphComment(lua_State* L) {
    TagLib::FLAC::File* f = FLAC::File::checkPtr(L, 1);
    int args = lua_gettop(L);

    switch(args) {
        case 1: {
            Ogg::XiphComment::pushPtr(L, f->xiphComment(), 1);
            break;
        }
        case 2: {
            Ogg::XiphComment::pushPtr(L, f->xiphComment((bool) lua_toboolean(L, 2)), 1);
            break;
        }
        default: {
            return luaL_error(L, "invalid arguments");
        }
    }
    return 1;
}

#if LTAGLIB_UNDER(LTAGLIB_1_12)
static int File_streamLength(lua_State* L) {
    lua_pushinteger(L, FLAC::File::checkPtr(L,1)->streamLength());
    return 1;
}
#endif

#endif

#if LTAGLIB_ATLEAST(LTAGLIB_1_9)
static int File_hasXiphComment(lua_State* L) {
    TagLib::FLAC::File* f = FLAC::File::checkPtr(L, 1);
    lua_pushboolean(L, f->hasXiphComment());
    return 1;
}

static int File_hasID3v1Tag(lua_State* L) {
    TagLib::FLAC::File* f = FLAC::File::checkPtr(L, 1);
    lua_pushboolean(L, f->hasID3v1Tag());
    return 1;
}

static int File_hasID3v2Tag(lua_State* L) {
    TagLib::FLAC::File* f = FLAC::File::checkPtr(L, 1);
    lua_pushboolean(L, f->hasID3v2Tag());
    return 1;
}
#endif

#if LTAGLIB_ATLEAST(LTAGLIB_1_11)
static int File_strip(lua_State* L) {
    TagLib::FLAC::File* f = FLAC::File::checkPtr(L, 1);

    switch(lua_gettop(L)) {
        case 1: {
            f->strip();
            break;
        }
        case 2: {
            f->strip(luaL_checkinteger(L, 2));
            break;
        }
        default: {
            return luaL_error(L, "invalid arguments");
        }
    }

    lua_settop(L,1);
    return 1;
}
#endif

static int File_audioProperties(lua_State* L) {
   TagLib::FLAC::File* f = FLAC::File::checkPtr(L, 1);
   FLAC::Properties::pushPtr(L, f->audioProperties(), 1);
   return 1;
}

static
const luaL_Reg File__index[] = {
#if LTAGLIB_ATLEAST(LTAGLIB_1_2)
    { "ID3v2Tag", File_ID3v2Tag },
    { "ID3v1Tag", File_ID3v1Tag },
    { "xiphComment", File_xiphComment },
#if LTAGLIB_UNDER(LTAGLIB_1_12)
    { "streamLength", File_streamLength },
#endif
#endif
#if LTAGLIB_ATLEAST(LTAGLIB_1_7)
    { "pictureList", File_pictureList },
    { "removePictures", File_removePictures },
    { "addPicture", File_addPicture },
#endif
#if LTAGLIB_ATLEAST(LTAGLIB_1_8)
    { "removePicture", File_removePicture },
#if LTAGLIB_UNDER(LTAGLIB_1_12)
    { "streamInfoData", File_streamInfoData },
#endif
#endif
#if LTAGLIB_ATLEAST(LTAGLIB_1_9)
    { "hasID3v2Tag", File_hasID3v2Tag },
    { "hasID3v1Tag", File_hasID3v1Tag },
    { "hasXiphComment", File_hasXiphComment },
#endif
    { "audioProperties", File_audioProperties },
#if LTAGLIB_ATLEAST(LTAGLIB_1_11)
    { "strip", File_strip },
#endif
    { NULL, NULL }
};

static int File__submodules(lua_State* L) {
#if LTAGLIB_ATLEAST(LTAGLIB_1_11)
    luaL_requiref(L, "TagLib.FLAC.File.TagTypes", luaopen_TagLib_FLAC_File_TagTypes, 0);
    lua_setfield(L, -2, "TagTypes");
#else
    (void)L;
#endif
    return 0;
}

#if LTAGLIB_ATLEAST(LTAGLIB_1_11)

LTAGLIB_PUBLIC
int luaopen_TagLib_FLAC_File_TagTypes(lua_State *L) {
    lua_newtable(L);

    lua_pushinteger(L, TagLib::FLAC::File::NoTags);
    lua_setfield(L, -2, "NoTags");

    lua_pushinteger(L, TagLib::FLAC::File::XiphComment);
    lua_setfield(L, -2, "XiphComment");

    lua_pushinteger(L, TagLib::FLAC::File::ID3v1);
    lua_setfield(L, -2, "ID3v1");

    lua_pushinteger(L, TagLib::FLAC::File::ID3v2);
    lua_setfield(L, -2, "ID3v2");

    lua_pushinteger(L, TagLib::FLAC::File::AllTags);
    lua_setfield(L, -2, "AllTags");

    return 1;
}

#endif

LTAGLIB_PUBLIC
int luaopen_TagLib_FLAC_File(lua_State *L) {
    return FLAC::File::open(L);
}

template<>
const UserdataTable FLAC::File::base::mod = {
    FLACFile__call,
    NULL,
    File__submodules,
};

template<>
const UserdataMetatable FLAC::File::base::metatable = {
    "TagLib::FLAC::File", /* name */
    File__index, /* indextable */
    NULL, /* indexfunc */
};

#undef T
#include "../shared/userdata.tcc"
template class DerivedUserdata<TagLib::FLAC::File, LuaTagLib::File>;
