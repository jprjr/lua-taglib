function(SOURCE_COMPILE_DEF FILE DEF)
  get_source_file_property(TMP_DEFINES ${FILE}
    COMPILE_DEFINITIONS)
  if(TMP_DEFINES STREQUAL "NOTFOUND")
      unset(TMP_DEFINES)
      set(TMP_DEFINES)
  endif()
  list(APPEND TMP_DEFINES "${DEF}=1")
  set_source_files_properties(${FILE}
    PROPERTIES COMPILE_DEFINITIONS "${TMP_DEFINES}")
  unset(TMP_DEFINES)
endfunction()
