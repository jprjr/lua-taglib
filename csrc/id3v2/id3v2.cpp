#include "id3v2.h"
#include "id3v2tag.h"
#include "id3v2header.h"
#include "id3v2footer.h"
#include "id3v2extendedheader.h"
#include "id3v2frame.h"

#if LTAGLIB_HAS_ATTACHEDPICTUREFRAME
#include "attachedpictureframe.h"
#endif

#if LTAGLIB_HAS_CHAPTERFRAME
#include "chapterframe.h"
#endif

#include "commentsframe.h"

#if LTAGLIB_HAS_EVENTTIMINGCODESFRAME
#include "eventtimingcodesframe.h"
#endif

#if LTAGLIB_HAS_GENERALENCAPSULATEDOBJECTFRAME
#include "generalencapsulatedobjectframe.h"
#endif

#if LTAGLIB_HAS_OWNERSHIPFRAME
#include "ownershipframe.h"
#endif

#if LTAGLIB_HAS_PODCASTFRAME
#include "podcastframe.h"
#endif

#if LTAGLIB_HAS_POPULARIMETERFRAME
#include "popularimeterframe.h"
#endif

#if LTAGLIB_HAS_PRIVATEFRAME
#include "privateframe.h"
#endif

#if LTAGLIB_HAS_RELATIVEVOLUMEFRAME
#include "relativevolumeframe.h"
#endif

#if LTAGLIB_HAS_SYNCHRONIZEDLYRICSFRAME
#include "synchronizedlyricsframe.h"
#endif

#include "textidentificationframe.h"

#if LTAGLIB_HAS_TABLEOFCONTENTSFRAME
#include "tableofcontentsframe.h"
#endif

#include "unknownframe.h"

#if LTAGLIB_HAS_UNIQUEFILEIDENTIFIERFRAME
#include "uniquefileidentifierframe.h"
#endif

#if LTAGLIB_HAS_URLLINKFRAME
#include "urllinkframe.h"
#endif

#if LTAGLIB_HAS_UNSYNCHRONIZEDLYRICSFRAME
#include "unsynchronizedlyricsframe.h"
#endif

using namespace LuaTagLib;

#define load(mod) \
luaL_requiref(L, "TagLib.ID3v2." #mod, luaopen_TagLib_ID3v2_ ## mod, 0); \
lua_setfield(L, -2, #mod);

#define loadf(frame) load(frame ## Frame)

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2(lua_State* L) {
    lua_newtable(L);

    load(Tag)
    load(Header)
    load(Footer)
    load(ExtendedHeader)
    load(Frame)

#if LTAGLIB_HAS_ID3V2_VERSION
    load(Version)
#endif

#if LTAGLIB_HAS_ATTACHEDPICTUREFRAME
    loadf(AttachedPicture)
#endif

#if LTAGLIB_HAS_CHAPTERFRAME
    loadf(Chapter)
#endif

    loadf(Comments)

#if LTAGLIB_HAS_EVENTTIMINGCODESFRAME
    loadf(EventTimingCodes)
#endif

#if LTAGLIB_HAS_GENERALENCAPSULATEDOBJECTFRAME
    loadf(GeneralEncapsulatedObject)
#endif

#if LTAGLIB_HAS_OWNERSHIPFRAME
    loadf(Ownership)
#endif

#if LTAGLIB_HAS_PODCASTFRAME
    loadf(Podcast)
#endif

#if LTAGLIB_HAS_POPULARIMETERFRAME
    loadf(Popularimeter)
#endif

#if LTAGLIB_HAS_PRIVATEFRAME
    loadf(Private)
#endif

#if LTAGLIB_HAS_RELATIVEVOLUMEFRAME
    loadf(RelativeVolume)
#endif

#if LTAGLIB_HAS_SYNCHRONIZEDLYRICSFRAME
    loadf(SynchronizedLyrics)
#endif

#if LTAGLIB_HAS_TABLEOFCONTENTSFRAME
    loadf(TableOfContents)
#endif

    loadf(TextIdentification)
    loadf(Unknown)

#if LTAGLIB_HAS_USERTEXTIDENTIFICATIONFRAME
    loadf(UserTextIdentification)
#endif

#if LTAGLIB_HAS_UNIQUEFILEIDENTIFIERFRAME
    loadf(UniqueFileIdentifier)
#endif

#if LTAGLIB_HAS_URLLINKFRAME
    loadf(UrlLink)
    loadf(UserUrlLink)
#endif

#if LTAGLIB_HAS_UNSYNCHRONIZEDLYRICSFRAME
    loadf(UnsynchronizedLyrics)
#endif

    return 1;
}

#if LTAGLIB_HAS_ID3V2_VERSION

using namespace LuaTagLib;

#define E(x) { #x, sizeof(#x) - 1, TagLib::ID3v2::x }
static const ID3v2::Version::enum_type versions[] = {
    E(v3), E(v4)
};

template<>
const ID3v2::Version::enum_type* ID3v2::Version::m_values = versions;

template<>
const size_t ID3v2::Version::m_len = sizeof(versions) / sizeof(versions[0]);

LTAGLIB_PUBLIC
int luaopen_TagLib_ID3v2_Version(lua_State* L) {
    return ID3v2::Version::open(L);
}

#include "../shared/enum.tcc"
template class LuaTagLib::Enum<TagLib::ID3v2::Version>;

#endif
