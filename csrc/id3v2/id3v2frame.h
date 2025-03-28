#ifndef LTAGLIB_ID3V2_FRAME_INCLUDE_GUARD
#define LTAGLIB_ID3V2_FRAME_INCLUDE_GUARD

#include "../taglib.h"
#include "../shared/userdata.h"
#include <id3v2frame.h>

#define LTAGLIB_HAS_ID3V2_FRAME_HEADER LTAGLIB_ATLEAST(LTAGLIB_2_0)

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_Frame(lua_State* L);

#if LTAGLIB_HAS_ID3V2_FRAME_HEADER
LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_Frame_Header(lua_State* L);
#endif

}

namespace LuaTagLib { 

#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::ID3v2::Frame>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::ID3v2::Frame>::mod;
#endif 


    namespace ID3v2 {

    class LTAGLIB_PRIVATE Frame: public BaseUserdata<TagLib::ID3v2::Frame> {
        public:
            /* when ID3v2::Tag adds a frame, it takes over memory
             * management. This recurses its way up to the first managed frame,
             * and marks it as unmanaged.
             *
             * It may be possible to add a frame that's already managed by TagLib?
             * I'm not sure, so I use optInstance and if it's null, stop.
             *
             * TODO is it possible to add a frame already managed by TagLib or
             * is that an error?
             */
            static void unmanageRefs(lua_State* L, int idx) {
                int i;
                UserdataPointer<TagLib::ID3v2::Frame>* f = Frame::optInstance(L, idx);
                if(f == NULL) return;
                if(f->isManaged()) {
                    /* we've found our managed, parent frame - stop searching */
                    f->unmanage();
                    return;
                }

                getreferencetable(L, idx);
                for(i=1; ;++i) {
                    lua_rawgeti(L, -1, i);
                    if(lua_isnil(L, -1)) break;
                    unmanageRefs(L, lua_gettop(L));
                    lua_pop(L, 1);
                    luaL_unref(L, -1, i);
                }
                lua_pop(L, 2);
            }

            /* used to unmanageRefs for a table (list) of frames */
            static void unmanageListRefs(lua_State* L, int idx) {
                int i;
                int tidx = lua_gettop(L) + 1;

                for(i=1; ;++i) {
                    lua_rawgeti(L, idx, i);
                    if(lua_isnil(L, tidx)) break;
                    unmanageRefs(L, tidx);
                    lua_pop(L, 1);
                }
                lua_pop(L, 1);
            }
#if LTAGLIB_HAS_ID3V2_FRAME_HEADER
            class LTAGLIB_PRIVATE Header: public BaseUserdata<TagLib::ID3v2::Frame::Header> {
            };
#endif
    };

} }


#endif
