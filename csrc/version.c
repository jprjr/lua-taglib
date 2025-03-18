#include "version.h"

LTAGLIB_PUBLIC
int luaopen_TagLib__VERSION(lua_State* L) {
    lua_pushliteral(L, LTAGLIB_LIBRARY_VERSION);
    return 1;
}
