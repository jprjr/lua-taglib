#ifndef LTAGLIB_ASF_PICTURE_INCLUDE_GUARD
#define LTAGLIB_ASF_PICTURE_INCLUDE_GUARD

#include "asf.h"

#define LTAGLIB_HAS_ASF_PICTURE (LTAGLIB_HAS_ASF && LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,7,0))

#if LTAGLIB_HAS_ASF_PICTURE

#include "../shared/userdata.h"
#include "../shared/enum.h"
#include <asfpicture.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_ASF_Picture(lua_State *L);

LTAGLIB_PUBLIC
int luaopen_TagLib_ASF_Picture_Type(lua_State *L);

}

namespace LuaTagLib {

#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::ASF::Picture>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::ASF::Picture>::mod;
#endif 


    namespace ASF {
        class LTAGLIB_PRIVATE Picture: public BaseUserdata<TagLib::ASF::Picture> {
            public:
                typedef Enum<TagLib::ASF::Picture::Type> Type;
        };
    }
}

#endif

#endif
