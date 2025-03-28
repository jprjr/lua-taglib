#ifndef LTAGLIB_FILE_INCLUDE_GUARD
#define LTAGLIB_FILE_INCLUDE_GUARD

#include "taglib.h"
#include "shared/enum.h"
#include "shared/userdata.h"
#include "tiostream.h"
#include "audioproperties.h"

#include <tfile.h>

#define LTAGLIB_HAS_FILE_STRIPTAGS (LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,12,0))
#define LTAGLIB_HAS_FILE_DUPLICATETAGS (LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,12,0))

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_File(lua_State *L);

LTAGLIB_PUBLIC
int luaopen_TagLib_File_Position(lua_State *L);

#if LTAGLIB_HAS_FILE_STRIPTAGS

LTAGLIB_PUBLIC
int luaopen_TagLib_File_StripTags(lua_State *L);

#endif

#if LTAGLIB_HAS_FILE_DUPLICATETAGS

LTAGLIB_PUBLIC
int luaopen_TagLib_File_DuplicateTags(lua_State *L);

#endif

}

namespace LuaTagLib {

    template<> const UserdataMetatable UserdataCommon<TagLib::File>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::File>::mod;

    class LTAGLIB_PRIVATE File: public BaseUserdata<TagLib::File> {
        public:
            typedef Enum<TagLib::File::Position> Position;
            #if LTAGLIB_HAS_FILE_STRIPTAGS
            typedef Enum<TagLib::File::StripTags> StripTags;
            #endif
            #if LTAGLIB_HAS_FILE_DUPLICATETAGS
            typedef Enum<TagLib::File::DuplicateTags> DuplicateTags;
            #endif
    };

    template<typename T>
    int File__call(lua_State* L) {
        int args = lua_gettop(L);
        typename T::taglib_type * f = NULL;
    
        switch(args) {
            case 1: {
#if LTAGLIB_HAS_IOSTREAM
                if(IOStream::isValid(L, 1)) {
                    f = new typename T::taglib_type(IOStream::checkPtr(L, 1));
                    break;
                }
#endif
                f = new typename T::taglib_type(checkstring(L, 1));
                lua_pop(L, 1);
                break;
            }
            case 2: {
#if LTAGLIB_HAS_IOSTREAM
                if(IOStream::isValid(L, 1)) {
                    f = new typename T::taglib_type(IOStream::checkPtr(L, 1), lua_toboolean(L,2));
                    break;
                }
#endif
                f = new typename T::taglib_type(checkstring(L, 1), lua_toboolean(L, 2));
                lua_pop(L, 1);
                break;
            }
            case 3: {
#if LTAGLIB_HAS_IOSTREAM
                if(IOStream::isValid(L, 1)) {
                    f = new typename T::taglib_type(IOStream::checkPtr(L, 1), lua_toboolean(L,2), AudioProperties::ReadStyle::checkValue(L, 3));
                    break;
                }
#endif
                f = new typename T::taglib_type(checkstring(L, 1), lua_toboolean(L, 2), AudioProperties::ReadStyle::checkValue(L, 3));
                lua_pop(L, 1);
                break;
            }
            default: break;
        }
    
        if(f == NULL) return luaL_error(L, "invalid arguments");
        T::pushPtr(L, f);
        return 1;
    }
}

#endif

