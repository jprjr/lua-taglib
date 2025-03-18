#ifndef LTAGLIB_PICTURE_INCLUDE_GUARD
#define LTAGLIB_PICTURE_INCLUDE_GUARD

#define LTAGLIB_PICTURE_E(prefix, x) { #x, sizeof(#x) - 1, prefix::x }

#define LTAGLIB_PICTURE_ENUM(e) \
LTAGLIB_PICTURE_E(e, Other), \
LTAGLIB_PICTURE_E(e, FileIcon), \
LTAGLIB_PICTURE_E(e, OtherFileIcon), \
LTAGLIB_PICTURE_E(e, FrontCover), \
LTAGLIB_PICTURE_E(e, BackCover), \
LTAGLIB_PICTURE_E(e, LeafletPage), \
LTAGLIB_PICTURE_E(e, Media), \
LTAGLIB_PICTURE_E(e, LeadArtist), \
LTAGLIB_PICTURE_E(e, Artist), \
LTAGLIB_PICTURE_E(e, Conductor), \
LTAGLIB_PICTURE_E(e, Band), \
LTAGLIB_PICTURE_E(e, Composer), \
LTAGLIB_PICTURE_E(e, Lyricist), \
LTAGLIB_PICTURE_E(e, RecordingLocation), \
LTAGLIB_PICTURE_E(e, DuringRecording), \
LTAGLIB_PICTURE_E(e, DuringPerformance), \
LTAGLIB_PICTURE_E(e, MovieScreenCapture), \
LTAGLIB_PICTURE_E(e, ColouredFish), \
LTAGLIB_PICTURE_E(e, Illustration), \
LTAGLIB_PICTURE_E(e, BandLogo), \
LTAGLIB_PICTURE_E(e, PublisherLogo)


#endif

