#include "taglib.h"
#include "version.h"

#include "audioproperties.h"
#include "fileref.h"
#include "tag.h"
#include "tbytevector.h"

#if LTAGLIB_HAS_BYTEVECTORSTREAM
#include "tbytevectorstream.h"
#endif

#include "tfile.h"

#if LTAGLIB_HAS_FILESTREAM
#include "tfilestream.h"
#endif

#if LTAGLIB_HAS_IOSTREAM
#include "tiostream.h"
#endif

#include "tstring.h"

#if LTAGLIB_HAS_VARIANT
#include "tvariant.h"
#endif

#include "tversionnumber.h"

#if LTAGLIB_HAS_APE
#include "ape/ape.h"
#include "mpc/mpc.h"
#endif

#if LTAGLIB_HAS_ASF
#include "asf/asf.h"
#endif

#if LTAGLIB_HAS_DSF
#include "dsdiff/dsdiff.h"
#include "dsf/dsf.h"
#endif

#if LTAGLIB_HAS_VORBIS
#include "flac/flac.h"
#include "ogg/ogg.h"
#include "vorbis/vorbis.h"
#endif

#if LTAGLIB_HAS_RIFF
#include "riff/riff.h"
#endif

#if LTAGLIB_HAS_MOD
#include "mod/mod.h"
#include "it/it.h"
#include "s3m/s3m.h"
#include "xm/xm.h"
#endif

#if LTAGLIB_HAS_MP4
#include "mp4/mp4.h"
#endif

#if LTAGLIB_HAS_SHORTEN
#include "shorten/shorten.h"
#endif

#if LTAGLIB_HAS_TRUEAUDIO
#include "trueaudio/trueaudio.h"
#endif

#if LTAGLIB_HAS_WAVPACK
#include "wavpack/wavpack.h"
#endif

#include "id3v1/id3v1.h"
#include "id3v2/id3v2.h"
#include "mpeg/mpeg.h"

using namespace LuaTagLib;

#define load(mod) \
luaL_requiref(L, "TagLib." #mod, luaopen_TagLib_ ## mod, 0); \
lua_setfield(L, -2, #mod);

LTAGLIB_PUBLIC
int luaopen_TagLib(lua_State* L) {
    lua_newtable(L);

    load(_VERSION)

    load(AudioProperties)
    load(ByteVector)
#if LTAGLIB_HAS_BYTEVECTORSTREAM
    load(ByteVectorStream)
#endif
    load(File)
    load(FileRef)
#if LTAGLIB_HAS_IOSTREAM
    load(IOStream)
#endif

#if LTAGLIB_HAS_FILESTREAM
    load(FileStream)
#endif
    load(String)
    load(Tag)
#if LTAGLIB_HAS_VARIANT
    load(Variant)
#endif
    load(VersionNumber)
    load(runtimeVersion)
    load(compiletimeVersion)


#if LTAGLIB_HAS_APE
    load(APE)
    load(MPC)
#endif

#if LTAGLIB_HAS_ASF
    load(ASF)
#endif

#if LTAGLIB_HAS_DSF
    load(DSF)
    load(DSDIFF)
#endif

    load(ID3v1)
    load(ID3v2)

#if LTAGLIB_HAS_MP4
    load(MP4)
#endif

    load(MPEG)

#if LTAGLIB_HAS_MOD
    load(Mod)
    load(IT)
    load(S3M)
    load(XM)
#endif

#if LTAGLIB_HAS_RIFF
    load(RIFF)
#endif

#if LTAGLIB_HAS_SHORTEN
    load(Shorten)
#endif

#if LTAGLIB_HAS_TRUEAUDIO
    load(TrueAudio)
#endif

#if LTAGLIB_HAS_VORBIS
    load(FLAC)
    load(Ogg)
    load(Vorbis)
#endif

#if LTAGLIB_HAS_WAVPACK
    load(WavPack)
#endif

    return 1;
}

