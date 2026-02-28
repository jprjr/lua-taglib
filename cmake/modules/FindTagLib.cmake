# attempts to find TagLib and extract the version from header files

if(DEFINED LUAROCKS_TAGLIB_LIBRARY AND NOT LUAROCKS_TAGLIB_LIBRARY STREQUAL "")
    set(TAGLIB_LIBRARY "${LUAROCKS_TAGLIB_LIBRARY}")
endif()

if(DEFINED LUAROCKS_TAGLIB_INCLUDE_DIR AND NOT LUAROCKS_TAGLIB_INCLUDE_DIR STREQUAL "")
    set(TAGLIB_INCLUDE_DIR "${LUAROCKS_TAGLIB_INCLUDE_DIR}")
endif()

if(DEFINED LUAROCKS_TAGLIB_USE_ZLIB AND NOT LUAROCKS_TAGLIB_USE_ZLIB STREQUAL "")
    set(TAGLIB_USE_ZLIB "${LUAROCKS_TAGLIB_USE_ZLIB}")
endif()

if(DEFINED LUAROCKS_ZLIB_INCLUDE_DIR AND NOT LUAROCKS_ZLIB_INCLUDE_DIR STREQUAL "")
    set(ZLIB_INCLUDE_DIR "${LUAROCKS_ZLIB_INCLUDE_DIR}")
endif()

if(DEFINED LUAROCKS_ZLIB_LIBRARY AND NOT LUAROCKS_ZLIB_LIBRARY STREQUAL "")
    set(ZLIB_LIBRARY "${LUAROCKS_ZLIB_LIBRARY}")
endif()

if(TAGLIB_USE_ZLIB)
    find_package(ZLIB REQUIRED)
endif()

find_package(PkgConfig QUIET)
if(PkgConfig_FOUND)
    pkg_check_modules(PC_TAGLIB QUIET taglib)
endif()

find_path(TAGLIB_INCLUDE_DIR
  NAMES taglib.h
  HINTS ${PC_TAGLIB_INCLUDE_DIRS}
  PATH_SUFFIXES taglib
  DOC "TagLib include directory"
)
mark_as_advanced(TAGLIB_INCLUDE_DIR)

find_library(TAGLIB_LIBRARY
  NAMES tag
  HINTS ${PC_TAGLIB_LIBRARY_DIRS}
  DOC "TagLib library"
)
mark_as_advanced(TAGLIB_LIBRARY)


if(DEFINED TAGLIB_INCLUDE_DIR AND EXISTS "${TAGLIB_INCLUDE_DIR}/taglib.h")

    file(READ "${TAGLIB_INCLUDE_DIR}/taglib.h" TAGLIB_H_CONTENTS)

    string(
      REGEX MATCH
      "#define TAGLIB_MAJOR_VERSION ([0-9]+)"
      _dummy
      "${TAGLIB_H_CONTENTS}"
    )
    set(TAGLIB_VERSION_MAJOR "${CMAKE_MATCH_1}")

    string(
      REGEX MATCH
      "#define TAGLIB_MINOR_VERSION ([0-9]+)"
      _dummy
      "${TAGLIB_H_CONTENTS}"
    )
    set(TAGLIB_VERSION_MINOR "${CMAKE_MATCH_1}")

    string(
      REGEX MATCH
      "#define TAGLIB_PATCH_VERSION ([0-9]+)"
      _dummy
      "${TAGLIB_H_CONTENTS}"
    )
    set(TAGLIB_VERSION_PATCH "${CMAKE_MATCH_1}")

    # PATCH is optional, versions 1.0 and 1.1 didn't have it
    if(TAGLIB_VERSION_PATCH STREQUAL "")
        set(TAGLIB_VERSION_PATCH "0")
    endif()

    if(
        NOT TAGLIB_VERSION_MAJOR STREQUAL ""
        AND NOT TAGLIB_VERSION_MINOR STREQUAL ""
    )
        set(TAGLIB_VERSION "${TAGLIB_VERSION_MAJOR}.${TAGLIB_VERSION_MINOR}.${TAGLIB_VERSION_PATCH}")
    endif()
endif()

if(TAGLIB_VERSION AND TAGLIB_VERSION VERSION_EQUAL "0.96")
  # TagLib 1.0 and 1.1 both list their version as 0.96 in the headers,
  # we don't have any 1.1-specific features so we'll set it to 1.0
  set(TAGLIB_VERSION_MAJOR "1")
  set(TAGLIB_VERSION_MINOR "0")
  set(TAGLIB_VERSION "${TAGLIB_VERSION_MAJOR}.${TAGLIB_VERSION_MINOR}.${TAGLIB_VERSION_PATCH}")
endif()

if(TAGLIB_VERSION AND TAGLIB_VERSION VERSION_EQUAL "1.7")
  # TagLib 1.8 reports itself as 1.7 in the headers,
  # if tpropertymap.h exists then we're really using taglib 1.8
  if(EXISTS "${TAGLIB_INCLUDE_DIR}/tpropertymap.h")
      # there's no 1.8.1 etc so we'll just set to 1.8.0
      set(TAGLIB_VERSION_MINOR "8")
      set(TAGLIB_VERSION "${TAGLIB_VERSION_MAJOR}.${TAGLIB_VERSION_MINOR}.${TAGLIB_VERSION_PATCH}")
  endif()
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
  TagLib
  REQUIRED_VARS TAGLIB_LIBRARY TAGLIB_INCLUDE_DIR
  VERSION_VAR TAGLIB_VERSION
)

if(TagLib_FOUND)
    set(TAGLIB_LIBRARIES "${TAGLIB_LIBRARY}")
    set(TAGLIB_INCLUDE_DIRS "${TAGLIB_INCLUDE_DIR}")
    set(TAGLIB_DEFINITIONS ${PC_TAGLIB_CFLAGS_OTHER})

    # version-based features
    # starting in taglib 2.1 we pull these values from the taglib_config headers
    set(TAGLIB_WITH_APE OFF)
    set(TAGLIB_WITH_ASF OFF)
    set(TAGLIB_WITH_DSF OFF)
    set(TAGLIB_WITH_MOD OFF)
    set(TAGLIB_WITH_MP4 OFF)
    set(TAGLIB_WITH_RIFF OFF)
    set(TAGLIB_WITH_SHORTEN OFF)
    set(TAGLIB_WITH_TRUEAUDIO OFF)
    set(TAGLIB_WITH_VORBIS OFF)

    set(TAGLIB_WITH_WAVPACK OFF)
    set(TAGLIB_WITH_APE_FILE OFF)

    set(TAGLIB_WITH_ASF_PICTURE OFF)

    set(TAGLIB_WITH_MP4_COVERART OFF)

    set(TAGLIB_WITH_RIFF_INFO OFF)

    set(TAGLIB_WITH_FLAC_PICTURE OFF)
    set(TAGLIB_WITH_FLAC_METADATABLOCK OFF)
    set(TAGLIB_WITH_SPEEX OFF)
    set(TAGLIB_WITH_OPUS OFF)
    set(TAGLIB_WITH_OGG_FLAC OFF)

    set(TAGLIB_WITH_BYTEVECTORSTREAM OFF)
    set(TAGLIB_WITH_FILESTREAM OFF)
    set(TAGLIB_WITH_IOSTREAM OFF)
    set(TAGLIB_WITH_PROPERTYMAP OFF)
    set(TAGLIB_WITH_VARIANT OFF)
    set(TAGLIB_WITH_VERSIONNUMBER ON)

    set(TAGLIB_WITH_ID3V2_ATTACHEDPICTUREFRAME OFF)
    set(TAGLIB_WITH_ID3V2_CHAPTERFRAME OFF)
    set(TAGLIB_WITH_ID3V2_EVENTTIMINGCODESFRAME OFF)
    set(TAGLIB_WITH_ID3V2_GENERALENCAPSULATEDOBJECTFRAME OFF)
    set(TAGLIB_WITH_ID3V2_OWNERSHIPFRAME OFF)
    set(TAGLIB_WITH_ID3V2_PODCASTFRAME OFF)
    set(TAGLIB_WITH_ID3V2_POPULARIMETERFRAME OFF)
    set(TAGLIB_WITH_ID3V2_PRIVATEFRAME OFF)
    set(TAGLIB_WITH_ID3V2_RELATIVEVOLUMEFRAME OFF)
    set(TAGLIB_WITH_ID3V2_SYNCHRONIZEDLYRICSFRAME OFF)
    set(TAGLIB_WITH_ID3V2_TABLEOFCONTENTSFRAME OFF)
    set(TAGLIB_WITH_ID3V2_USERTEXTIDENTIFICATIONFRAME OFF)
    set(TAGLIB_WITH_ID3V2_UNIQUEFILEIDENTIFIERFRAME OFF)
    set(TAGLIB_WITH_ID3V2_UNSYNCHRONIZEDLYRICSFRAME OFF)
    set(TAGLIB_WITH_ID3V2_URLLINKFRAME OFF)

    if(EXISTS "${TAGLIB_INCLUDE_DIR}/apetag.h")
        set(TAGLIB_WITH_APE ON)
    endif()

    if(EXISTS "${TAGLIB_INCLUDE_DIR}/asffile.h")
        set(TAGLIB_WITH_ASF ON)
    endif()

    if(EXISTS "${TAGLIB_INCLUDE_DIR}/dsffile.h")
        set(TAGLIB_WITH_DSF ON)
    endif()

    if(EXISTS "${TAGLIB_INCLUDE_DIR}/modfile.h")
        set(TAGLIB_WITH_MOD ON)
    endif()

    if(EXISTS "${TAGLIB_INCLUDE_DIR}/mp4file.h")
        set(TAGLIB_WITH_MP4 ON)
    endif()

    if(EXISTS "${TAGLIB_INCLUDE_DIR}/rifffile.h")
        set(TAGLIB_WITH_RIFF ON)
    endif()

    if(EXISTS "${TAGLIB_INCLUDE_DIR}/trueaudiofile.h")
        set(TAGLIB_WITH_TRUEAUDIO ON)
    endif()

    if(EXISTS "${TAGLIB_INCLUDE_DIR}/shortenfile.h")
        set(TAGLIB_WITH_SHORTEN ON)
    endif()

    if(EXISTS "${TAGLIB_INCLUDE_DIR}/oggfile.h")
        set(TAGLIB_WITH_VORBIS ON)
    endif()

    if(EXISTS "${TAGLIB_INCLUDE_DIR}/apefile.h")
        set(TAGLIB_WITH_APE_FILE ON)
    endif()

    if(EXISTS "${TAGLIB_INCLUDE_DIR}/wavpackfile.h")
        set(TAGLIB_WITH_WAVPACK ON)
    endif()

    if(EXISTS "${TAGLIB_INCLUDE_DIR}/asfpicture.h")
        set(TAGLIB_WITH_ASF_PICTURE ON)
    endif()

    if(EXISTS "${TAGLIB_INCLUDE_DIR}/flacmetadatablock.h")
        set(TAGLIB_WITH_FLAC_METADATABLOCK ON)
    endif()

    if(EXISTS "${TAGLIB_INCLUDE_DIR}/flacpicture.h")
        set(TAGLIB_WITH_FLAC_PICTURE ON)
    endif()

    if(EXISTS "${TAGLIB_INCLUDE_DIR}/oggflacfile.h")
        set(TAGLIB_WITH_OGG_FLAC ON)
    endif()

    if(EXISTS "${TAGLIB_INCLUDE_DIR}/speexfile.h")
        set(TAGLIB_WITH_SPEEX ON)
    endif()

    if(EXISTS "${TAGLIB_INCLUDE_DIR}/opusfile.h")
        set(TAGLIB_WITH_OPUS ON)
    endif()

    if(EXISTS "${TAGLIB_INCLUDE_DIR}/mp4coverart.h")
        set(TAGLIB_WITH_MP4_COVERART ON)
    endif()

    if(EXISTS "${TAGLIB_INCLUDE_DIR}/infotag.h")
        set(TAGLIB_WITH_RIFF_INFO ON)
    endif()

    if(EXISTS "${TAGLIB_INCLUDE_DIR}/bytevectorstream.h")
        set(TAGLIB_WITH_BYTEVECTORSTREAM ON)
    endif()

    if(EXISTS "${TAGLIB_INCLUDE_DIR}/tfilestream.h")
        set(TAGLIB_WITH_FILESTREAM ON)
    endif()

    if(EXISTS "${TAGLIB_INCLUDE_DIR}/tiostream.h")
        set(TAGLIB_WITH_IOSTREAM ON)
    endif()

    if(EXISTS "${TAGLIB_INCLUDE_DIR}/tpropertymap.h")
        set(TAGLIB_WITH_PROPERTYMAP ON)
    endif()

    if(EXISTS "${TAGLIB_INCLUDE_DIR}/tvariant.h")
        set(TAGLIB_WITH_VARIANT ON)
    endif()

    if(EXISTS "${TAGLIB_INCLUDE_DIR}/tversionnumber.h")
        set(TAGLIB_WITH_VERSIONNUMBER ON)
    endif()

    if(EXISTS "${TAGLIB_INCLUDE_DIR}/attachedpictureframe.h")
        set(TAGLIB_WITH_ID3V2_ATTACHEDPICTUREFRAME ON)
    endif()

    if(EXISTS "${TAGLIB_INCLUDE_DIR}/chapterframe.h")
        set(TAGLIB_WITH_ID3V2_CHAPTERFRAME ON)
    endif()

    if(EXISTS "${TAGLIB_INCLUDE_DIR}/eventtimingcodesframe.h")
        set(TAGLIB_WITH_ID3V2_EVENTTIMINGCODESFRAME ON)
    endif()

    if(EXISTS "${TAGLIB_INCLUDE_DIR}/generalencapsulatedobjectframe.h")
        set(TAGLIB_WITH_ID3V2_GENERALENCAPSULATEDOBJECTFRAME ON)
    endif()

    if(EXISTS "${TAGLIB_INCLUDE_DIR}/ownershipframe.h")
        set(TAGLIB_WITH_ID3V2_OWNERSHIPFRAME ON)
    endif()

    if(EXISTS "${TAGLIB_INCLUDE_DIR}/podcastframe.h")
        set(TAGLIB_WITH_ID3V2_PODCASTFRAME ON)
    endif()

    if(EXISTS "${TAGLIB_INCLUDE_DIR}/popularimeterframe.h")
        set(TAGLIB_WITH_ID3V2_POPULARIMETERFRAME ON)
    endif()

    if(EXISTS "${TAGLIB_INCLUDE_DIR}/privateframe.h")
        set(TAGLIB_WITH_ID3V2_PRIVATEFRAME ON)
    endif()

    if(EXISTS "${TAGLIB_INCLUDE_DIR}/relativevolumeframe.h")
        set(TAGLIB_WITH_ID3V2_RELATIVEVOLUMEFRAME ON)
    endif()

    if(EXISTS "${TAGLIB_INCLUDE_DIR}/synchronizedlyricsframe.h")
        set(TAGLIB_WITH_ID3V2_SYNCHRONIZEDLYRICSFRAME ON)
    endif()

    if(EXISTS "${TAGLIB_INCLUDE_DIR}/tableofcontentsframe.h")
        set(TAGLIB_WITH_ID3V2_TABLEOFCONTENTSFRAME ON)
    endif()

    if(TAGLIB_VERSION VERSION_GREATER_EQUAL "1.3")
        set(TAGLIB_WITH_ID3V2_USERTEXTIDENTIFICATIONFRAME ON)
    endif()

    if(EXISTS "${TAGLIB_INCLUDE_DIR}/uniquefileidentifierframe.h")
        set(TAGLIB_WITH_ID3V2_UNIQUEFILEIDENTIFIERFRAME ON)
    endif()

    if(EXISTS "${TAGLIB_INCLUDE_DIR}/unsynchronizedlyricsframe.h")
        set(TAGLIB_WITH_ID3V2_UNSYNCHRONIZEDLYRICSFRAME ON)
    endif()

    if(EXISTS "${TAGLIB_INCLUDE_DIR}/urllinkframe.h")
        set(TAGLIB_WITH_ID3V2_URLLINKFRAME ON)
    endif()

    message(STATUS "TagLib Features:")
    message(STATUS "  ID3v2 Attached Picture Frame: ${TAGLIB_WITH_ID3V2_ATTACHEDPICTUREFRAME}")
    message(STATUS "  ID3v2 Chapter Frame: ${TAGLIB_WITH_ID3V2_CHAPTERFRAME}")
    message(STATUS "  ID3v2 Event Timing Codes Frame: ${TAGLIB_WITH_ID3V2_EVENTTIMINGCODESFRAME}")
    message(STATUS "  ID3v2 General Encapsulated Object Frame: ${TAGLIB_WITH_ID3V2_GENERALENCAPSULATEDOBJECTFRAME}")
    message(STATUS "  ID3v2 Ownership Frame: ${TAGLIB_WITH_ID3V2_OWNERSHIPFRAME}")
    message(STATUS "  ID3v2 Podcast Frame: ${TAGLIB_WITH_ID3V2_PODCASTFRAME}")
    message(STATUS "  ID3v2 Popularimeter Frame: ${TAGLIB_WITH_ID3V2_POPULARIMETERFRAME}")
    message(STATUS "  ID3v2 Private Frame: ${TAGLIB_WITH_ID3V2_PRIVATEFRAME}")
    message(STATUS "  ID3v2 Relative Volume Frame: ${TAGLIB_WITH_ID3V2_RELATIVEVOLUMEFRAME}")
    message(STATUS "  ID3v2 Synchronized Lyrics Frame: ${TAGLIB_WITH_ID3V2_SYNCHRONIZEDLYRICSFRAME}")
    message(STATUS "  ID3v2 Table of Contents Frame: ${TAGLIB_WITH_ID3V2_TABLEOFCONTENTSFRAME}")
    message(STATUS "  ID3v2 Usertext Frame: ${TAGLIB_WITH_ID3V2_USERTEXTIDENTIFICATIONFRAME}")
    message(STATUS "  ID3v2 Unique File Identifier Frame: ${TAGLIB_WITH_ID3V2_UNIQUEFILEIDENTIFIERFRAME}")
    message(STATUS "  ID3v2 Unsynchronized Lyrics Frame: ${TAGLIB_WITH_ID3V2_UNSYNCHRONIZEDLYRICSFRAME}")
    message(STATUS "  ID3v2 URL Link Frame: ${TAGLIB_WITH_ID3V2_URLLINKFRAME}")

    message(STATUS "  APE Tag and MPC file support (TagLib 1.3+): ${TAGLIB_WITH_APE}")
    message(STATUS "  APE file support (TagLib 1.7+): ${TAGLIB_WITH_APE_FILE}")
    message(STATUS "  WavPack support (TagLib 1.5+): ${TAGLIB_WITH_WAVPACK}")

    message(STATUS "  ASF support (TagLib 1.6+): ${TAGLIB_WITH_ASF}")
    message(STATUS "  ASF Picture support (TagLib 1.7+): ${TAGLIB_WITH_ASF_PICTURE}")

    message(STATUS "  DSF and DSDIIF support (TagLib 2.0+): ${TAGLIB_WITH_DSF}")

    message(STATUS "  MOD, XM, S3M, IT support (TagLib 1.8+): ${TAGLIB_WITH_MOD}")

    message(STATUS "  MP4 support (TagLib 1.6+): ${TAGLIB_WITH_MP4}")
    message(STATUS "  MP4 Cover art support (TagLib 1.7+): ${TAGLIB_WITH_MP4_COVERART}")

    message(STATUS "  RIFF support (TagLib 1.6+): ${TAGLIB_WITH_RIFF}")
    message(STATUS "  RIFF INFO tag support (TagLib 1.9+): ${TAGLIB_WITH_RIFF_INFO}")

    message(STATUS "  Shorten support (TagLib 2.1+): ${TAGLIB_WITH_SHORTEN}")

    message(STATUS "  TrueAudio support (TagLib 1.5+): ${TAGLIB_WITH_TRUEAUDIO}")

    message(STATUS "  Ogg/Vorbis support (TagLib 1.0+): ${TAGLIB_WITH_VORBIS}")
    message(STATUS "  FLAC-in-Ogg support (TagLib 1.2+): ${TAGLIB_WITH_OGG_FLAC}")
    message(STATUS "  Speex support (TagLib 1.5+): ${TAGLIB_WITH_SPEEX}")
    message(STATUS "  FLAC Picture support (TagLib 1.7+): ${TAGLIB_WITH_FLAC_PICTURE}")
    message(STATUS "  FLAC MetadataBlock support (TagLib 1.7+): ${TAGLIB_WITH_FLAC_METADATABLOCK}")
    message(STATUS "  Opus support (TagLib 1.9+): ${TAGLIB_WITH_OPUS}")

    if(NOT TARGET TagLib::TagLib)
        add_library(TagLib::TagLib UNKNOWN IMPORTED)
        set_target_properties(TagLib::TagLib PROPERTIES
          IMPORTED_LOCATION "${TAGLIB_LIBRARY}"
          INTERFACE_COMPILE_OPTIONS "${PC_TAGLIB_CFLAGS_OTHER}"
          INTERFACE_INCLUDE_DIRECTORIES "${TAGLIB_INCLUDE_DIR}"
        )
        if(TAGLIB_USE_ZLIB)
            target_link_libraries(TagLib::TagLib INTERFACE "${ZLIB_LIBRARY}")
        endif()
    endif()
endif()
