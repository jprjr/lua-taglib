#ifndef LTAGLIB_MPC_FILE_INCLUDE_GUARD
#define LTAGLIB_MPC_FILE_INCLUDE_GUARD

#include "../taglib.h"

#define LTAGLIB_HAS_MPC_FILE (LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,3,0))

#if LTAGLIB_HAS_MPC_FILE

#include "../tfile.h"
#include "../shared/userdata.h"
#include <mpcfile.h>


extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_MPC_File(lua_State *L);

LTAGLIB_PUBLIC
int luaopen_TagLib_MPC_File_TagTypes(lua_State *L);

}

namespace LuaTagLib {

    template<> const UserdataMetatable UserdataCommon<TagLib::MPC::File>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::MPC::File>::mod;

    namespace MPC {
        typedef DerivedUserdata<TagLib::MPC::File, LuaTagLib::File> File;
    }
}

#endif

#endif
