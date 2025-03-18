#include "oggfile.h"

#include "oggpageheader.h"
#include "../tbytevector.h"

using namespace LuaTagLib;

static int File_packet(lua_State* L) {
    TagLib::Ogg::File* ogg = Ogg::File::checkPtr(L, 1);
    ByteVector::pushValue(L,ogg->packet(luaL_checkinteger(L,2)));
    return 1;
}

static int File_setPacket(lua_State* L) {
    TagLib::Ogg::File* ogg = Ogg::File::checkPtr(L, 1);
    ogg->setPacket(luaL_checkinteger(L,2), ByteVector::looseValue(L,3));
    lua_settop(L,1);
    return 1;
}

static int File_firstPageHeader(lua_State* L) {
    TagLib::Ogg::File* ogg = Ogg::File::checkPtr(L, 1);
    Ogg::PageHeader::pushPtr(L, (TagLib::Ogg::PageHeader*) ogg->firstPageHeader(), 1);
    return 1;
}

static int File_lastPageHeader(lua_State* L) {
    TagLib::Ogg::File* ogg = Ogg::File::checkPtr(L, 1);
    Ogg::PageHeader::pushPtr(L, (TagLib::Ogg::PageHeader*) ogg->lastPageHeader(), 1);
    return 1;
}

static
const luaL_Reg File__index[] = {
    { "packet", File_packet},
    { "setPacket", File_setPacket},
    { "firstPageHeader", File_firstPageHeader},
    { "lastPageHeader", File_lastPageHeader},
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_Ogg_File(lua_State* L) {
    return Ogg::File::open(L);
}

template<>
const UserdataTable Ogg::File::base::mod = {
    NULL,
    NULL,
    NULL,
};

template<>
const UserdataMetatable Ogg::File::base::metatable = {
    "TagLib::Ogg::File", /* name */
    File__index, /* indextable */
    NULL, /* indexfunc */
};

#include "../shared/userdata.tcc"
template class DerivedUserdata<TagLib::Ogg::File, LuaTagLib::File>;
