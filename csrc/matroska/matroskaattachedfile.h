#ifndef LTAGLIB_MATROSKA_ATTACHEDFILE_INCLUDE_GUARD
#define LTAGLIB_MATROSKA_ATTACHEDFILE_INCLUDE_GUARD

#include "../taglib.h"
#include "../shared/userdata.h"
#include "../tlist.h"
#include <matroskaattachedfile.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_Matroska_AttachedFile(lua_State* L);

}

namespace LuaTagLib {

#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::Matroska::AttachedFile>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::Matroska::AttachedFile>::mod;
#endif 

    namespace Matroska {
        class LTAGLIB_PRIVATE AttachedFile: public BaseUserdata<TagLib::Matroska::AttachedFile> {
            public:
                static TagLib::Matroska::AttachedFile* pushValue(lua_State* L, const TagLib::Matroska::AttachedFile& val) {
                    return UserdataExtra::pushValue<LuaTagLib::Matroska::AttachedFile>(L, val);
                }
        };
    }
}

#endif

