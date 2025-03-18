#ifndef LTAGLIB_STRINGLIST_INCLUDE_GUARD
#define LTAGLIB_STRINGLIST_INCLUDE_GUARD

#include "tlist.h"
#include "tstring.h"

#include <tstringlist.h>

namespace LuaTagLib {
    typedef ValueList<TagLib::StringList, String> StringList;
}

#endif
