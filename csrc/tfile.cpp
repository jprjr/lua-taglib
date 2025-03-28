#include "tfile.h"

#include "audioproperties.h"
#include "tag.h"
#include "tstring.h"
#include "tstringlist.h"
#include "tbytevector.h"
#include "tpropertymap.h"
#include "tvariant.h"

using namespace LuaTagLib;

#if LTAGLIB_HAS_PROPERTYMAP
static int File_properties(lua_State* L) {
    TagLib::File* f = File::checkPtr(L, 1);
    PropertyMap::pushValue(L, f->properties());
    return 1;
}

static int File_removeUnsupportedProperties(lua_State* L) {
    TagLib::File* f = File::checkPtr(L, 1);
    f->removeUnsupportedProperties(StringList::checkValue(L, 2));

    lua_settop(L,1);
    return 1;
}

static int File_setProperties(lua_State* L) {
    TagLib::File* f = File::checkPtr(L, 1);
    lua_pushvalue(L, 1);
    PropertyMap::pushValue(L, f->setProperties(PropertyMap::checkValue(L,2)));
    return 2;
}
#endif

#if LTAGLIB_HAS_VARIANT
static int File_complexPropertyKeys(lua_State* L) {
    TagLib::File* f = File::checkPtr(L, 1);

    StringList::pushValue(L, f->complexPropertyKeys());
    return 1;
}

static int File_complexProperties(lua_State* L) {
    TagLib::File* f = File::checkPtr(L, 1);

    VariantMapList::pushValue(L, f->complexProperties(String::checkValue(L, 2)));
    return 1;
}

static int File_setComplexProperties(lua_State* L) {
    TagLib::File* f = File::checkPtr(L, 1);

    lua_pushvalue(L,1);
    lua_pushboolean(L, f->setComplexProperties(String::checkValue(L, 2), VariantMapList::checkValue(L, 3)));
    return 2;
}
#endif

static int File_name(lua_State* L) {
    TagLib::File* f = File::checkPtr(L, 1);
#ifdef _WIN32
    String::pushValue(L, f->name().toString());
#else
    lua_pushstring(L, f->name());
#endif
    return 1;
}

static int File_tag(lua_State* L) {
    TagLib::File* f = File::checkPtr(L, 1);
    Tag::pushPtr(L, f->tag(), 1);
    return 1;
}

static int File_audioProperties(lua_State* L) {
    TagLib::File* f = File::checkPtr(L, 1);
    AudioProperties::pushPtr(L, f->audioProperties(), 1);
    return 1;
}

static int File_save(lua_State* L) {
    TagLib::File* f = File::checkPtr(L, 1);
#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,2,0)
    lua_pushboolean(L, f->save());
#else
    f->save();
    lua_pushboolean(L, 1);
#endif
    return 1;
}

static int File_readBlock(lua_State* L) {
    TagLib::File* f = File::checkPtr(L, 1);

    ByteVector::pushValue(L, f->readBlock(luaL_checkinteger(L,2)));
    return 1;
}

static int File_writeBlock(lua_State* L) {
    TagLib::File* f = File::checkPtr(L, 1);

    f->writeBlock(ByteVector::looseValue(L, 2));
    return 0;
}

static int File_find(lua_State* L) {
    TagLib::File* f = File::checkPtr(L, 1);
    int args = lua_gettop(L);

    switch(args) {
        case 2: {
            lua_pushinteger(L, f->find(ByteVector::looseValue(L, 2)));
            break;
        }
        case 3: {
            lua_pushinteger(L, f->find(ByteVector::looseValue(L, 2), luaL_checkinteger(L, 3)));
            break;
        }
        case 4: {
            lua_pushinteger(L, f->find(ByteVector::looseValue(L, 2), luaL_checkinteger(L, 3), ByteVector::looseValue(L, 4)));
            break;
        }
        default: {
            return luaL_error(L, "invalid arguments");
        }
    }

    return 1;
}

static int File_rfind(lua_State* L) {
    TagLib::File* f = File::checkPtr(L, 1);
    int args = lua_gettop(L);

    switch(args) {
        case 2: {
            lua_pushinteger(L, f->rfind(ByteVector::looseValue(L, 2)));
            break;
        }
        case 3: {
            lua_pushinteger(L, f->rfind(ByteVector::looseValue(L, 2), luaL_checkinteger(L, 3)));
            break;
        }
        case 4: {
            lua_pushinteger(L, f->rfind(ByteVector::looseValue(L, 2), luaL_checkinteger(L, 3), ByteVector::looseValue(L, 4)));
            break;
        }
        default: {
            return luaL_error(L, "invalid arguments");
        }
    }

    return 1;
}

static int File_insert(lua_State* L) {
    TagLib::File* f = File::checkPtr(L, 1);
    int args = lua_gettop(L);

    switch(args) {
        case 2: {
            f->insert(ByteVector::looseValue(L, 2));
            break;
        }
        case 3: {
            f->insert(ByteVector::looseValue(L, 2), luaL_checkinteger(L, 3));
            break;
        }
        case 4: {
            f->insert(ByteVector::looseValue(L, 2), luaL_checkinteger(L, 3), luaL_checkinteger(L, 4));
            break;
        }
        default: {
            return luaL_error(L, "invalid arguments");
        }
    }

    return 0;
}

static int File_removeBlock(lua_State* L) {
    TagLib::File* f = File::checkPtr(L, 1);
    int args = lua_gettop(L);

    switch(args) {
        case 1: {
            f->removeBlock();
            break;
        }
        case 2: {
            f->removeBlock(luaL_checkinteger(L, 2));
            break;
        }
        case 3: {
            f->removeBlock(luaL_checkinteger(L, 2), luaL_checkinteger(L, 3));
            break;
        }
        default: {
            return luaL_error(L, "invalid arguments");
        }
    }

    return 0;
}

static int File_readOnly(lua_State* L) {
    TagLib::File* f = File::checkPtr(L, 1);
    lua_pushboolean(L, f->readOnly());
    return 1;
}

static int File_isOpen(lua_State* L) {
    TagLib::File* f = File::checkPtr(L, 1);
    lua_pushboolean(L, f->isOpen());
    return 1;
}

static int File_isValid(lua_State* L) {
    TagLib::File* f = File::checkPtr(L, 1);
    lua_pushboolean(L, f->isValid());
    return 1;
}

static int File_length(lua_State* L) {
    TagLib::File* f = File::checkPtr(L, 1);
    lua_pushinteger(L, f->length());
    return 1;
}

static int File_tell(lua_State* L) {
    TagLib::File* f = File::checkPtr(L, 1);
    lua_pushinteger(L, f->tell());
    return 1;
}

static int File_clear(lua_State* L) {
    TagLib::File* f = File::checkPtr(L, 1);
    f->clear();
    return 0;
}

static int File_seek(lua_State* L) {
    int args = lua_gettop(L);
    TagLib::File* f = File::checkPtr(L, 1);

    switch(args) {
        case 2: {
            f->seek(luaL_checkinteger(L, 2));
            break;
        }
        case 3: {
            f->seek(luaL_checkinteger(L, 2), File::Position::checkValue(L, 3));
            break;
        }
        default: {
            return luaL_error(L, "invalid arguments");
        }
    }
    return 0;
}

static const luaL_Reg File__index[] = {
#if LTAGLIB_HAS_PROPERTYMAP
    { "properties", File_properties },
    { "removeUnsupportedProperties", File_removeUnsupportedProperties },
    { "setProperties", File_setProperties },
#endif
#if LTAGLIB_HAS_VARIANT
    { "complexPropertyKeys", File_complexPropertyKeys },
    { "complexProperties", File_complexProperties },
    { "setComplexProperties", File_setComplexProperties },
#endif
    { "name", File_name },
    { "tag", File_tag },
    { "audioProperties", File_audioProperties },
    { "save", File_save },
    { "readBlock", File_readBlock },
    { "writeBlock", File_writeBlock },
    { "find", File_find },
    { "rfind", File_rfind },
    { "insert", File_insert },
    { "removeBlock", File_removeBlock },
    { "readOnly", File_readOnly },
    { "isOpen", File_isOpen },
    { "isValid", File_isValid },
    { "length", File_length },
    { "tell", File_tell },
    { "clear", File_clear },
    { "seek", File_seek },
    { NULL, NULL }
};

#if LTAGLIB_UNDER(LTAGLIB_1_12)
static int File_static_isReadable(lua_State* L) {
    bool res = TagLib::File::isReadable(checkstring(L, 1));
    lua_pop(L, 1);
    lua_pushboolean(L, res);
    return 1;
}

static int File_static_isWritable(lua_State* L) {
    bool res = TagLib::File::isWritable(checkstring(L, 1));
    lua_pop(L, 1);
    lua_pushboolean(L, res);
    return 1;
}
#endif

static const luaL_Reg File_static_methods[] = {
#if LTAGLIB_UNDER(LTAGLIB_1_12)
    { "isReadable", File_static_isReadable },
    { "isWritable", File_static_isWritable },
#endif
    { NULL, NULL }
};

template<>
const UserdataMetatable File::base::metatable = {
    "TagLib::File", /* name */
    File__index, /* indextable */
    NULL, /* indexfunc */
};

#define E(x) { #x, sizeof(#x) - 1, TagLib::File::x }

static const File::Position::enum_type filePositions[] = {
    E(Beginning),
    E(Current),
    E(End),
};

template<>
const File::Position::enum_type* File::Position::m_values = filePositions;

template<>
const size_t File::Position::m_len = sizeof(filePositions) / sizeof(filePositions[0]);

LTAGLIB_PUBLIC
int luaopen_TagLib_File_Position(lua_State *L) {
    File::Position::open(L);
    return 1;
}

#if LTAGLIB_HAS_FILE_STRIPTAGS

static const File::StripTags::enum_type fileStripTags[] = {
    E(StripNone), E(StripOthers)
};

template<>
const File::StripTags::enum_type* File::StripTags::m_values = fileStripTags;

template<>
const size_t File::StripTags::m_len = sizeof(fileStripTags) / sizeof(fileStripTags[0]);


LTAGLIB_PUBLIC
int luaopen_TagLib_File_StripTags(lua_State *L) {
    File::StripTags::open(L);
    return 1;
}

#endif

#if LTAGLIB_HAS_FILE_DUPLICATETAGS

static const File::DuplicateTags::enum_type fileDuplicateTags[] = {
    E(Duplicate), E(DoNotDuplicate)
};

template<>
const File::DuplicateTags::enum_type* File::DuplicateTags::m_values = fileDuplicateTags;

template<>
const size_t File::DuplicateTags::m_len = sizeof(fileDuplicateTags) / sizeof(fileDuplicateTags[0]);


LTAGLIB_PUBLIC
int luaopen_TagLib_File_DuplicateTags(lua_State *L) {
    File::DuplicateTags::open(L);
    return 1;
}

#endif

static int File_submodules(lua_State* L) {
    luaL_requiref(L, "TagLib.File.Position", luaopen_TagLib_File_Position, 0);
    lua_setfield(L, -2, "Position");

#if LTAGLIB_HAS_FILE_STRIPTAGS
    luaL_requiref(L, "TagLib.File.StripTags", luaopen_TagLib_File_StripTags, 0);
    lua_setfield(L, -2, "StripTags");
#endif

#if LTAGLIB_HAS_FILE_DUPLICATETAGS
    luaL_requiref(L, "TagLib.File.DuplicateTags", luaopen_TagLib_File_DuplicateTags, 0);
    lua_setfield(L, -2, "DuplicateTags");
#endif
    return 0;
}


LTAGLIB_PUBLIC
int luaopen_TagLib_File(lua_State *L) {
    return File::open(L);
}

#include "shared/enum.tcc"

template class LuaTagLib::Enum<TagLib::File::Position>;

#if LTAGLIB_HAS_FILE_STRIPTAGS
template class LuaTagLib::Enum<TagLib::File::StripTags>;
#endif

#if LTAGLIB_HAS_FILE_DUPLICATETAGS
template class LuaTagLib::Enum<TagLib::File::DuplicateTags>;
#endif

template<>
const UserdataTable File::base::mod = {
    NULL,
    File_static_methods,
    File_submodules,
};


#include "shared/userdata.tcc"
template class LuaTagLib::BaseUserdata<TagLib::File>;
