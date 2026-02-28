#ifndef LTAGLIB_PROPERTYMAP_INCLUDE_GUARD
#define LTAGLIB_PROPERTYMAP_INCLUDE_GUARD

#include "taglib.h"

#include "tmap.h"
#include "tstringlist.h"
#include <tpropertymap.h>

namespace LuaTagLib {
    typedef ValueMap<TagLib::PropertyMap, String, StringList> PropertyMap;
}

#endif
