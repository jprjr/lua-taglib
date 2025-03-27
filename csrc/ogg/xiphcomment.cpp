#include "xiphcomment.h"

#include "../tbytevector.h"
#include "../tstring.h"
#include "../tstringlist.h"
#include "../tlist.h"
#include "../tmap.h"
#include "../flac/flacpicture.h"

using namespace LuaTagLib;

static int XiphComment__call(lua_State* L) {
    int args = lua_gettop(L);
    TagLib::Ogg::XiphComment* x = NULL;

    switch(args) {
        case 0: {
            x = new TagLib::Ogg::XiphComment();
            break;
        }
        case 1: {
            x = new TagLib::Ogg::XiphComment(ByteVector::looseValue(L, 2));
            break;
        }
        default: break;
    }

    if(x == NULL) return luaL_error(L, "invalid argument");
    Ogg::XiphComment::pushPtr(L, x);
    return 1;
}

static int XiphComment_addField(lua_State* L) {
    int args = lua_gettop(L);
    TagLib::Ogg::XiphComment* xc = Ogg::XiphComment::checkPtr(L, 1);

    switch(args) {
        case 3: {
            xc->addField(String::checkValue(L, 2), String::checkValue(L, 3));
            break;
        }
        case 4: {
            xc->addField(String::checkValue(L, 2), String::checkValue(L, 3), (bool) lua_toboolean(L, 4));
            break;
        }
        default: {
            return luaL_error(L, "invalid arguments");
        }
    }
    lua_settop(L,1);
    return 1;
}

#if LTAGLIB_UNDER(LTAGLIB_1_12)
static int XiphComment_removeField(lua_State* L) {
    int args = lua_gettop(L);
    TagLib::Ogg::XiphComment* xc = Ogg::XiphComment::checkPtr(L, 1);

    switch(args) {
        case 2: {
            xc->removeField(String::checkValue(L, 2));
            break;
        }
        case 3: {
            xc->removeField(String::checkValue(L, 2), String::checkValue(L, 3));
            break;
        }
        default: {
            return luaL_error(L, "invalid arguments");
        }
    }
    lua_settop(L,1);
    return 1;
}
#endif

static int XiphComment_fieldCount(lua_State* L) {
    TagLib::Ogg::XiphComment* xc = Ogg::XiphComment::checkPtr(L, 1);
    lua_pushinteger(L, xc->fieldCount());
    return 1;
}

class LTAGLIB_PRIVATE FieldListMapImpl {
    public:
        typedef TagLib::Ogg::FieldListMap taglib_type;
        typedef String Key;
        class LTAGLIB_PRIVATE Value {
            public:
                typedef TagLib::StringList taglib_type;
                static void push(lua_State* L, const taglib_type& list, int parent) {
                    (void) parent;
                    StringList::pushValue(L, list);
                }
        };
};

typedef ConstImplMapReference<TagLib::Ogg::FieldListMap, FieldListMapImpl> FieldListMap;

static int XiphComment_fieldListMap(lua_State* L) {
    TagLib::Ogg::XiphComment* xc = Ogg::XiphComment::checkPtr(L, 1);

    FieldListMap::pushRef(L, xc->fieldListMap(), 1);
    return 1;
}

static int XiphComment_vendorID(lua_State* L) {
    TagLib::Ogg::XiphComment* xc = Ogg::XiphComment::checkPtr(L, 1);
    String::pushValue(L, xc->vendorID());
    return 1;
}

#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,5,0)
static int XiphComment_contains(lua_State* L) {
    TagLib::Ogg::XiphComment* xc = Ogg::XiphComment::checkPtr(L, 1);
    lua_pushboolean(L, xc->contains(String::checkValue(L, 2)));
    return 1;
}
#endif

static int XiphComment_render(lua_State* L) {
    TagLib::Ogg::XiphComment* xc = Ogg::XiphComment::checkPtr(L, 1);
#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,2,0)
    if(lua_gettop(L) == 2) {
          ByteVector::pushValue(L, xc->render( (bool) lua_toboolean(L,2)));
          return 1;
    }
#endif
    ByteVector::pushValue(L, xc->render());
    return 1;
}

#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,11,0)
static int XiphComment_removeFields(lua_State* L) {
    int args = lua_gettop(L);
    TagLib::Ogg::XiphComment* xc = Ogg::XiphComment::checkPtr(L, 1);

    switch(args) {
        case 2: {
            xc->removeFields(String::checkValue(L, 2));
            break;
        }
        case 3: {
            xc->removeFields(String::checkValue(L, 2), String::checkValue(L, 3));
            break;
        }
        default: {
            return luaL_error(L, "invalid arguments");
        }
    }

    lua_settop(L,1);
    return 1;
}

static int XiphComment_removeAllFields(lua_State* L) {
    TagLib::Ogg::XiphComment* xc = Ogg::XiphComment::checkPtr(L, 1);
    xc->removeAllFields();
    lua_settop(L,1);
    return 1;
}

static int XiphComment_pictureList(lua_State* L) {
    TagLib::Ogg::XiphComment* xc = Ogg::XiphComment::checkPtr(L, 1);
    PtrList< TagLib::List<TagLib::FLAC::Picture*>, FLAC::Picture>::pushPtr(L, xc->pictureList(), 1);
    return 1;
}

static int XiphComment_removePicture(lua_State* L) {
    int args = lua_gettop(L);
    TagLib::Ogg::XiphComment* xc = Ogg::XiphComment::checkPtr(L, 1);
    TagLib::FLAC::Picture* pic = FLAC::Picture::checkPtr(L, 2);

    switch(args) {
        case 2: {
            xc->removePicture(pic);
            break;
        }
        case 3: {
            xc->removePicture(pic, lua_toboolean(L, 3));
            break;
        }
        default: return luaL_error(L,"invalid arguments");
    }
    lua_settop(L,1);
    return 1;
}

static int XiphComment_removeAllPictures(lua_State* L) {
    TagLib::Ogg::XiphComment* xc = Ogg::XiphComment::checkPtr(L, 1);
    xc->removeAllPictures();
    lua_settop(L,1);
    return 1;
}

static int XiphComment_addPicture(lua_State* L) {
    TagLib::Ogg::XiphComment* xc = Ogg::XiphComment::checkPtr(L, 1);
    TagLib::FLAC::Picture* pic = FLAC::Picture::checkPtr(L, 2);
    xc->addPicture(pic);
    lua_settop(L,1);
    return 1;
}
#endif

static
const luaL_Reg XiphComment__index[] = {
    { "addField", XiphComment_addField },
#if LTAGLIB_UNDER(LTAGLIB_1_12)
    { "removeField", XiphComment_removeField },
#endif
    { "fieldCount", XiphComment_fieldCount },
    { "fieldListMap", XiphComment_fieldListMap },
    { "vendorID", XiphComment_vendorID },
#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,5,0)
    { "contains", XiphComment_contains },
#endif
    { "render", XiphComment_render },
#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,11,0)
    { "removeFields", XiphComment_removeFields },
    { "removeAllFields", XiphComment_removeAllFields },
    { "pictureList", XiphComment_pictureList },
    { "removePicture", XiphComment_removePicture },
    { "removeAllPictures", XiphComment_removeAllPictures },
    { "addPicture", XiphComment_addPicture },
#endif
    { NULL, NULL }
};

#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,8,0)
static int XiphComment_static_checkKey(lua_State* L) {
    lua_pushboolean(L, TagLib::Ogg::XiphComment::checkKey(String::checkValue(L, 1)));
    return 1;
}
#endif

static const luaL_Reg XiphComment__static[] = {
#if LTAGLIB_VERSION >= LTAGLIB_VERSION_NUM(1,8,0)
    { "checkKey", XiphComment_static_checkKey },
#endif
    { NULL, NULL }
};

LTAGLIB_PUBLIC
int luaopen_TagLib_Ogg_XiphComment(lua_State* L) {
    return Ogg::XiphComment::open(L);
}

template<>
const UserdataTable Ogg::XiphComment::base::mod = {
    XiphComment__call,
    XiphComment__static,
    NULL,
};

template<>
const UserdataMetatable Ogg::XiphComment::base::metatable = {
    "TagLib::Ogg::XiphComment", /* name */
    XiphComment__index, /* indextable */
    NULL, /* indexfunc */
};


template<>
const char* FieldListMap::base::__name = "TagLib::Ogg::FieldListMap";

#include "../shared/userdata.tcc"
template class LuaTagLib::DerivedUserdata<TagLib::Ogg::XiphComment, LuaTagLib::Tag>;
