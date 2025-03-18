#include "oggpage.h"

#include "../tbytevector.h"
#include "../tbytevectorlist.h"
#include "oggpageheader.h"
#include "oggfile.h"

using namespace LuaTagLib;

static int Page__call(lua_State* L) {
    int args = lua_gettop(L);
    TagLib::Ogg::Page* p = NULL;

    switch(args) {
        case 2: {
            p = new TagLib::Ogg::Page(Ogg::File::checkPtr(L, 2), luaL_checkinteger(L, 3));
            break;
        }
        default: break;
    }

    if(p == NULL) return luaL_error(L, "invalid arguments");
    Ogg::Page::pushPtr(L, p);
    return 1;
}

static int Page_fileOffset(lua_State* L) {
    TagLib::Ogg::Page* p = Ogg::Page::checkPtr(L, 1);
    lua_pushinteger(L, p->fileOffset());
    return 1;
}

static int Page_header(lua_State* L) {
    TagLib::Ogg::Page* p = Ogg::Page::checkPtr(L, 1);
    Ogg::PageHeader::pushPtr(L, (TagLib::Ogg::PageHeader*) p->header(), 1);
    return 1;
}

#if LTAGLIB_ATLEAST(LTAGLIB_1_6) && LTAGLIB_UNDER(LTAGLIB_1_12)
static int Page_getCopyWithNewPageSequenceNumber(lua_State* L) {
    TagLib::Ogg::Page* p = Ogg::Page::checkPtr(L, 1);
    Ogg::Page::pushPtr(L, p->getCopyWithNewPageSequenceNumber(luaL_checkinteger(L,2)), 0);
    Ogg::Page::checkInstance(L, -1)->setDelete();
    return 1;
}
#endif

static int Page_firstPacketIndex(lua_State* L) {
    TagLib::Ogg::Page* p = Ogg::Page::checkPtr(L, 1);
    lua_pushinteger(L, p->firstPacketIndex());
    return 1;
}

static int Page_setFirstPacketIndex(lua_State* L) {
    TagLib::Ogg::Page* p = Ogg::Page::checkPtr(L, 1);
    p->setFirstPacketIndex(lua_tointeger(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Page_containsPacket(lua_State* L) {
    TagLib::Ogg::Page* p = Ogg::Page::checkPtr(L, 1);
    Ogg::Page::ContainsPacketFlags::pushValue(L, p->containsPacket(lua_tointeger(L, 2)));
    return 1;
}

static int Page_packetCount(lua_State* L) {
    TagLib::Ogg::Page* p = Ogg::Page::checkPtr(L, 1);
    lua_pushinteger(L, p->packetCount());
    return 1;
}

static int Page_packets(lua_State* L) {
    TagLib::Ogg::Page* p = Ogg::Page::checkPtr(L, 1);
    ByteVectorList::pushValue(L, p->packets());
    return 1;
}

static int Page_size(lua_State* L) {
    TagLib::Ogg::Page* p = Ogg::Page::checkPtr(L, 1);
    lua_pushinteger(L, p->size());
    return 1;
}

static int Page_render(lua_State* L) {
    TagLib::Ogg::Page* p = Ogg::Page::checkPtr(L, 1);
    ByteVector::pushValue(L, p->render());
    return 1;
}

#if LTAGLIB_ATLEAST(LTAGLIB_1_11)
static int Page_pageSequenceNumber(lua_State* L) {
    TagLib::Ogg::Page* p = Ogg::Page::checkPtr(L, 1);
    lua_pushinteger(L, p->pageSequenceNumber());
    return 1;
}

static int Page_setPageSequenceNumber(lua_State* L) {
    TagLib::Ogg::Page* p = Ogg::Page::checkPtr(L, 1);
    p->setPageSequenceNumber(lua_tointeger(L, 2));
    lua_settop(L,1);
    return 1;
}
#endif

static
const luaL_Reg Page__index[] = {
    { "fileOffset", Page_fileOffset },
    { "header", Page_header },
#if LTAGLIB_ATLEAST(LTAGLIB_1_6) && LTAGLIB_UNDER(LTAGLIB_1_12)
    { "getCopyWithNewPageSequenceNumber", Page_getCopyWithNewPageSequenceNumber },
#endif
    { "firstPacketIndex", Page_firstPacketIndex },
    { "setFirstPacketIndex", Page_setFirstPacketIndex },
    { "containsPacket", Page_containsPacket },
    { "packetCount", Page_packetCount },
    { "packets", Page_packets },
    { "size", Page_size },
    { "render", Page_render },
#if LTAGLIB_ATLEAST(LTAGLIB_1_11)
    { "pageSequenceNumber", Page_pageSequenceNumber },
    { "setPageSequenceNumber", Page_setPageSequenceNumber },
#endif
    { NULL, NULL }
};

class LTAGLIB_PRIVATE PageListImpl {
    public:
        class LTAGLIB_PRIVATE Value {
            public:
                typedef TagLib::Ogg::Page taglib_type;
                static void push(lua_State* L, taglib_type* p, int parent) {
                    (void)parent;
                    Ogg::Page::pushPtr(L, p);
                }
        };
};

class LTAGLIB_PRIVATE PageList: public List< TagLib::List< TagLib::Ogg::Page* >, PageListImpl> {
    public:
        static void pushPtr(lua_State* L, const TagLib::List<TagLib::Ogg::Page*>& list, int parent) {
            List< TagLib::List<TagLib::Ogg::Page*>, PageListImpl>::pushList(L, list, parent);
        }
};

static int Page_static_paginate(lua_State* L) {
    int args = lua_gettop(L);

    switch(args) {
        case 4: {
            PageList::pushPtr(
              L,
              TagLib::Ogg::Page::paginate(
                ByteVectorList::looseValue(L, 1),
                Ogg::Page::PaginationStrategy::checkValue(L, 2),
                luaL_checkinteger(L, 3),
                luaL_checkinteger(L, 4)
              ),
              0);
            break;
        }
        case 5: {
            PageList::pushPtr(
              L,
              TagLib::Ogg::Page::paginate(
                ByteVectorList::looseValue(L, 1),
                Ogg::Page::PaginationStrategy::checkValue(L, 2),
                luaL_checkinteger(L, 3),
                luaL_checkinteger(L, 4),
                lua_toboolean(L, 5)
              ),
              0);
            break;
        }
        case 6: {
            PageList::pushPtr(
              L,
              TagLib::Ogg::Page::paginate(
                ByteVectorList::looseValue(L, 1),
                Ogg::Page::PaginationStrategy::checkValue(L, 2),
                luaL_checkinteger(L, 3),
                luaL_checkinteger(L, 4),
                lua_toboolean(L, 5),
                lua_toboolean(L, 6)
              ),
              0);
            break;
        }
        case 7: {
            PageList::pushPtr(
              L,
              TagLib::Ogg::Page::paginate(
                ByteVectorList::looseValue(L, 1),
                Ogg::Page::PaginationStrategy::checkValue(L, 2),
                luaL_checkinteger(L, 3),
                luaL_checkinteger(L, 4),
                lua_toboolean(L, 5),
                lua_toboolean(L, 6),
                lua_toboolean(L, 7)
              ),
              0);
            break;
        }
        return luaL_error(L, "invalid arguments");
    }

    return 1;
}

static const luaL_Reg Page__static[] = {
    { "paginate", Page_static_paginate },
    { NULL, NULL }
};

static int Page__submodules(lua_State* L) {
    luaL_requiref(L, "TagLib.Ogg.Page.ContainsPacketFlags", luaopen_TagLib_Ogg_Page_ContainsPacketFlags, 0);
    lua_setfield(L, -2, "ContainsPacketFlags");

    luaL_requiref(L, "TagLib.Ogg.Page.PaginationStrategy", luaopen_TagLib_Ogg_Page_PaginationStrategy, 0);
    lua_setfield(L, -2, "PaginationStrategy");
    return 0;
}

#define E(x) { #x, sizeof(#x) - 1, TagLib::Ogg::Page::x }

static const Ogg::Page::ContainsPacketFlags::enum_type containsPacketFlags[] = {
    E(DoesNotContainPacket), E(CompletePacket), E(BeginsWithPacket),
    E(EndsWithPacket)
};

static const Ogg::Page::PaginationStrategy::enum_type paginationStrategy[] = {
    E(SinglePagePerGroup), E(Repaginate)
};

LTAGLIB_PUBLIC
int luaopen_TagLib_Ogg_Page(lua_State *L) {
    return Ogg::Page::open(L);
}

LTAGLIB_PUBLIC
int luaopen_TagLib_Ogg_Page_ContainsPacketFlags(lua_State *L) {
    return Ogg::Page::ContainsPacketFlags::open(L);
}

LTAGLIB_PUBLIC
int luaopen_TagLib_Ogg_Page_PaginationStrategy(lua_State* L) {
    return Ogg::Page::PaginationStrategy::open(L);
}

template<>
const UserdataTable Ogg::Page::base::mod = {
    Page__call,
    Page__static,
    Page__submodules,
};


template<>
const UserdataMetatable Ogg::Page::base::metatable = {
    "TagLib::Ogg::Page", /* name */
    Page__index, /* indextable */
    NULL, /* indexfunc */
};


template<>
const Ogg::Page::ContainsPacketFlags::enum_type*
Ogg::Page::ContainsPacketFlags::m_values = containsPacketFlags;

template<>
const size_t Ogg::Page::ContainsPacketFlags::m_len = sizeof(containsPacketFlags) / sizeof(containsPacketFlags[0]);

template<>
const Ogg::Page::PaginationStrategy::enum_type*
Ogg::Page::PaginationStrategy::m_values = paginationStrategy;

template<>
const size_t Ogg::Page::PaginationStrategy::m_len = sizeof(paginationStrategy) / sizeof(paginationStrategy[0]);

template<>
const char* PageList::base::__name = "TagLib::List<TagLib::Ogg::Page*>";

#include "../shared/enum.tcc"

template class Enum<TagLib::Ogg::Page::ContainsPacketFlags>;
template class Enum<TagLib::Ogg::Page::PaginationStrategy>;

#include "../shared/userdata.tcc"
template class BaseUserdata<TagLib::Ogg::Page>;
