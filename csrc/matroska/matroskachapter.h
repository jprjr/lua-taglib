#ifndef LTAGLIB_MATROSKA_CHAPTER_INCLUDE_GUARD
#define LTAGLIB_MATROSKA_CHAPTER_INCLUDE_GUARD

#include "../taglib.h"

#include "../shared/userdata.h"
#include "../shared/enum.h"
#include "../tlist.h"

#include <matroskachapter.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_Matroska_Chapter(lua_State* L);

LTAGLIB_PUBLIC
int luaopen_TagLib_Matroska_Chapter_Display(lua_State* L);

}

namespace LuaTagLib {

#ifndef _MSC_VER 
    template<> const UserdataMetatable UserdataCommon<TagLib::Matroska::Chapter>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::Matroska::Chapter>::mod;
#endif 

    namespace Matroska {
        class LTAGLIB_PRIVATE Chapter: public BaseUserdata<TagLib::Matroska::Chapter> {
            public:
                static TagLib::Matroska::Chapter* pushValue(lua_State *L, const TagLib::Matroska::Chapter& val) {
                    return UserdataExtra::pushValue<LuaTagLib::Matroska::Chapter>(L,val);
                }

                class LTAGLIB_PRIVATE Display: public BaseUserdata<TagLib::Matroska::Chapter::Display> {
                    public:
                        static TagLib::Matroska::Chapter::Display* pushValue(lua_State *L, const TagLib::Matroska::Chapter::Display& val) {
                            return UserdataExtra::pushValue<LuaTagLib::Matroska::Chapter::Display>(L,val);
                        }

                };
        };
    }
}

#endif

