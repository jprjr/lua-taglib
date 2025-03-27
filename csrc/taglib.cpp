#include "taglib.h"
#include "version.h"

#include "audioproperties.h"
#include "fileref.h"
#include "tag.h"
#include "tbytevector.h"
#include "tbytevectorstream.h"
#include "tfile.h"
#include "tfilestream.h"
#include "tiostream.h"
#include "tstring.h"
#include "tvariant.h"
#include "tversionnumber.h"
#include "ape/ape.h"
#include "asf/asf.h"
#include "dsdiff/dsdiff.h"
#include "dsf/dsf.h"
#include "flac/flac.h"
#include "id3v1/id3v1.h"
#include "id3v2/id3v2.h"
#include "it/it.h"
#include "mpc/mpc.h"
#include "mpeg/mpeg.h"
#include "mp4/mp4.h"
#include "mod/mod.h"
#include "ogg/ogg.h"
#include "riff/riff.h"
#include "s3m/s3m.h"
#include "trueaudio/trueaudio.h"
#include "vorbis/vorbis.h"
#include "wavpack/wavpack.h"
#include "xm/xm.h"

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
#endif

#if LTAGLIB_HAS_ASF
    load(ASF)
#endif

#if LTAGLIB_HAS_DSDIFF
    load(DSDIFF)
#endif

#if LTAGLIB_HAS_DSF
    load(DSF)
#endif

    load(FLAC)
    load(ID3v1)
    load(ID3v2)

#if LTAGLIB_HAS_IT
    load(IT)
#endif

#if LTAGLIB_HAS_MP4
    load(MP4)
#endif

#if LTAGLIB_HAS_MPC
    load(MPC)
#endif

    load(MPEG)

#if LTAGLIB_HAS_MOD
    load(Mod)
#endif

    load(Ogg)

#if LTAGLIB_HAS_RIFF
    load(RIFF)
#endif

#if LTAGLIB_HAS_S3M
    load(S3M)
#endif

#if LTAGLIB_HAS_TRUEAUDIO
    load(TrueAudio)
#endif

    load(Vorbis)

#if LTAGLIB_HAS_WAVPACK
    load(WavPack)
#endif

#if LTAGLIB_HAS_XM
    load(XM)
#endif

    return 1;
}

