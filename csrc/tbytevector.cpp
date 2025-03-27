#include "tbytevector.h"

using namespace LuaTagLib;

bool ByteVector::isValidish(lua_State* L, int idx) {
    return isstring(L, idx) || isValid(L, idx);
}

TagLib::ByteVector ByteVector::looseValue(lua_State* L, int idx) {
    TagLib::ByteVector tmp;
    const char* str_tmp;
    std::size_t str_len;

    const TagLib::ByteVector* t = ByteVector::optPtr(L, idx);
    if(t != NULL) return *t;

    str_tmp = checklstring(L, idx, &str_len);
    tmp = TagLib::ByteVector(str_tmp, str_len);
    lua_pop(L, 1);

    return tmp;

}

static int ByteVector__index(lua_State* L) {
    const TagLib::ByteVector* b = ByteVector::checkPtr(L, 1);

    if(lua_isinteger(L, 2)) {
        lua_Integer idx = lua_tointeger(L, 2);
        char val;
        if(idx < 0 || ((std::size_t)idx) > b->size()) {
            return luaL_error(L, "index %d out of range", idx);
        }
        --idx;
        val = b->at(idx);
        lua_pushlstring(L, &val, 1);
        return 1;
    }

    return 0;
}

static int ByteVector__tostring(lua_State* L) {
    const TagLib::ByteVector* b = ByteVector::checkPtr(L, 1);
    lua_pushlstring(L, b->data(), b->size());
    return 1;
}

static int ByteVector__len(lua_State* L) {
    lua_pushinteger(L,
      ByteVector::checkPtr(L, 1)->size()
    );
    return 1;
}

static int ByteVector__concat(lua_State* L) {
    TagLib::ByteVector a;
    TagLib::ByteVector b;

    a = ByteVector::looseValue(L, 1);
    b = ByteVector::looseValue(L, 2);

    ByteVector::pushPtr(L, new TagLib::ByteVector(a + b));
    return 1;
}

static int ByteVector__eq(lua_State* L) {
    TagLib::ByteVector a;
    TagLib::ByteVector b;

    a = ByteVector::looseValue(L, 1);
    b = ByteVector::looseValue(L, 2);

    lua_pushboolean(L, a == b);
    return 1;
}

static int ByteVector__lt(lua_State* L) {
    TagLib::ByteVector a;
    TagLib::ByteVector b;

    a = ByteVector::looseValue(L, 1);
    b = ByteVector::looseValue(L, 2);

    lua_pushboolean(L, a < b);
    return 1;
}

static int ByteVector__le(lua_State* L) {
    TagLib::ByteVector a;
    TagLib::ByteVector b;

    a = ByteVector::looseValue(L, 1);
    b = ByteVector::looseValue(L, 2);

    lua_pushboolean(L, a < b || a == b);
    return 1;
}

static const luaL_Reg __metatable[] = {
    { "__le", ByteVector__le },
    { "__lt", ByteVector__lt },
    { "__eq", ByteVector__eq },
    { "__concat", ByteVector__concat },
    { "__len", ByteVector__len },
    { "__tostring", ByteVector__tostring },
    { NULL, NULL }
};

static int ByteVector__createmeta(lua_State* L) {
    luaL_setfuncs(L, __metatable, 0);

    lua_newtable(L);
    lua_pushcclosure(L, ByteVector__index, 0);
    lua_setfield(L, -2, "__index");
    return 0;
}


static int ByteVector__call(lua_State* L) {
    const char* str_tmp;
    std::size_t str_len;
    const TagLib::ByteVector* t = ByteVector::optPtr(L, 1);
    TagLib::ByteVector* b = NULL;

    if(t) {
        b = new TagLib::ByteVector(*t);
    } else {
        str_tmp = checklstring(L, 1, &str_len);
        b = new TagLib::ByteVector(str_tmp,str_len);
        lua_pop(L, 1);
    }
    ByteVector::pushPtr(L, b);
    return 1;
}

template<>
const UserdataTable ByteVector::base::mod = {
    ByteVector__call,
    NULL,
    NULL,
};

template<>
const UserdataMetatable ByteVector::base::metatable = {
    "TagLib::ByteVector",
    NULL, /* indextable */
    ByteVector__createmeta,
};

LTAGLIB_PUBLIC
int luaopen_TagLib_ByteVector(lua_State* L) {
    return ByteVector::open(L);
}

#include "shared/userdata.tcc"
template class LuaTagLib::BaseUserdata<TagLib::ByteVector>;
