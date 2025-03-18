#include "oggpageheader.h"

#include "oggfile.h"
#include "../tbytevector.h"
#include "../tlist.h"
#include "../shared/integer.h"

using namespace LuaTagLib;

static int PageHeader__call(lua_State* L) {
    int args = lua_gettop(L);
    TagLib::Ogg::PageHeader* p = NULL;

    switch(args) {
        case 1: {
            p = new TagLib::Ogg::PageHeader(Ogg::File::checkPtr(L, 1));
            break;
        }
        case 2: {
            p = new TagLib::Ogg::PageHeader(Ogg::File::checkPtr(L, 1), luaL_checkinteger(L, 2));
            break;
        }
        default: {
            return luaL_error(L, "invalid arguments");
        }
    }

    if(p == NULL) return luaL_error(L, "invalid arguments");
    Ogg::PageHeader::pushPtr(L, p);
    return 1;
}

static int PageHeader_isValid(lua_State* L) {
    TagLib::Ogg::PageHeader* ph = Ogg::PageHeader::checkPtr(L, 1);
    lua_pushboolean(L, ph->isValid());
    return 1;
}

static int PageHeader_packetSizes(lua_State* L) {
    TagLib::Ogg::PageHeader* ph = Ogg::PageHeader::checkPtr(L, 1);

    ValueList<TagLib::List<int>, Integer>::pushValue(L, ph->packetSizes());
    return 1;
}

static int PageHeader_setPacketSizes(lua_State* L) {
    TagLib::Ogg::PageHeader* ph = Ogg::PageHeader::checkPtr(L, 1);
    ph->setPacketSizes(ValueList<TagLib::List<int>, Integer>::checkValue(L, 2));
    lua_settop(L,1);
    return 1;
}

static int PageHeader_firstPacketContinued(lua_State* L) {
    TagLib::Ogg::PageHeader* ph = Ogg::PageHeader::checkPtr(L, 1);
    lua_pushboolean(L, ph->firstPacketContinued());
    return 1;
}

static int PageHeader_setFirstPacketContinued(lua_State* L) {
    TagLib::Ogg::PageHeader* ph = Ogg::PageHeader::checkPtr(L, 1);
    ph->setFirstPacketContinued(lua_toboolean(L, 2));
    lua_settop(L,1);
    return 1;
}

static int PageHeader_lastPacketCompleted(lua_State* L) {
    TagLib::Ogg::PageHeader* ph = Ogg::PageHeader::checkPtr(L, 1);
    lua_pushboolean(L, ph->lastPacketCompleted());
    return 1;
}

static int PageHeader_setLastPacketCompleted(lua_State* L) {
    TagLib::Ogg::PageHeader* ph = Ogg::PageHeader::checkPtr(L, 1);
    ph->setLastPacketCompleted(lua_toboolean(L, 2));
    lua_settop(L,1);
    return 1;
}

static int PageHeader_firstPageOfStream(lua_State* L) {
    TagLib::Ogg::PageHeader* ph = Ogg::PageHeader::checkPtr(L, 1);
    lua_pushboolean(L, ph->firstPageOfStream());
    return 1;
}

static int PageHeader_setFirstPageOfStream(lua_State* L) {
    TagLib::Ogg::PageHeader* ph = Ogg::PageHeader::checkPtr(L, 1);
    ph->setFirstPageOfStream(lua_toboolean(L, 2));
    lua_settop(L,1);
    return 1;
}

static int PageHeader_lastPageOfStream(lua_State* L) {
    TagLib::Ogg::PageHeader* ph = Ogg::PageHeader::checkPtr(L, 1);
    lua_pushboolean(L, ph->lastPageOfStream());
    return 1;
}

static int PageHeader_setLastPageOfStream(lua_State* L) {
    TagLib::Ogg::PageHeader* ph = Ogg::PageHeader::checkPtr(L, 1);
    ph->setLastPageOfStream(lua_toboolean(L, 2));
    lua_settop(L,1);
    return 1;
}

static int PageHeader_absoluteGranularPosition(lua_State* L) {
    TagLib::Ogg::PageHeader* ph = Ogg::PageHeader::checkPtr(L, 1);
    lua_pushinteger(L, ph->absoluteGranularPosition());
    return 1;
}

static int PageHeader_setAbsoluteGranularPosition(lua_State* L) {
    TagLib::Ogg::PageHeader* ph = Ogg::PageHeader::checkPtr(L, 1);
    ph->setAbsoluteGranularPosition(lua_tointeger(L, 2));
    lua_settop(L,1);
    return 1;
}

static int PageHeader_streamSerialNumber(lua_State* L) {
    TagLib::Ogg::PageHeader* ph = Ogg::PageHeader::checkPtr(L, 1);
    lua_pushinteger(L, ph->streamSerialNumber());
    return 1;
}

static int PageHeader_setStreamSerialNumber(lua_State* L) {
    TagLib::Ogg::PageHeader* ph = Ogg::PageHeader::checkPtr(L, 1);
    ph->setStreamSerialNumber(lua_tointeger(L, 2));
    lua_settop(L,1);
    return 1;
}

static int PageHeader_pageSequenceNumber(lua_State* L) {
    TagLib::Ogg::PageHeader* ph = Ogg::PageHeader::checkPtr(L, 1);
    lua_pushinteger(L, ph->pageSequenceNumber());
    return 1;
}

static int PageHeader_setPageSequenceNumber(lua_State* L) {
    TagLib::Ogg::PageHeader* ph = Ogg::PageHeader::checkPtr(L, 1);
    ph->setPageSequenceNumber(lua_tointeger(L, 2));
    lua_settop(L,1);
    return 1;
}

static int PageHeader_size(lua_State* L) {
    TagLib::Ogg::PageHeader* ph = Ogg::PageHeader::checkPtr(L, 1);
    lua_pushinteger(L, ph->size());
    return 1;
}

static int PageHeader_dataSize(lua_State* L) {
    TagLib::Ogg::PageHeader* ph = Ogg::PageHeader::checkPtr(L, 1);
    lua_pushinteger(L, ph->dataSize());
    return 1;
}

static int PageHeader_render(lua_State* L) {
    TagLib::Ogg::PageHeader* ph = Ogg::PageHeader::checkPtr(L, 1);
    ByteVector::pushValue(L, ph->render());
    return 1;
}

static
const luaL_Reg PageHeader__index[] = {
    { "isValid", PageHeader_isValid },
    { "packetSizes", PageHeader_packetSizes },
    { "setPacketSizes", PageHeader_setPacketSizes },
    { "firstPacketContinued", PageHeader_firstPacketContinued},
    { "setFirstPacketContinued", PageHeader_setFirstPacketContinued},
    { "lastPacketCompleted", PageHeader_lastPacketCompleted},
    { "setLastPacketCompleted", PageHeader_setLastPacketCompleted},
    { "firstPageOfStream", PageHeader_firstPageOfStream},
    { "setFirstPageOfStream", PageHeader_setFirstPageOfStream},
    { "lastPageOfStream", PageHeader_lastPageOfStream},
    { "setLastPageOfStream", PageHeader_setLastPageOfStream},
    { "absoluteGranularPosition", PageHeader_absoluteGranularPosition},
    { "setAbsoluteGranularPosition", PageHeader_setAbsoluteGranularPosition},
    { "streamSerialNumber", PageHeader_streamSerialNumber},
    { "setStreamSerialNumber", PageHeader_setStreamSerialNumber},
    { "pageSequenceNumber", PageHeader_pageSequenceNumber},
    { "setPageSequenceNumber", PageHeader_setPageSequenceNumber},
    { "size", PageHeader_size},
    { "dataSize", PageHeader_dataSize},
    { "render", PageHeader_render},
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_Ogg_PageHeader(lua_State *L) {
    return Ogg::PageHeader::open(L);
}

template<>
const UserdataTable Ogg::PageHeader::base::mod = {
    PageHeader__call,
    NULL,
    NULL
};

template<>
const UserdataMetatable Ogg::PageHeader::base::metatable = {
    "TagLib::Ogg::PageHeader", /* name */
    PageHeader__index, /* indextable */
    NULL, /* indexfunc */
};

#include "../shared/userdata.tcc"
template class BaseUserdata<TagLib::Ogg::PageHeader>;
