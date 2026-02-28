#ifndef LTAGLIB_MATROSKA_CHAPTEREDITION_INCLUDE_GUARD
#define LTAGLIB_MATROSKA_CHAPTEREDITION_INCLUDE_GUARD

#include "../taglib.h"
#include "../shared/userdata.h"
#include <matroskachapteredition.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_Matroska_ChapterEdition(lua_State* L);

}

namespace LuaTagLib {

#ifndef _MSC_VER 
    template<> const UserdataMetatable UserdataCommon<TagLib::Matroska::ChapterEdition>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::Matroska::ChapterEdition>::mod;
#endif 

    namespace Matroska {
        class LTAGLIB_PRIVATE ChapterEdition: public BaseUserdata<TagLib::Matroska::ChapterEdition> {
            public:
                static TagLib::Matroska::ChapterEdition* pushValue(lua_State* L, const TagLib::Matroska::ChapterEdition& val) {
                    return UserdataExtra::pushValue<LuaTagLib::Matroska::ChapterEdition>(L, val);
                }

        };
    }
}

#endif


