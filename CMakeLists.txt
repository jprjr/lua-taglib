cmake_minimum_required(VERSION 3.13) # target_link_options required 3.13
project(lua-taglib LANGUAGES C CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

include(SourceCompileDefinitions)
include(CheckIPOSupported)
check_ipo_supported(RESULT LTO_SUPPORTED)

if(LUA_VERSION)
  find_package(Lua ${LUA_VERSION} EXACT REQUIRED)
else()
  find_package(Lua REQUIRED)
  set(LUA_VERSION "${LUA_VERSION_MAJOR}.${LUA_VERSION_MINOR}" CACHE STRING "Lua version to use")
endif()

find_package(TagLib REQUIRED)

if(NOT DEFINED CMODULE_INSTALL_DIR)
    set(CMODULE_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/lib/lua/${LUA_VERSION}")
endif()

set(luataglib_sources)
set(luataglib_iostream_sources)
set(luataglib_id3v2_definitions)

list(APPEND luataglib_sources "csrc/version.c")
list(APPEND luataglib_sources "csrc/lua/compat.cpp")
list(APPEND luataglib_sources "csrc/lua/meta.cpp")
list(APPEND luataglib_sources "csrc/lua/lstring.cpp")
list(APPEND luataglib_sources "csrc/shared/integer.cpp")
list(APPEND luataglib_sources "csrc/shared/userdata.cpp")
list(APPEND luataglib_sources "csrc/audioproperties.cpp")
list(APPEND luataglib_sources "csrc/fileref.cpp")
list(APPEND luataglib_sources "csrc/tag.cpp")
list(APPEND luataglib_sources "csrc/taglib.cpp")
list(APPEND luataglib_sources "csrc/tbytevector.cpp")
list(APPEND luataglib_sources "csrc/tbytevectorlist.cpp")
list(APPEND luataglib_sources "csrc/tfile.cpp")
list(APPEND luataglib_sources "csrc/tstring.cpp")
list(APPEND luataglib_sources "csrc/tstringlist.cpp")
list(APPEND luataglib_sources "csrc/tversionnumber.cpp")
if(TAGLIB_WITH_VERSIONNUMBER)
  source_compile_def("csrc/tversionnumber.cpp" "LTAGLIB_HAS_VERSIONNUMBER")
endif()

list(APPEND luataglib_iostream_sources "csrc/taglib.cpp")

if(TAGLIB_WITH_APE)
    list(APPEND luataglib_sources "csrc/ape/ape.cpp")
    list(APPEND luataglib_sources "csrc/ape/apefooter.cpp")
    list(APPEND luataglib_sources "csrc/ape/apeitem.cpp")
    list(APPEND luataglib_sources "csrc/ape/apetag.cpp")
    list(APPEND luataglib_sources "csrc/mpc/mpc.cpp")
    list(APPEND luataglib_sources "csrc/mpc/mpcfile.cpp")
    list(APPEND luataglib_sources "csrc/mpc/mpcproperties.cpp")

    list(APPEND luataglib_iostream_sources "csrc/mpc/mpcfile.cpp")

    source_compile_def("csrc/taglib.cpp" "LTAGLIB_HAS_APE")
    source_compile_def("csrc/taglib.cpp" "LTAGLIB_HAS_MPC")
    source_compile_def("csrc/mpeg/mpegfile.cpp" "LTAGLIB_HAS_APE")
endif()

if(TAGLIB_WITH_APE_FILE)
    list(APPEND luataglib_sources "csrc/ape/apefile.cpp")
    list(APPEND luataglib_sources "csrc/ape/apeproperties.cpp")

    list(APPEND luataglib_iostream_sources "csrc/ape/apefile.cpp")

    source_compile_def("csrc/ape/ape.cpp" "LTAGLIB_HAS_APE_FILE")
endif()

if(TAGLIB_WITH_WAVPACK)
    list(APPEND luataglib_sources "csrc/wavpack/wavpack.cpp")
    list(APPEND luataglib_sources "csrc/wavpack/wavpackfile.cpp")
    list(APPEND luataglib_sources "csrc/wavpack/wavpackproperties.cpp")

    list(APPEND luataglib_iostream_sources "csrc/wavpack/wavpackfile.cpp")

    source_compile_def("csrc/taglib.cpp" "LTAGLIB_HAS_WAVPACK")
endif()

if(TAGLIB_WITH_ASF)
    list(APPEND luataglib_sources "csrc/asf/asf.cpp")
    list(APPEND luataglib_sources "csrc/asf/asfattribute.cpp")
    list(APPEND luataglib_sources "csrc/asf/asffile.cpp")
    list(APPEND luataglib_sources "csrc/asf/asfproperties.cpp")
    list(APPEND luataglib_sources "csrc/asf/asftag.cpp")

    list(APPEND luataglib_iostream_sources "csrc/asf/asffile.cpp")

    source_compile_def("csrc/taglib.cpp" "LTAGLIB_HAS_ASF")
endif()

if(TAGLIB_WITH_ASF_PICTURE)
    list(APPEND luataglib_sources "csrc/asf/asfpicture.cpp")

    source_compile_def("csrc/asf/asf.cpp" "LTAGLIB_HAS_ASF_PICTURE")
    source_compile_def("csrc/asf/asfattribute.cpp" "LTAGLIB_HAS_ASF_PICTURE")
endif()

if(TAGLIB_WITH_DSF)
    list(APPEND luataglib_sources "csrc/dsdiff/dsdiff.cpp")
    list(APPEND luataglib_sources "csrc/dsdiff/dsdifffile.cpp")
    list(APPEND luataglib_sources "csrc/dsdiff/dsdiffproperties.cpp")
    list(APPEND luataglib_sources "csrc/dsdiff/diin/dsdiffdiin.cpp")
    list(APPEND luataglib_sources "csrc/dsdiff/diin/dsdiffdiintag.cpp")
    list(APPEND luataglib_sources "csrc/dsf/dsf.cpp")
    list(APPEND luataglib_sources "csrc/dsf/dsffile.cpp")
    list(APPEND luataglib_sources "csrc/dsf/dsfproperties.cpp")

    list(APPEND luataglib_iostream_sources "csrc/dsf/dsffile.cpp")
    list(APPEND luataglib_iostream_sources "csrc/dsf/dsdifffile.cpp")

    source_compile_def("csrc/taglib.cpp" "LTAGLIB_HAS_DSF")
    source_compile_def("csrc/taglib.cpp" "LTAGLIB_HAS_DSDIIF")
endif()

if(TAGLIB_WITH_MOD)
    list(APPEND luataglib_sources "csrc/it/it.cpp")
    list(APPEND luataglib_sources "csrc/it/itfile.cpp")
    list(APPEND luataglib_sources "csrc/it/itproperties.cpp")
    list(APPEND luataglib_sources "csrc/mod/mod.cpp")
    list(APPEND luataglib_sources "csrc/mod/modfile.cpp")
    list(APPEND luataglib_sources "csrc/mod/modfilebase.cpp")
    list(APPEND luataglib_sources "csrc/mod/modproperties.cpp")
    list(APPEND luataglib_sources "csrc/mod/modtag.cpp")
    list(APPEND luataglib_sources "csrc/s3m/s3m.cpp")
    list(APPEND luataglib_sources "csrc/s3m/s3mfile.cpp")
    list(APPEND luataglib_sources "csrc/s3m/s3mproperties.cpp")
    list(APPEND luataglib_sources "csrc/xm/xm.cpp")
    list(APPEND luataglib_sources "csrc/xm/xmfile.cpp")
    list(APPEND luataglib_sources "csrc/xm/xmproperties.cpp")

    list(APPEND luataglib_iostream_sources "csrc/mod/modfile.cpp")
    list(APPEND luataglib_iostream_sources "csrc/it/itfile.cpp")
    list(APPEND luataglib_iostream_sources "csrc/s3m/s3mfile.cpp")
    list(APPEND luataglib_iostream_sources "csrc/xm/xmfile.cpp")

    source_compile_def("csrc/taglib.cpp" "LTAGLIB_HAS_MOD")
    source_compile_def("csrc/taglib.cpp" "LTAGLIB_HAS_IT")
    source_compile_def("csrc/taglib.cpp" "LTAGLIB_HAS_S3M")
    source_compile_def("csrc/taglib.cpp" "LTAGLIB_HAS_XM")
endif()

if(TAGLIB_WITH_MP4)
    list(APPEND luataglib_sources "csrc/mp4/mp4.cpp")
    list(APPEND luataglib_sources "csrc/mp4/mp4file.cpp")
    list(APPEND luataglib_sources "csrc/mp4/mp4item.cpp")
    list(APPEND luataglib_sources "csrc/mp4/mp4properties.cpp")
    list(APPEND luataglib_sources "csrc/mp4/mp4tag.cpp")

    list(APPEND luataglib_iostream_sources "csrc/mp4/mp4file.cpp")

    source_compile_def("csrc/taglib.cpp" "LTAGLIB_HAS_MP4")
endif()

if(TAGLIB_WITH_MP4_COVERART)
    list(APPEND luataglib_sources "csrc/mp4/mp4coverart.cpp")
    source_compile_def("csrc/mp4/mp4.cpp" "LTAGLIB_HAS_MP4_COVERART")
    source_compile_def("csrc/mp4/mp4item.cpp" "LTAGLIB_HAS_MP4_COVERART")
endif()

if(TAGLIB_WITH_RIFF)
    list(APPEND luataglib_sources "csrc/riff/riff.cpp")
    list(APPEND luataglib_sources "csrc/riff/aiff/aiff.cpp")
    list(APPEND luataglib_sources "csrc/riff/aiff/aifffile.cpp")
    list(APPEND luataglib_sources "csrc/riff/aiff/aiffproperties.cpp")
    list(APPEND luataglib_sources "csrc/riff/wav/wav.cpp")
    list(APPEND luataglib_sources "csrc/riff/wav/wavfile.cpp")
    list(APPEND luataglib_sources "csrc/riff/wav/wavproperties.cpp")

    list(APPEND luataglib_iostream_sources "csrc/riff/wav/wavfile.cpp")
    list(APPEND luataglib_iostream_sources "csrc/riff/aiff/aifffile.cpp")

    source_compile_def("csrc/taglib.cpp" "LTAGLIB_HAS_RIFF")
endif()

if(TAGLIB_WITH_RIFF_INFO)
    list(APPEND luataglib_sources "csrc/riff/info/info.cpp")
    list(APPEND luataglib_sources "csrc/riff/info/infotag.cpp")

    source_compile_def("csrc/riff/riff.cpp" "LTAGLIB_HAS_RIFF_INFO")
    source_compile_def("csrc/riff/wav/wavfile.cpp" "LTAGLIB_HAS_RIFF_INFO")
endif()

if(TAGLIB_WITH_TRUEAUDIO)
    list(APPEND luataglib_sources "csrc/trueaudio/trueaudio.cpp")
    list(APPEND luataglib_sources "csrc/trueaudio/trueaudiofile.cpp")
    list(APPEND luataglib_sources "csrc/trueaudio/trueaudioproperties.cpp")

    list(APPEND luataglib_iostream_sources "csrc/trueaudio/trueaudiofile.cpp")

    source_compile_def("csrc/taglib.cpp" "LTAGLIB_HAS_TRUEAUDIO")
endif()

if(TAGLIB_WITH_VORBIS)
    list(APPEND luataglib_sources "csrc/flac/flac.cpp")
    list(APPEND luataglib_sources "csrc/flac/flacfile.cpp")
    list(APPEND luataglib_sources "csrc/flac/flacproperties.cpp")
    list(APPEND luataglib_sources "csrc/ogg/ogg.cpp")
    list(APPEND luataglib_sources "csrc/ogg/oggfile.cpp")
    list(APPEND luataglib_sources "csrc/ogg/oggpage.cpp")
    list(APPEND luataglib_sources "csrc/ogg/oggpageheader.cpp")
    list(APPEND luataglib_sources "csrc/ogg/xiphcomment.cpp")
    list(APPEND luataglib_sources "csrc/ogg/vorbis/vorbis.cpp")
    list(APPEND luataglib_sources "csrc/ogg/vorbis/vorbisfile.cpp")
    list(APPEND luataglib_sources "csrc/ogg/vorbis/vorbisproperties.cpp")
    list(APPEND luataglib_sources "csrc/vorbis/vorbis.cpp")

    list(APPEND luataglib_iostream_sources "csrc/flac/flacfile.cpp")
    list(APPEND luataglib_iostream_sources "csrc/ogg/vorbis/vorbisfile.cpp")

    source_compile_def("csrc/taglib.cpp" "LTAGLIB_HAS_FLAC")
    source_compile_def("csrc/taglib.cpp" "LTAGLIB_HAS_OGG")
    source_compile_def("csrc/taglib.cpp" "LTAGLIB_HAS_VORBIS")
endif()

if(TAGLIB_WITH_FLAC_PICTURE)
    list(APPEND luataglib_sources "csrc/flac/flacpicture.cpp")

    source_compile_def("csrc/flac/flacfile.cpp" "LTAGLIB_HAS_FLAC_PICTURE")
    source_compile_def("csrc/flac/flac.cpp" "LTAGLIB_HAS_FLAC_PICTURE")
    source_compile_def("csrc/ogg/xiphcomment.cpp" "LTAGLIB_HAS_FLAC_PICTURE")
endif()

if(TAGLIB_WITH_OGG_FLAC)
    list(APPEND luataglib_sources "csrc/ogg/flac/oggflac.cpp")
    list(APPEND luataglib_sources "csrc/ogg/flac/oggflacfile.cpp")

    list(APPEND luataglib_iostream_sources "csrc/ogg/flac/oggflacfile.cpp")

    source_compile_def("csrc/ogg/ogg.cpp" LTAGLIB_HAS_OGG_FLAC)
endif()

if(TAGLIB_WITH_FLAC_METADATABLOCK)
    list(APPEND luataglib_sources "csrc/flac/flacmetadatablock.cpp")

    source_compile_def("csrc/flac/flac.cpp" LTAGLIB_HAS_FLAC_METADATABLOCK)
endif()

if(TAGLIB_WITH_SPEEX)
    list(APPEND luataglib_sources "csrc/ogg/speex/speex.cpp")
    list(APPEND luataglib_sources "csrc/ogg/speex/speexfile.cpp")
    list(APPEND luataglib_sources "csrc/ogg/speex/speexproperties.cpp")

    list(APPEND luataglib_iostream_sources "csrc/ogg/speex/speexfile.cpp")

    source_compile_def("csrc/ogg/ogg.cpp" LTAGLIB_HAS_SPEEX)
endif()

if(TAGLIB_WITH_OPUS)
    list(APPEND luataglib_sources "csrc/ogg/opus/opus.cpp")
    list(APPEND luataglib_sources "csrc/ogg/opus/opusfile.cpp")
    list(APPEND luataglib_sources "csrc/ogg/opus/opusproperties.cpp")

    list(APPEND luataglib_iostream_sources "csrc/ogg/opus/opusfile.cpp")

    source_compile_def("csrc/ogg/ogg.cpp" LTAGLIB_HAS_OPUS)
endif()

list(APPEND luataglib_sources "csrc/id3v1/id3v1.cpp")
list(APPEND luataglib_sources "csrc/id3v1/id3v1tag.cpp")
list(APPEND luataglib_sources "csrc/id3v2/commentsframe.cpp")
list(APPEND luataglib_sources "csrc/id3v2/id3v2.cpp")
list(APPEND luataglib_sources "csrc/id3v2/id3v2extendedheader.cpp")
list(APPEND luataglib_sources "csrc/id3v2/id3v2footer.cpp")
list(APPEND luataglib_sources "csrc/id3v2/id3v2header.cpp")
list(APPEND luataglib_sources "csrc/id3v2/id3v2tag.cpp")
list(APPEND luataglib_sources "csrc/id3v2/id3v2frame.cpp")
list(APPEND luataglib_sources "csrc/id3v2/textidentificationframe.cpp")
list(APPEND luataglib_sources "csrc/id3v2/unknownframe.cpp")

if(TAGLIB_WITH_ID3V2_ATTACHEDPICTUREFRAME)
    list(APPEND luataglib_sources "csrc/id3v2/attachedpictureframe.cpp")
    list(APPEND luataglib_id3v2_definitions "LTAGLIB_HAS_ATTACHEDPICTUREFRAME=1")
endif()

if(TAGLIB_WITH_ID3V2_CHAPTERFRAME)
    list(APPEND luataglib_sources "csrc/id3v2/chapterframe.cpp")
    list(APPEND luataglib_id3v2_definitions "LTAGLIB_HAS_CHAPTERFRAME=1")
endif()

if(TAGLIB_WITH_ID3V2_EVENTTIMINGCODESFRAME)
    list(APPEND luataglib_sources "csrc/id3v2/eventtimingcodesframe.cpp")
    list(APPEND luataglib_id3v2_definitions "LTAGLIB_HAS_EVENTTIMINGCODESFRAME=1")
endif()

if(TAGLIB_WITH_ID3V2_GENERALENCAPSULATEDOBJECTFRAME)
    list(APPEND luataglib_sources "csrc/id3v2/generalencapsulatedobjectframe.cpp")
    list(APPEND luataglib_id3v2_definitions "LTAGLIB_HAS_GENERALENCAPSULATEDOBJECTFRAME=1")
endif()

if(TAGLIB_WITH_ID3V2_OWNERSHIPFRAME)
    list(APPEND luataglib_sources "csrc/id3v2/ownershipframe.cpp")
    list(APPEND luataglib_id3v2_definitions "LTAGLIB_HAS_OWNERSHIPFRAME=1")
endif()

if(TAGLIB_WITH_ID3V2_PODCASTFRAME)
    list(APPEND luataglib_sources "csrc/id3v2/podcastframe.cpp")
    list(APPEND luataglib_id3v2_definitions "LTAGLIB_HAS_PODCASTFRAME=1")
endif()

if(TAGLIB_WITH_ID3V2_POPULARIMETERFRAME)
    list(APPEND luataglib_sources "csrc/id3v2/popularimeterframe.cpp")
    list(APPEND luataglib_id3v2_definitions "LTAGLIB_HAS_POPULARIMETERFRAME=1")
endif()

if(TAGLIB_WITH_ID3V2_PRIVATEFRAME)
    list(APPEND luataglib_sources "csrc/id3v2/privateframe.cpp")
    list(APPEND luataglib_id3v2_definitions "LTAGLIB_HAS_PRIVATEFRAME=1")
endif()

if(TAGLIB_WITH_ID3V2_RELATIVEVOLUMEFRAME)
    list(APPEND luataglib_sources "csrc/id3v2/relativevolumeframe.cpp")
    list(APPEND luataglib_id3v2_definitions "LTAGLIB_HAS_RELATIVEVOLUMEFRAME=1")
endif()

if(TAGLIB_WITH_ID3V2_SYNCHRONIZEDLYRICSFRAME)
    list(APPEND luataglib_sources "csrc/id3v2/synchronizedlyricsframe.cpp")
    list(APPEND luataglib_id3v2_definitions "LTAGLIB_HAS_SYNCHRONIZEDLYRICSFRAME=1")
endif()

if(TAGLIB_WITH_ID3V2_TABLEOFCONTENTSFRAME)
    list(APPEND luataglib_sources "csrc/id3v2/tableofcontentsframe.cpp")
    list(APPEND luataglib_id3v2_definitions "LTAGLIB_HAS_TABLEOFCONTENTSFRAME=1")
endif()

if(TAGLIB_WITH_ID3V2_USERTEXTIDENTIFICATIONFRAME)
    set_source_files_properties("csrc/id3v2/textidentificationframe.cpp"
        PROPERTIES COMPILE_DEFINITIONS "LTAGLIB_HAS_USERTEXTIDENTIFICATIONFRAME=1")
    list(APPEND luataglib_id3v2_definitions "LTAGLIB_HAS_USERTEXTIDENTIFICATIONFRAME=1")
endif()

if(TAGLIB_WITH_ID3V2_UNIQUEFILEIDENTIFIERFRAME)
    list(APPEND luataglib_sources "csrc/id3v2/uniquefileidentifierframe.cpp")
    list(APPEND luataglib_id3v2_definitions "LTAGLIB_HAS_UNIQUEFILEIDENTIFIERFRAME=1")
endif()

if(TAGLIB_WITH_ID3V2_UNSYNCHRONIZEDLYRICSFRAME)
    list(APPEND luataglib_sources "csrc/id3v2/unsynchronizedlyricsframe.cpp")
    list(APPEND luataglib_id3v2_definitions "LTAGLIB_HAS_UNSYNCHRONIZEDLYRICSFRAME=1")
endif()

if(TAGLIB_WITH_ID3V2_URLLINKFRAME)
    list(APPEND luataglib_sources "csrc/id3v2/urllinkframe.cpp")
    list(APPEND luataglib_id3v2_definitions "LTAGLIB_HAS_URLLINKFRAME=1")
endif()

set_source_files_properties("csrc/id3v2/id3v2.cpp"
    PROPERTIES COMPILE_DEFINITIONS "${luataglib_id3v2_definitions}")

list(APPEND luataglib_sources "csrc/mpeg/mpeg.cpp")
list(APPEND luataglib_sources "csrc/mpeg/mpegfile.cpp")
list(APPEND luataglib_sources "csrc/mpeg/mpegheader.cpp")
list(APPEND luataglib_sources "csrc/mpeg/mpegproperties.cpp")
list(APPEND luataglib_sources "csrc/mpeg/xingheader.cpp")

list(APPEND luataglib_iostream_sources "csrc/mpeg/mpegfile.cpp")

if(TAGLIB_WITH_IOSTREAM)
    list(APPEND luataglib_sources "csrc/tiostream.cpp")
    foreach(f ${luataglib_iostream_sources})
        source_compile_def(${f} "LTAGLIB_HAS_IOSTREAM")
    endforeach()
endif()

if(TAGLIB_WITH_BYTEVECTORSTREAM)
    list(APPEND luataglib_sources "csrc/tbytevectorstream.cpp")
    source_compile_def("csrc/taglib.cpp" "LTAGLIB_HAS_BYTEVECTORSTREAM")
endif()

if(TAGLIB_WITH_FILESTREAM)
    list(APPEND luataglib_sources "csrc/tfilestream.cpp")
    source_compile_def("csrc/taglib.cpp" "LTAGLIB_HAS_FILESTREAM")
endif()

if(TAGLIB_WITH_PROPERTYMAP)
    list(APPEND luataglib_sources "csrc/tpropertymap.cpp")
    source_compile_def("csrc/taglib.cpp" "LTAGLIB_HAS_PROPERTYMAP")
    source_compile_def("csrc/tfile.cpp" "LTAGLIB_HAS_PROPERTYMAP")
    source_compile_def("csrc/tag.cpp" "LTAGLIB_HAS_PROPERTYMAP")
    source_compile_def("csrc/id3v2/textidentificationframe.cpp" "LTAGLIB_HAS_PROPERTYMAP")
    source_compile_def("csrc/id3v2/commentsframe.cpp" "LTAGLIB_HAS_PROPERTYMAP")
    if(TAGLIB_WITH_DSF)
        source_compile_def("csrc/dsf/dsffile.cpp" "LTAGLIB_HAS_PROPERTYMAP")
        source_compile_def("csrc/dsdiff/dsdifffile.cpp" "LTAGLIB_HAS_PROPERTYMAP")
    endif()

    if(TAGLIB_WITH_ID3V2_CHAPTERFRAME)
        source_compile_def("csrc/id3v2/chapterframe.cpp" "LTAGLIB_HAS_PROPERTYMAP")
    endif()

    if(TAGLIB_WITH_ID3V2_PODCASTFRAME)
        source_compile_def("csrc/id3v2/podcastframe.cpp" "LTAGLIB_HAS_PROPERTYMAP")
    endif()

    if(TAGLIB_WITH_ID3V2_TABLEOFCONTENTSFRAME)
        source_compile_def("csrc/id3v2/tableofcontentsframe.cpp" "LTAGLIB_HAS_PROPERTYMAP")
    endif()

    if(TAGLIB_WITH_ID3V2_UNIQUEFILEIDENTIFIERFRAME)
        source_compile_def("csrc/id3v2/uniquefileidentifierframe.cpp" "LTAGLIB_HAS_PROPERTYMAP")
    endif()

    if(TAGLIB_WITH_ID3V2_UNSYNCHRONIZEDLYRICSFRAME)
        source_compile_def("csrc/id3v2/unsynchronizedlyricsframe.cpp" "LTAGLIB_HAS_PROPERTYMAP")
    endif()
    
    if(TAGLIB_WITH_ID3V2_URLLINKFRAME)
        source_compile_def("csrc/id3v2/urllinkframe.cpp" "LTAGLIB_HAS_PROPERTYMAP")
    endif()
endif()

if(TAGLIB_WITH_VARIANT)
    list(APPEND luataglib_sources "csrc/tvariant.cpp")
    source_compile_def("csrc/tag.cpp" "LTAGLIB_HAS_VARIANT")
    source_compile_def("csrc/taglib.cpp" "LTAGLIB_HAS_VARIANT")
    source_compile_def("csrc/tfile.cpp" "LTAGLIB_HAS_VARIANT")
endif()

add_library(LuaTagLib SHARED ${luataglib_sources})

if(WIN32)
    target_link_libraries(LuaTagLib PRIVATE ${LUA_LIBRARIES})
endif()

target_include_directories(LuaTagLib PRIVATE ${LUA_INCLUDE_DIR})
target_link_libraries(LuaTagLib PRIVATE TagLib::TagLib)
target_compile_definitions(LuaTagLib PRIVATE "TAGLIB_VERSION_MAJOR=${TAGLIB_VERSION_MAJOR};TAGLIB_VERSION_MINOR=${TAGLIB_VERSION_MINOR};TAGLIB_VERSION_PATCH=${TAGLIB_VERSION_PATCH}")

if(TAGLIB_VERSION VERSION_GREATER_EQUAL 2.0.0)
    set_property(TARGET LuaTagLib PROPERTY CXX_STANDARD 17)
else()
    set_property(TARGET LuaTagLib PROPERTY CXX_STANDARD 11)
endif()

if(APPLE)
    target_link_options(LuaTagLib PRIVATE "-undefined dynamic_lookup")
    set_target_properties(LuaTagLib PROPERTIES SUFFIX ".so")
endif()

set_target_properties(LuaTagLib PROPERTIES PREFIX "" OUTPUT_NAME "TagLib" POSITION_INDEPENDENT_CODE ON CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS OFF)
set_target_properties(LuaTagLib PROPERTIES C_VISIBILITY_PRESET hidden CXX_VISIBILITY_PRESET hidden)

if(LTO_SUPPORTED)
    set_property(TARGET LuaTagLib PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(LuaTagLib PRIVATE "-Wall")
    target_compile_options(LuaTagLib PRIVATE "-Wextra")
    target_compile_options(LuaTagLib PRIVATE "-Wcast-align")
endif()

if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    target_compile_options(LuaTagLib PRIVATE "-Wall")
    target_compile_options(LuaTagLib PRIVATE "-Wextra")
endif()

install(TARGETS LuaTagLib
  LIBRARY DESTINATION "${CMODULE_INSTALL_DIR}"
  RUNTIME DESTINATION "${CMODULE_INSTALL_DIR}"
  ARCHIVE DESTINATION "${CMODULE_INSTALL_DIR}"
)

