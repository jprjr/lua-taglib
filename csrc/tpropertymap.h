#ifndef LTAGLIB_PROPERTYMAP_INCLUDE_GUARD
#define LTAGLIB_PROPERTYMAP_INCLUDE_GUARD

#include "taglib.h"

#define LTAGLIB_HAS_PROPERTYMAP (LTAGLIB_ATLEAST(LTAGLIB_1_8))

#if LTAGLIB_HAS_PROPERTYMAP

#include "tmap.h"
#include "tstringlist.h"
#include <tpropertymap.h>

namespace LuaTagLib {
    typedef ValueMap<TagLib::PropertyMap, String, StringList> PropertyMap;
}


#endif
#endif
