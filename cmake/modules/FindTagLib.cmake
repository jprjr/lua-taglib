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
