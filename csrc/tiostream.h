#ifndef LTAGLIB_IOSTREAM_INCLUDE_GUARD
#define LTAGLIB_IOSTREAM_INCLUDE_GUARD

#include "taglib.h"

#define LTAGLIB_HAS_IOSTREAM (LTAGLIB_ATLEAST(LTAGLIB_1_8))

#if LTAGLIB_HAS_IOSTREAM

#include "shared/userdata.h"
#include "shared/enum.h"
#include <tiostream.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_IOStream(lua_State* L);

LTAGLIB_PUBLIC
int luaopen_TagLib_IOStream_Position(lua_State* L);

}



namespace LuaTagLib {
    class LTAGLIB_PRIVATE LuaIOStream: public TagLib::IOStream {
        public:
#if LTAGLIB_UNDER(LTAGLIB_2_0)
            typedef unsigned long lt_size;
            typedef unsigned long lt_uoffset;
            typedef long lt_offset;
#else
            typedef size_t lt_size;
            typedef TagLib::offset_t lt_uoffset;
            typedef TagLib::offset_t lt_offset;
#endif

            LuaIOStream(lua_State* L)
            : L(L) { };

            ~LuaIOStream() { };

            TagLib::FileName name() const LTAGLIB_OVERRIDE;
            TagLib::ByteVector readBlock(lt_size length) LTAGLIB_OVERRIDE;
            void writeBlock(const TagLib::ByteVector& data) LTAGLIB_OVERRIDE;
            void insert(const TagLib::ByteVector& data, lt_uoffset start, lt_size replace) LTAGLIB_OVERRIDE;
            void removeBlock(lt_uoffset start, lt_size len) LTAGLIB_OVERRIDE;
            bool readOnly() const LTAGLIB_OVERRIDE;
            bool isOpen() const LTAGLIB_OVERRIDE;
            void seek(lt_offset off, TagLib::IOStream::Position pos) LTAGLIB_OVERRIDE;
            void clear() LTAGLIB_OVERRIDE;
            lt_offset tell() const LTAGLIB_OVERRIDE;
            lt_offset length() LTAGLIB_OVERRIDE;
            void truncate(lt_offset len) LTAGLIB_OVERRIDE;

            lua_State* L;
        private:
            void loadUserdata() const;
    };

    class LTAGLIB_PRIVATE IOStream: public BaseUserdata<TagLib::IOStream> {
        public:
            typedef Enum<TagLib::IOStream::Position> Position;
    };


}

#endif

#endif
