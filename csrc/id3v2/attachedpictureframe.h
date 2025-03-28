#ifndef LTAGLIB_ID3V2_ATTACHEDPICTUREFRAME_INCLUDE_GUARD
#define LTAGLIB_ID3V2_ATTACHEDPICTUREFRAME_INCLUDE_GUARD

#include "../taglib.h"

#define LTAGLIB_HAS_ATTACHEDPICTUREFRAME (LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,2,0))

#if LTAGLIB_HAS_ATTACHEDPICTUREFRAME

#include "id3v2frame.h"
#include "../shared/enum.h"
#include <attachedpictureframe.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_AttachedPictureFrame(lua_State* L);

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_AttachedPictureFrame_Type(lua_State* L);

}

namespace LuaTagLib {
#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::ID3v2::AttachedPictureFrame>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::ID3v2::AttachedPictureFrame>::mod;
#endif 

    namespace ID3v2 {
    class LTAGLIB_PRIVATE AttachedPictureFrame: public DerivedUserdata<TagLib::ID3v2::AttachedPictureFrame, Frame> {
        public:
            typedef Enum<TagLib::ID3v2::AttachedPictureFrame::Type> Type;
    };
} }

#endif

#endif
