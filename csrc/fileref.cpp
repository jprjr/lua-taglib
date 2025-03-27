#include "fileref.h"

#include "tfile.h"
#include "audioproperties.h"
#include "tag.h"
#include "tbytevector.h"
#include "tstringlist.h"

#if LTAGLIB_ATLEAST(LTAGLIB_2_0)
#include "tpropertymap.h"
#include "tvariant.h"
#endif

using namespace LuaTagLib;

static int FileRef__call(lua_State* L) {
    int args = lua_gettop(L);

    UserdataPointer<TagLib::File>* file = NULL;
    TagLib::FileRef* f = NULL;

    switch(args) {
        case 1: {
            if( (file = File::optInstance(L, 1)) != NULL) {
                f = new TagLib::FileRef(file->getPtr());
                file->unmanage();
                break;
            }
            f = new TagLib::FileRef(checkstring(L, 1));
            lua_pop(L, 1);
            break;
        }
        case 2: {
            f = new TagLib::FileRef(checkstring(L, 1), lua_toboolean(L, 2));
            lua_pop(L, 1);
            break;
        }
        case 3: {
            f = new TagLib::FileRef(checkstring(L, 1), lua_toboolean(L, 2), AudioProperties::ReadStyle::checkValue(L, 3));
            lua_pop(L, 1);
            break;
        }
        default: break;
    }

    if(f == NULL) return luaL_error(L, "invalid arguments");
    FileRef::pushPtr(L, f);
    return 1;
}

static int FileRef_tag(lua_State* L) {
    TagLib::FileRef* f = FileRef::checkPtr(L, 1);
    Tag::pushPtr(L, f->tag(), 1);
    return 1;
}

static int FileRef_audioProperties(lua_State* L) {
    TagLib::FileRef* f = FileRef::checkPtr(L, 1);
    AudioProperties::pushPtr(L, f->audioProperties(), 1);
    return 1;
}

static int FileRef_file(lua_State* L) {
    TagLib::FileRef* f = FileRef::checkPtr(L, 1);
    File::pushPtr(L, f->file(), 1);
    return 1;
}

static int FileRef_save(lua_State* L) {
    TagLib::FileRef* f = FileRef::checkPtr(L, 1);
    f->save();
    return 0;
}

static int FileRef_isNull(lua_State* L) {
    TagLib::FileRef* f = FileRef::checkPtr(L, 1);
    lua_pushboolean(L, f->isNull());
    return 1;
}

#if LTAGLIB_ATLEAST(LTAGLIB_1_11)
static int FileRef_swap(lua_State* L) {
    FileRef::checkPtr(L,1)->swap(FileRef::checkValue(L,2));
    lua_settop(L,1);
    return 1;
}
#endif

#if LTAGLIB_ATLEAST(LTAGLIB_2_0)
static int FileRef_properties(lua_State* L) {
    TagLib::FileRef* f = FileRef::checkPtr(L, 1);
    PropertyMap::pushValue(L, f->properties());
    return 1;
}

static int FileRef_removeUnsupportedProperties(lua_State* L) {
    TagLib::FileRef* f = FileRef::checkPtr(L, 1);
    f->removeUnsupportedProperties(StringList::checkValue(L, 2));

    lua_settop(L,1);
    return 1;
}

static int FileRef_setProperties(lua_State* L) {
    TagLib::FileRef* f = FileRef::checkPtr(L, 1);

    lua_pushvalue(L,1);
    PropertyMap::pushValue(L, f->setProperties(PropertyMap::checkValue(L, 2)));
    return 2;
}

static int FileRef_complexPropertyKeys(lua_State* L) {
    TagLib::FileRef* f = FileRef::checkPtr(L, 1);
    StringList::pushValue(L, f->complexPropertyKeys());
    return 1;
}

static int FileRef_complexProperties(lua_State* L) {
    TagLib::FileRef* f = FileRef::checkPtr(L, 1);
    VariantMapList::pushValue(L, f->complexProperties(String::checkValue(L, 2)));
    return 1;
}

static int FileRef_setComplexProperties(lua_State* L) {
    TagLib::FileRef* f = FileRef::checkPtr(L, 1);

    lua_pushvalue(L,1);
    lua_pushboolean(L, f->setComplexProperties(String::checkValue(L, 2), VariantMapList::checkValue(L, 3)));
    return 2;
}
#endif

static
const luaL_Reg FileRef__index[] = {
    { "tag", FileRef_tag },
    { "audioProperties", FileRef_audioProperties },
    { "file", FileRef_file },
    { "save", FileRef_save },
    { "isNull", FileRef_isNull },
#if LTAGLIB_ATLEAST(LTAGLIB_1_11)
    { "swap", FileRef_swap },
#endif
#if LTAGLIB_ATLEAST(LTAGLIB_2_0)
    { "properties", FileRef_properties },
    { "removeUnsupportedProperties", FileRef_removeUnsupportedProperties },
    { "setProperties", FileRef_setProperties },
    { "complexPropertyKeys", FileRef_complexPropertyKeys },
    { "complexProperties", FileRef_complexProperties },
    { "setComplexProperties", FileRef_setComplexProperties },
#endif
    { NULL, NULL }
};

#if LTAGLIB_UNDER(LTAGLIB_2_0)

static int FileRef_static_create(lua_State* L) {
    int args = lua_gettop(L);
    TagLib::File* ptr = NULL;

    switch(args) {
        case 1: {
            ptr = TagLib::FileRef::create(checkstring(L, 1));
            break;
        }
        case 2: {
            ptr = TagLib::FileRef::create(checkstring(L, 1), lua_toboolean(L, 2));
            break;
        }
        case 3: {
            ptr = TagLib::FileRef::create(checkstring(L, 1), lua_toboolean(L, 2),
              AudioProperties::ReadStyle::checkValue(L, 3));
            break;
        }
        default: break;
    }
    lua_pop(L,1);
    if(ptr == NULL) return luaL_error(L, "invalid arguments");

    File::pushPtr(L, ptr);
    return 1;
}
#endif

#if LTAGLIB_ATLEAST(LTAGLIB_1_4)
static int FileRef_static_defaultFileExtensions(lua_State* L) {
    StringList::pushValue(L, TagLib::FileRef::defaultFileExtensions());
    return 1;
}
#endif

static const luaL_Reg FileRef__static[] = {
#if LTAGLIB_ATLEAST(LTAGLIB_1_4)
    { "defaultFileExtensions", FileRef_static_defaultFileExtensions },
#endif
#if LTAGLIB_UNDER(LTAGLIB_2_0)
    { "create", FileRef_static_create },
#endif
    { NULL, NULL }
};

LTAGLIB_PUBLIC int
luaopen_TagLib_FileRef(lua_State* L) {
    return FileRef::open(L);
}

template<>
const UserdataTable FileRef::base::mod = {
    FileRef__call,
    FileRef__static,
    NULL
};

template<>
const UserdataMetatable FileRef::base::metatable = {
    "TagLib::FileRef", /* name */
    FileRef__index, /* indextable */
    NULL, /* indexfunc */
};

#include "shared/userdata.tcc"
template class LuaTagLib::BaseUserdata<TagLib::FileRef>;
