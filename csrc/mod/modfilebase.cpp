#include "modfilebase.h"

#if LTAGLIB_HAS_MOD_FILEBASE
using namespace LuaTagLib;

/* ensures we create an empty __index metatable for
 * child types to use */
static const luaL_Reg FileBase__index[] = {
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_Mod_FileBase(lua_State *L) {
    return Mod::FileBase::open(L);
}

template<>
const UserdataTable Mod::FileBase::base::mod = {
    NULL,
    NULL,
    NULL
};

template<>
const UserdataMetatable Mod::FileBase::base::metatable = {
    "TagLib::Mod::FileBase", /* name */
    FileBase__index, /* indextable */
    NULL, /* indexfunc */
};

#include "../shared/userdata.tcc"
template class LuaTagLib::DerivedUserdata<TagLib::Mod::FileBase, LuaTagLib::File>;

#endif

