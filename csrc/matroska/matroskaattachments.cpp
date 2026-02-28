#include "matroskaattachments.h"
#include "matroskaattachedfile.h"

using namespace LuaTagLib;

static int Attachments__call(lua_State* L) {
    int args = lua_gettop(L);
    TagLib::Matroska::Attachments* c = NULL;

    switch(args) {
        case 0: {
            c = new TagLib::Matroska::Attachments();
            break;
        }
        default: break;
    }
    if(c == NULL) return luaL_error(L, "invalid arguments");

    Matroska::Attachments::pushPtr(L, c);
    return 1;
}

static int Attachments_addAttachedFile(lua_State* L) {
    Matroska::Attachments::checkPtr(L,1)->addAttachedFile(
      Matroska::AttachedFile::checkValue(L,2)
    );
    lua_settop(L,1);
    return 1;
}

static int Attachments_removeAttachedFile(lua_State* L) {
    Matroska::Attachments::checkPtr(L,1)->removeAttachedFile(
      luaL_checkinteger(L, 2)
    );
    lua_settop(L,1);
    return 1;
}

static int Attachments_clear(lua_State* L) {
    Matroska::Attachments::checkPtr(L,1)->clear();
    lua_settop(L,1);
    return 1;
}

static int Attachments_attachedFileList(lua_State* L) {
    ConstValueListReference<TagLib::Matroska::Attachments::AttachedFileList,Matroska::AttachedFile>::pushRef(L,
      Matroska::Attachments::checkPtr(L,1)->attachedFileList(),
      1
    );
    return 1;
}

static
const luaL_Reg Attachments__index[] = {
    { "clear", Attachments_clear },
    { "addAttachedFile", Attachments_addAttachedFile },
    { "removeAttachedFile", Attachments_removeAttachedFile },
    { "attachedFileList", Attachments_attachedFileList },
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_Matroska_Attachments(lua_State *L) {
    return Matroska::Attachments::open(L);
}

template<>
const UserdataTable Matroska::Attachments::base::mod = {
    Attachments__call, /* call */
    NULL, /* __index */
    NULL, /* init */
};

template<>
const UserdataMetatable Matroska::Attachments::base::metatable = {
    "TagLib::Matroska::Attachments", /* name */
    Attachments__index, /* indextable */
    NULL, /* indexfunc */
};

#include "../shared/userdata.tcc"
template class LuaTagLib::BaseUserdata<TagLib::Matroska::Attachments>;

template<>
const char* ConstValueListReference<TagLib::Matroska::Attachments::AttachedFileList,Matroska::AttachedFile>::base::__name = "TagLib::Matroska::AttachedFileList";
