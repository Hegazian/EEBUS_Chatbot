set(keo_target_util "keo_util")
set(keo_target_util_additional_dox_files "")

set(DOXYGEN_STRIP_FROM_INC_PATH "${DOXYGEN_STRIP_FROM_INC_PATH} ${CMAKE_CURRENT_LIST_DIR}/include")

set(DOXYGEN_INPUT "${DOXYGEN_INPUT} ${CMAKE_CURRENT_LIST_DIR}/doc/modules.dox")

keo_library(
  LIBRARY_NAME ${keo_target_util}

  LIBRARY_TYPE SHARED

  EXPORT_NAME  ${targets_export_name}

  LIST_SRC
  ${CMAKE_CURRENT_LIST_DIR}/INIReader/ini.c
  ${CMAKE_CURRENT_LIST_DIR}/src/KETimer_posix.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/KEVersion.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/KEIniReader.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/KELogger.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/KELoggerConsoleConsumer.cpp


  LIST_HDR_PRIVATE

  LIST_HDR_PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/include/keo_util/KELogging.h
  ${CMAKE_CURRENT_LIST_DIR}/include/keo_util/KELogger.h
  ${CMAKE_CURRENT_LIST_DIR}/include/keo_util/KELoggerConsoleConsumer.h
  ${CMAKE_CURRENT_LIST_DIR}/include/keo_util/KETimer.h
  ${CMAKE_CURRENT_LIST_DIR}/include/keo_util/KETimer_posix.h
  ${CMAKE_CURRENT_LIST_DIR}/include/keo_util/KEVersion.h
  ${CMAKE_CURRENT_LIST_DIR}/include/keo_util/KEIniReader.h
  ${CMAKE_CURRENT_LIST_DIR}/include/keo_util/KEVersion.h

  LIST_HDR_INTERFACE

  INCLUDE_DIRECTORIES_PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/INIReader

  INCLUDE_DIRECTORIES_PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/include

  INCLUDE_DIRECTORIES_INTERFACE

  HDR_INSTALL_DIR include/keo_util

  LINK_LIBRARIES
  pthread rt

  SDK
  )

target_compile_definitions(${keo_target_util} PRIVATE LOGGER_ID="keo_util")

if (NOT KEO_SRC) # already generated in src package
  add_dependencies(${keo_target_util} ${KEO_PROJECT_PROJECT_NAME}versionfile)
endif()


if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" AND NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 8.0.0)
    set_source_files_properties(
      ${CMAKE_CURRENT_LIST_DIR}/src/KELoggerConsoleConsumer.cpp
      PROPERTIES COMPILE_FLAGS -Wno-error=pedantic)
endif()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" )
    set_source_files_properties(
      ${CMAKE_CURRENT_LIST_DIR}/src/KELoggerConsoleConsumer.cpp
      PROPERTIES COMPILE_FLAGS -Wno-error=c99-extensions)
endif()


# ============================================================
#
# Unit tests
#
# ============================================================

keo_googletest(
  TEST_NAME ${keo_target_util}

  LIST_SRC
  ${CMAKE_CURRENT_LIST_DIR}/tests/gtest_main.cpp
  ${CMAKE_CURRENT_LIST_DIR}/tests/KETimerTest.cpp
  ${CMAKE_CURRENT_LIST_DIR}/tests/KEVersionTest.cpp
  ${CMAKE_CURRENT_LIST_DIR}/tests/KELoggerTest.cpp

  LINK_LIBRARIES
  ${keo_target_util}

  )
