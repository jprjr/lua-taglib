#ifndef LTAGLIB_VARIANT_INCLUDE_GUARD
#define LTAGLIB_VARIANT_INCLUDE_GUARD

#include "taglib.h"

#define LTAGLIB_HAS_VARIANT (LTAGLIB_ATLEAST(LTAGLIB_2_0))

#if LTAGLIB_HAS_VARIANT

#include "tstring.h"
#include "tlist.h"
#include "tmap.h"
#include "shared/enum.h"

#include <tvariant.h>

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_Variant_Type(lua_State* L);

LTAGLIB_PUBLIC
int luaopen_TagLib_Variant(lua_State* L);

}

namespace LuaTagLib {
    class LTAGLIB_PRIVATE Variant {
        public:
            typedef TagLib::Variant taglib_type;
            static TagLib::Variant checkValue(lua_State* L, int idx);
            static void pushValue(lua_State* L, const TagLib::Variant& v);
            typedef Enum<TagLib::Variant::Type> Type;
    };

    typedef ValueList<TagLib::VariantList, Variant> VariantList;

    typedef ValueMap<TagLib::VariantMap, String, Variant> VariantMap;

    typedef ValueList<TagLib::List<TagLib::VariantMap>,VariantMap> VariantMapList;
}

#endif

#endif

