#ifndef LTAGLIB_S3M_INCLUDE_GUARD
#define LTAGLIB_S3M_INCLUDE_GUARD

#include "s3mfile.h"
#include "s3mproperties.h"

#define LTAGLIB_HAS_S3M (LTAGLIB_HAS_S3M_FILE || LTAGLIB_HAS_S3M_PROPERTIES)

#if LTAGLIB_HAS_S3M

extern "C" {

LTAGLIB_PUBLIC
int luaopen_TagLib_S3M(lua_State* L);

}

#endif
#endif
