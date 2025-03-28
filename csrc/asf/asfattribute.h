#ifndef LTAGLIB_ASF_ATTRIBUTE_INCLUDE_GUARD
#define LTAGLIB_ASF_ATTRIBUTE_INCLUDE_GUARD

#include "asf.h"

#if LTAGLIB_HAS_ASF

#include "../shared/userdata.h"
#include "../shared/enum.h"

#include <asfattribute.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_ASF_Attribute(lua_State *L);

LTAGLIB_PUBLIC
int luaopen_TagLib_ASF_Attribute_AttributeTypes(lua_State *L);

}

namespace LuaTagLib {

#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::ASF::Attribute>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::ASF::Attribute>::mod;
#endif 


    namespace ASF {
        class LTAGLIB_PRIVATE Attribute: public BaseUserdata<TagLib::ASF::Attribute> {
            public:
                typedef Enum<TagLib::ASF::Attribute::AttributeTypes> AttributeTypes;
        };
    }
}

#endif

#endif

