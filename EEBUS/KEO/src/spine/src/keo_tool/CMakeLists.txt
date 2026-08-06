set(keo_target_tool "keo_tool")
set(keo_target_tool_additional_dox_files "")


set(DOXYGEN_STRIP_FROM_INC_PATH "${DOXYGEN_STRIP_FROM_INC_PATH} ${CMAKE_CURRENT_LIST_DIR}/ArgParser/include")
set(DOXYGEN_STRIP_FROM_INC_PATH "${DOXYGEN_STRIP_FROM_INC_PATH} ${CMAKE_CURRENT_LIST_DIR}/include")

set(DOXYGEN_INPUT "${DOXYGEN_INPUT} ${CMAKE_CURRENT_LIST_DIR}/doc/modules.dox")  

keo_library(
  LIBRARY_NAME ${keo_target_tool}

  LIBRARY_TYPE STATIC

  LIST_SRC
  ${CMAKE_CURRENT_LIST_DIR}/src/KEFootprint.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/KEJobRunner.cpp

  LIST_HDR_PRIVATE

  LIST_HDR_PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/include/keo_tool/KEFootprint.h
  ${CMAKE_CURRENT_LIST_DIR}/include/keo_tool/KEJobRunner.h
  ${CMAKE_CURRENT_LIST_DIR}/include/keo_tool/KESemaphore.h
  
  LIST_HDR_INTERFACE

  INCLUDE_DIRECTORIES_PRIVATE

  INCLUDE_DIRECTORIES_PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/include

  INCLUDE_DIRECTORIES_INTERFACE

  HDR_INSTALL_DIR include/keo_tool

  LINK_LIBRARIES
  ${keo_target_util}
  )

target_compile_definitions(${keo_target_tool} PRIVATE LOGGER_ID="keo_tool")

if (NOT KEO_SRC) # already generated in src package
  add_dependencies(${keo_target_tool} ${KEO_PROJECT_PROJECT_NAME}versionfile)
endif()


# ============================================================
#
# Unit tests
#
# ============================================================

keo_googletest(
  TEST_NAME ${keo_target_tool}

  LIST_SRC
  ${CMAKE_CURRENT_LIST_DIR}/tests/gtest_main.cpp
  ${CMAKE_CURRENT_LIST_DIR}/tests/KEJobRunnerTest.cpp
  LINK_LIBRARIES 
  ${keo_target_tool}
  )

