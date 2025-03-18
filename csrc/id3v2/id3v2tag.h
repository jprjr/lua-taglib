#ifndef LTAGLIB_ID3V2_TAG_INCLUDE_GUARD
#define LTAGLIB_ID3V2_TAG_INCLUDE_GUARD

#include "../shared/userdata.h"
#include "../tag.h"
#include "../tlist.h"
#include "../tmap.h"
#include "../tbytevector.h"

#include "id3v2frame.h"

#include <id3v2tag.h>

extern "C" {

    LTAGLIB_PUBLIC int
    luaopen_TagLib_ID3v2_Tag(lua_State* L);

}

namespace LuaTagLib { namespace ID3v2 {
    typedef DerivedUserdata<TagLib::ID3v2::Tag,LuaTagLib::Tag> Tag;

    typedef ConstPtrListReference<TagLib::ID3v2::FrameList,ID3v2::Frame> FrameList;

    class LTAGLIB_PRIVATE FrameListMapImpl {
        public:
            typedef TagLib::ID3v2::FrameListMap taglib_type;
            typedef ByteVector Key;
            class LTAGLIB_PRIVATE Value {
                public:
                    typedef TagLib::ID3v2::FrameList taglib_type;
                    static void push(lua_State* L, const taglib_type& list, int parent) {
                        PtrList<TagLib::ID3v2::FrameList, ID3v2::Frame>::pushPtr(L, list, parent);
                    }
            };
    };
    typedef ConstImplMapReference<TagLib::ID3v2::FrameListMap, FrameListMapImpl> FrameListMap;
} }

#endif

