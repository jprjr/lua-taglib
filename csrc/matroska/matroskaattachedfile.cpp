#include "matroskaattachedfile.h"

#include "../tstring.h"
#include "../tbytevector.h"

using namespace LuaTagLib;

static int AttachedFile__call(lua_State* L) {
    int args = lua_gettop(L);
    TagLib::Matroska::AttachedFile* a = NULL;

    switch(args) {
        case 1: {
            if(Matroska::AttachedFile::isValid(L, 1)) {
                a = new TagLib::Matroska::AttachedFile(Matroska::AttachedFile::checkValue(L, 1));
                break;
            }
            break;
        }
        case 3: {
            a = new TagLib::Matroska::AttachedFile(
                ByteVector::checkValue(L, 1),
                String::checkValue(L, 2),
                String::checkValue(L, 3)
            );
            break;
        }
        case 4: {
            a = new TagLib::Matroska::AttachedFile(
                ByteVector::checkValue(L, 1),
                String::checkValue(L, 2),
                String::checkValue(L, 3),
                luaL_checkinteger(L, 4)
            );
            break;
        }
        case 5: {
            a = new TagLib::Matroska::AttachedFile(
                ByteVector::checkValue(L, 1),
                String::checkValue(L, 2),
                String::checkValue(L, 3),
                luaL_checkinteger(L, 4),
                String::checkValue(L, 5)
            );
            break;
        }

        default: break;
    }
    if(a == NULL) return luaL_error(L, "invalid arguments");
    Matroska::AttachedFile::pushPtr(L, a);
    return 1;
}

static int AttachedFile_swap(lua_State* L) {
    Matroska::AttachedFile::checkPtr(L, 1)->swap(Matroska::AttachedFile::checkValue(L, 2));
    lua_settop(L, 1);
    return 1;
}

static int AttachedFile_fileName(lua_State* L) {
    String::pushValue(L, Matroska::AttachedFile::checkPtr(L, 1)->fileName());
    return 1;
}

static int AttachedFile_description(lua_State* L) {
    String::pushValue(L, Matroska::AttachedFile::checkPtr(L, 1)->description());
    return 1;
}

static int AttachedFile_mediaType(lua_State* L) {
    String::pushValue(L, Matroska::AttachedFile::checkPtr(L, 1)->mediaType());
    return 1;
}

static int AttachedFile_data(lua_State* L) {
    ByteVector::pushValue(L, Matroska::AttachedFile::checkPtr(L, 1)->data());
    return 1;
}

static int AttachedFile_uid(lua_State* L) {
    lua_pushinteger(L, Matroska::AttachedFile::checkPtr(L, 1)->uid());
    return 1;
}

static
const luaL_Reg AttachedFile__index[] = {
    { "swap", AttachedFile_swap },
    { "fileName", AttachedFile_fileName },
    { "description", AttachedFile_description },
    { "mediaType", AttachedFile_mediaType },
    { "data", AttachedFile_data },
    { "uid", AttachedFile_uid },
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_Matroska_AttachedFile(lua_State *L) {
    return Matroska::AttachedFile::open(L);
}

template<>
const UserdataTable Matroska::AttachedFile::base::mod = {
    AttachedFile__call, /* call */
    NULL, /* __index */
    NULL, /* init */
};

template<>
const UserdataMetatable Matroska::AttachedFile::base::metatable = {
    "TagLib::Matroska::AttachedFile", /* name */
    AttachedFile__index, /* indextable */
    NULL, /* indexfunc */
};


#include "../shared/userdata.tcc"
template class LuaTagLib::BaseUserdata<TagLib::Matroska::AttachedFile>;

