#ifndef LTAGLIB_APE_FOOTER_INCLUDE_GUARD
#define LTAGLIB_APE_FOOTER_INCLUDE_GUARD

#include "../taglib.h"

#define LTAGLIB_HAS_APE_FOOTER (LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,3,0))

#if LTAGLIB_HAS_APE_FOOTER

#include "../shared/userdata.h"
#include <apefooter.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_APE_Footer(lua_State *L);

}

namespace LuaTagLib {

    template<> const UserdataMetatable UserdataCommon<TagLib::APE::Footer>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::APE::Footer>::mod;

    namespace APE {
        typedef BaseUserdata<TagLib::APE::Footer> Footer;
    }
}

#endif

#endif

