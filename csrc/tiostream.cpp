#include "tiostream.h"

#if LTAGLIB_HAS_IOSTREAM

#include "tbytevector.h"

using namespace LuaTagLib;

static
const void* getWeakRefKey(void) {
    static char key;
    return &key;
}

static
int getWeakRefTable(lua_State* L) {
    int created = getsubtable(L, LUA_REGISTRYINDEX, getWeakRefKey());
    if(created) {
        lua_newtable(L);
        lua_pushstring(L, "v");
        lua_setfield(L, -2, "__mode");
        lua_setmetatable(L, -2);
    }
    return created;
}

static
const void* getUserdataRefKey(void) {
    static char key;
    return &key;
}

static
const void* getStringKey(void) {
    static char key;
    return &key;
}

static int IOStream__call(lua_State* L) {
    LuaIOStream* l = NULL;
    int args = lua_gettop(L);

    switch(args) {
        case 1: {
            l = new LuaIOStream(L);
            break;
        }
        default: break;
    }

    if(l == NULL) return luaL_error(L, "invalid arguments");

    IOStream::pushPtr(L, l);

    /* save a strong reference to our user-provided object with our userdata */
    lua_pushvalue(L, 1);
    addkeyreference(L, -2, getUserdataRefKey());

    /* save a weak reference to our userdata
     * in the registry index */
    getWeakRefTable(L);
    lua_pushvalue(L, -2);
    lua_rawsetp(L, -2, l);
    lua_pop(L, 1);

    return 1;
}

static int IOStream_name(lua_State* L) {
    TagLib::IOStream* l = IOStream::checkPtr(L, 1);
#ifdef _WIN32
    String::pushValue(L, l->name().toString());
#else
    lua_pushstring(L, l->name());
#endif
    return 1;
}

static int IOStream_readBlock(lua_State* L) {
    TagLib::IOStream* l = IOStream::checkPtr(L, 1);
    ByteVector::pushValue(L, l->readBlock(luaL_checkinteger(L, 2)));
    return 1;
}

static int IOStream_writeBlock(lua_State* L) {
    TagLib::IOStream* l = IOStream::checkPtr(L, 1);
    l->writeBlock(ByteVector::checkValue(L,2));
    lua_settop(L,1);
    return 1;
}

static int IOStream_insert(lua_State* L) {
    TagLib::IOStream* l = IOStream::checkPtr(L, 1);
    l->insert(ByteVector::checkValue(L, 2), luaL_checkinteger(L, 3), luaL_checkinteger(L, 4));
    lua_settop(L,1);
    return 1;
}

static int IOStream_removeBlock(lua_State* L) {
    TagLib::IOStream* l = IOStream::checkPtr(L, 1);

    l->removeBlock(luaL_checkinteger(L, 2), luaL_checkinteger(L, 3));
    lua_settop(L, 1);
    return 1;
}

static int IOStream_readOnly(lua_State* L) {
    TagLib::IOStream* l = IOStream::checkPtr(L, 1);

    lua_pushboolean(L, l->readOnly());
    return 1;
}

static int IOStream_isOpen(lua_State* L) {
    TagLib::IOStream* l = IOStream::checkPtr(L, 1);

    lua_pushboolean(L, l->isOpen());
    return 1;
}

static int IOStream_seek(lua_State* L) {
    TagLib::IOStream* l = IOStream::checkPtr(L, 1);

    l->seek(luaL_checkinteger(L, 2), IOStream::Position::checkValue(L, 3));

    lua_settop(L, 1);
    return 1;
}

static int IOStream_clear(lua_State* L) {
    IOStream::checkPtr(L, 1)->clear();

    lua_settop(L, 1);
    return 1;
}

static int IOStream_tell(lua_State* L) {
    TagLib::IOStream* l = IOStream::checkPtr(L, 1);

    lua_pushinteger(L, l->tell());
    return 1;
}

static int IOStream_length(lua_State* L) {
    TagLib::IOStream* l = IOStream::checkPtr(L, 1);

    lua_pushinteger(L, l->length());
    return 1;
}

static int IOStream_truncate(lua_State* L) {
    TagLib::IOStream* l = IOStream::checkPtr(L, 1);

    l->truncate(luaL_checkinteger(L,2));

    lua_settop(L, 1);
    return 1;
}

static const luaL_Reg IOStream__index[] = {
    { "name", IOStream_name },
    { "readBlock", IOStream_readBlock },
    { "writeBlock", IOStream_writeBlock },
    { "insert", IOStream_insert },
    { "removeBlock", IOStream_removeBlock },
    { "readOnly", IOStream_readOnly },
    { "isOpen", IOStream_isOpen },
    { "seek", IOStream_seek },
    { "clear", IOStream_clear },
    { "tell", IOStream_tell },
    { "length", IOStream_length },
    { "truncate", IOStream_truncate },
    { NULL, NULL }
};

static int IOStream__submodules(lua_State* L) {
    luaL_requiref(L, "TagLib.IOStream.Position", luaopen_TagLib_IOStream_Position, 0);
    lua_setfield(L, -2, "Position");
    return 0;
}

template<>
const UserdataTable IOStream::base::mod = {
    IOStream__call,
    NULL,
    IOStream__submodules,
};

template<>
const UserdataMetatable IOStream::base::metatable = {
    "TagLib::IOStream",
    IOStream__index,
    NULL
};

#define E(x) { #x, sizeof(#x) - 1, TagLib::IOStream::x }
static const IOStream::Position::enum_type iostreamPositions[] = {
    E(Beginning), E(Current), E(End)
};

template<>
const IOStream::Position::enum_type* IOStream::Position::m_values = iostreamPositions;

template<>
const size_t IOStream::Position::m_len = sizeof(iostreamPositions) / sizeof(iostreamPositions[0]);

LTAGLIB_PUBLIC
int luaopen_TagLib_IOStream_Position(lua_State* L) {
    return IOStream::Position::open(L);
}

LTAGLIB_PUBLIC
int luaopen_TagLib_IOStream(lua_State* L) {
    return IOStream::open(L);
}

namespace LuaTagLib {
    void LuaIOStream::loadUserdata() const {
        getWeakRefTable(L);
        lua_rawgetp(L, -1, this); /* stack is now weakRefTable, and our userdata */
        lua_remove(L, -2); /* now it's just our userdata */
        getkeyreference(L, -1, getUserdataRefKey());
          /* stack is now:
           *   our userdata (-2)
           *   their userdata (-1) */
    }

    TagLib::FileName LuaIOStream::name() const {
        const char* str_data;

        loadUserdata();

        lua_getfield(L, -1, "name");
        lua_insert(L, -2); /* (our userdata), name function, (their userdata) */
        lua_call(L, 1, 1); /* (our userdata), (some value) */

        str_data = checkstring(L, -1);
        /* stack is now (our userdata), (some value), string */
        /* want to save our string as a reference to our userdata's uservalue to prevent
         * garbage-collection */
        addkeyreference(L, -3, getStringKey());

        lua_pop(L, 2);
        return str_data;
    }

    TagLib::ByteVector LuaIOStream::readBlock(size_t length) {
        size_t str_len;
        const char* str_data;
        TagLib::ByteVector b;

        loadUserdata(); /* +2 values */

        lua_getfield(L, -1, "readBlock"); /* +1 */
        lua_insert(L, -2);

        lua_pushinteger(L, length); /* +1 */
        lua_call(L, 2, 1);

        str_data = checklstring(L, -1, &str_len); /* +1 */
        b = TagLib::ByteVector(str_data,str_len);
        lua_pop(L, 3);

        return b;
    }

    void LuaIOStream::writeBlock(const TagLib::ByteVector& data) {
        loadUserdata(); /* +2 */

        lua_getfield(L, -1, "writeBlock"); /* +1 */
        lua_insert(L, -2);

        lua_pushlstring(L, data.data(), data.size()); /* +1 */

        lua_call(L, 2, 0); /* -3, +0 */
        lua_pop(L, 1);
    }

    void LuaIOStream::insert(const TagLib::ByteVector& data, lt_uoffset off, lt_size replace) {
        loadUserdata(); /* +2 */

        lua_getfield(L, -1, "writeBlock"); /* +1 */
        lua_insert(L, -2);

        lua_pushlstring(L, data.data(), data.size());
        lua_pushinteger(L, off);
        lua_pushinteger(L, replace);

        lua_call(L, 4, 0);
        lua_pop(L, 1);
    }

    void LuaIOStream::removeBlock(lt_uoffset off, lt_size len) {
        loadUserdata(); /* +2 */

        lua_getfield(L, -1, "removeBlock");
        lua_insert(L, -2);

        lua_pushinteger(L, off);
        lua_pushinteger(L, len);

        lua_call(L, 3, 0);
        lua_pop(L, 1);
    }

    bool LuaIOStream::readOnly() const {
        loadUserdata(); /* +2 */

        lua_getfield(L, -1, "readOnly");
        lua_insert(L, -2);

        lua_call(L, 1, 1);
        bool isReadOnly = lua_toboolean(L, -1);
        lua_pop(L, 2);
        return isReadOnly;
    }

    bool LuaIOStream::isOpen() const {
        loadUserdata(); /* +2 */

        lua_getfield(L, -1, "isOpen");
        lua_insert(L, -2);

        lua_call(L, 1, 1);
        bool o = lua_toboolean(L, -1);
        lua_pop(L, 2);
        return o;
    }

    void LuaIOStream::seek(lt_offset off, TagLib::IOStream::Position pos) {
        loadUserdata();

        lua_getfield(L, -1, "seek");
        lua_insert(L, -2);

        lua_pushinteger(L, off);
        LuaTagLib::IOStream::Position::pushValue(L, pos);

        lua_call(L, 3, 0);
        lua_pop(L, 1);
    }

    void LuaIOStream::clear() {
        loadUserdata();

        lua_getfield(L, -1, "clear");
        lua_insert(L, -2);

        lua_call(L, 1, 0);
        lua_pop(L, 1);
    }

    LuaIOStream::lt_offset LuaIOStream::tell() const {
        loadUserdata(); /* +2 */

        lua_getfield(L, -1, "tell");
        lua_insert(L, -2);

        lua_call(L, 1, 1);
        lt_offset t = luaL_checkinteger(L, -1);
        lua_pop(L, 2);
        return t;
    }

    LuaIOStream::lt_offset LuaIOStream::length() {
        loadUserdata(); /* +2 */

        lua_getfield(L, -1, "length");
        lua_insert(L, -2);

        lua_call(L, 1, 1);
        lt_offset t = luaL_checkinteger(L, -1);
        lua_pop(L, 2);
        return t;
    }

    void LuaIOStream::truncate(lt_offset len) {
        loadUserdata(); /* +2 */

        lua_getfield(L, -1, "truncate");
        lua_insert(L, -2);

        lua_pushinteger(L, len);

        lua_call(L, 2, 0);
        lua_pop(L, 1);
    }

}

#include "shared/enum.tcc"
template class LuaTagLib::Enum<TagLib::IOStream::Position>;

#include "shared/userdata.tcc"
template class LuaTagLib::BaseUserdata<TagLib::IOStream>;

#endif
