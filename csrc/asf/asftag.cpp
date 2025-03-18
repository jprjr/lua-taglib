#include "asftag.h"

#if LTAGLIB_HAS_ASF

#include "asfattribute.h"
#include "../tstring.h"
#include "../tbytevector.h"
#include "../tlist.h"
#include "../tmap.h"

using namespace LuaTagLib;

static int Tag__call(lua_State* L) {
    TagLib::ASF::Tag* t = NULL;
    int args = lua_gettop(L);

    switch(args) {
        case 0: {
            t = new TagLib::ASF::Tag();
            break;
        }
        default: break;
    }

    if(t == NULL) return luaL_error(L, "invalid arguments");
    ASF::Tag::pushPtr(L, t);
    return 1;
}

static int Tag_rating(lua_State* L) {
    TagLib::ASF::Tag* tag = ASF::Tag::checkPtr(L, 1);
    String::pushValue(L, tag->rating());
    return 1;
}

static int Tag_copyright(lua_State* L) {
    TagLib::ASF::Tag* tag = ASF::Tag::checkPtr(L, 1);
    String::pushValue(L, tag->copyright());
    return 1;
}

static int Tag_setRating(lua_State* L) {
    TagLib::ASF::Tag* tag = ASF::Tag::checkPtr(L, 1);
    tag->setRating(String::checkValue(L, 2));

    lua_settop(L,1);
    return 1;
}

static int Tag_setCopyright(lua_State* L) {
    TagLib::ASF::Tag* tag = ASF::Tag::checkPtr(L, 1);
    tag->setCopyright(String::checkValue(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Tag_removeItem(lua_State* L) {
    TagLib::ASF::Tag* tag = ASF::Tag::checkPtr(L, 1);
    tag->removeItem(String::checkValue(L, 2));
    lua_settop(L,1);
    return 1;
}

static int Tag_setAttribute(lua_State* L) {
    TagLib::ASF::Tag* tag = ASF::Tag::checkPtr(L, 1);
    tag->setAttribute(String::checkValue(L, 2), ASF::Attribute::checkValue(L, 3));
    lua_settop(L,1);
    return 1;
}

static int Tag_addAttribute(lua_State* L) {
    TagLib::ASF::Tag* tag = ASF::Tag::checkPtr(L, 1);
    tag->addAttribute(String::checkValue(L, 2), ASF::Attribute::checkValue(L, 3));
    lua_settop(L,1);
    return 1;
}

typedef List<TagLib::ASF::AttributeList, ASF::Attribute> AttributeList;
class LTAGLIB_PRIVATE AttributeListMapImpl {
    public:
        typedef TagLib::ASF::AttributeListMap taglib_type;
        typedef String Key;
        class LTAGLIB_PRIVATE Value {
            public:
                typedef TagLib::ASF::AttributeList taglib_type;
                static void push(lua_State* L, const taglib_type& list, int parent) {
                    (void) parent;
                    ValueList<TagLib::ASF::AttributeList, ASF::Attribute>::pushValue(L, list);
                }
                static taglib_type check(lua_State* L, int idx) {
                    return ValueList<TagLib::ASF::AttributeList, ASF::Attribute>::checkValue(L, idx);
                }
        };
};

typedef ImplMapReference<TagLib::ASF::AttributeListMap, AttributeListMapImpl> AttributeListMap;

static int Tag_attributeListMap(lua_State* L) {
    TagLib::ASF::Tag* tag = ASF::Tag::checkPtr(L, 1);

    AttributeListMap::pushRef(L, tag->attributeListMap(), 1);
    return 1;
}

#if LTAGLIB_ATLEAST(LTAGLIB_1_10)
static int Tag_contains(lua_State* L) {
    lua_pushboolean(L, ASF::Tag::checkPtr(L,1)->contains(String::checkValue(L,2)));
    return 1;
}

static int Tag_attribute(lua_State* L) {
    ValueList<TagLib::ASF::AttributeList, ASF::Attribute>::pushValue(L,
        ASF::Tag::checkPtr(L,1)->attribute(String::checkValue(L,2))
    );
    return 1;
}
#endif

static
const luaL_Reg Tag__index[] = {
    { "rating", Tag_rating },
    { "copyright", Tag_copyright },
    { "setRating", Tag_setRating },
    { "setCopyright", Tag_setCopyright },
    { "removeItem", Tag_removeItem },
    { "setAttribute", Tag_setAttribute },
    { "addAttribute", Tag_addAttribute },
    { "attributeListMap", Tag_attributeListMap },
#if LTAGLIB_ATLEAST(LTAGLIB_1_10)
    { "contains", Tag_contains },
    { "attribute", Tag_attribute },
#endif
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_ASF_Tag(lua_State *L) {
    return ASF::Tag::open(L);
}

template<>
const UserdataTable ASF::Tag::base::mod = {
    Tag__call,
    NULL,
    NULL,
};

template<>
const UserdataMetatable ASF::Tag::base::metatable = {
    "TagLib::ASF::Tag", /* name */
    Tag__index, /* indextable */
    NULL, /* indexfunc */
};

template<>
const char* AttributeListMap::base::__name = "TagLib::ASF::AttributeListMap";

template<>
const char* AttributeList::base::__name = "TagLib::ASF::AttributeList";

#include "../shared/userdata.tcc"
template class DerivedUserdata<TagLib::ASF::Tag, LuaTagLib::Tag>;
#endif
