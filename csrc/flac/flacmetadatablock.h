#ifndef LTAGLIB_FLAC_METADATABLOCK_INCLUDE_GUARD
#define LTAGLIB_FLAC_METADATABLOCK_INCLUDE_GUARD

#include "../taglib.h"

#define LTAGLIB_HAS_FLAC_METADATABLOCK (LTAGLIB_ATLEAST(LTAGLIB_1_7))

#if LTAGLIB_HAS_FLAC_METADATABLOCK

#include "../shared/userdata.h"
#include "../shared/enum.h"
#include <flacmetadatablock.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_FLAC_MetadataBlock(lua_State *L);

LTAGLIB_PUBLIC
int luaopen_TagLib_FLAC_MetadataBlock_BlockType(lua_State *L);

}


namespace LuaTagLib {

#ifndef _MSC_VER 

    template<> const UserdataMetatable UserdataCommon<TagLib::FLAC::MetadataBlock>::metatable;
    template<> const UserdataTable     UserdataCommon<TagLib::FLAC::MetadataBlock>::mod;
#endif 


    namespace FLAC {
    class LTAGLIB_PRIVATE MetadataBlock: public BaseUserdata<TagLib::FLAC::MetadataBlock> {
        public:
            typedef Enum<TagLib::FLAC::MetadataBlock::BlockType> BlockType;
    };
} }

#endif

#endif
