#ifndef LTAGLIB_DFDIFF_DIIN_TAG_INCLUDE_GUARD
#define LTAGLIB_DFDIFF_DIIN_TAG_INCLUDE_GUARD

#include "../../taglib.h"

#define LTAGLIB_HAS_DSDIFF_DIIN_TAG (LTAGLIB_ATLEAST(LTAGLIB_2_0))

#if LTAGLIB_HAS_DSDIFF_DIIN_TAG

#include "../../tag.h"
#include "../../shared/userdata.h"

#include <dsdiffdiintag.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_DSDIFF_DIIN_Tag(lua_State *L);

}

namespace LuaTagLib {

#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::DSDIFF::DIIN::Tag>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::DSDIFF::DIIN::Tag>::mod;
#endif 


    namespace DSDIFF { namespace DIIN {
        typedef DerivedUserdata<TagLib::DSDIFF::DIIN::Tag,LuaTagLib::Tag> Tag;
    } }
}


#endif

#endif
