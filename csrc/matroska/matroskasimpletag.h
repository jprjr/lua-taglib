#ifndef LTAGLIB_MATROSKA_SIMPLETAG_INCLUDE_GUARD
#define LTAGLIB_MATROSKA_SIMPLETAG_INCLUDE_GUARD

#include "../taglib.h"

#include "../shared/userdata.h"
#include "../shared/enum.h"
#include "../tlist.h"

#include <matroskasimpletag.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_Matroska_SimpleTag(lua_State* L);

LTAGLIB_PUBLIC
int luaopen_TagLib_Matroska_SimpleTag_TargetTypeValue(lua_State* L);

LTAGLIB_PUBLIC
int luaopen_TagLib_Matroska_SimpleTag_ValueType(lua_State* L);

}

namespace LuaTagLib {

#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::Matroska::SimpleTag>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::Matroska::SimpleTag>::mod;
#endif 

    namespace Matroska {
    class LTAGLIB_PRIVATE SimpleTag: public BaseUserdata<TagLib::Matroska::SimpleTag> {
        public:
            typedef Enum<TagLib::Matroska::SimpleTag::ValueType> ValueType;
            typedef Enum<TagLib::Matroska::SimpleTag::TargetTypeValue> TargetTypeValue;

            static TagLib::Matroska::SimpleTag* pushValue(lua_State* L, const TagLib::Matroska::SimpleTag& val) {
                return UserdataExtra::pushValue<LuaTagLib::Matroska::SimpleTag>(L, val);
            }
    };
    }
}

#endif
