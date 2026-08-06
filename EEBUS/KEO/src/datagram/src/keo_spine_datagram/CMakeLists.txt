

# set databinder output directory
if ( NOT GENERATED_SPINE_DIR )
  set(GENERATED_SPINE_DIR   "${CMAKE_CURRENT_BINARY_DIR}/GeneratedSpine")
endif()

# ======================================================================================================
#
# Required packages
#
# ======================================================================================================

# find databinder if not build as source package

if (NOT KEO_SRC)

  # prepare renaming the databinder
  if ((NOT DATABINDER_ROOT) AND KEO_SPINE_DATABINDER_ROOT)
    set(DATABINDER_ROOT ${KEO_SPINE_DATABINDER_ROOT})
  endif()

  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR}/cmake)

  find_package(SpinePythonDataBinder)
  if( NOT DATABINDER_FOUND)
    message(FATAL_ERROR "DataBinding not found. Try to set DATABINDER_ROOT.")
  endif()
else()
  file(STRINGS ${GENERATED_SPINE_DIR}/GeneratedSrc.txt SPINE_GENERATED_SOURCE_FILES)
  file(STRINGS ${GENERATED_SPINE_DIR}/GeneratedProtectedHeader.txt SPINE_GENERATED_PROTECTED_HEADER_FILES)
  file(STRINGS ${GENERATED_SPINE_DIR}/GeneratedHeader.txt SPINE_GENERATED_HEADER_FILES)
endif()

if (NOT SPINE_XSD_DIRECTORY)
    set(SPINE_XSD_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/xsd")
endif()

message(STATUS "SPINE_XSD_DIRECTORY is ${SPINE_XSD_DIRECTORY}")


# ------------------------------------------------------------------------------------------------------
#
# SPINE Databinder configuration
#
# ------------------------------------------------------------------------------------------------------

set(GENERATED_DIR ${GENERATED_SPINE_DIR})
if (NOT KEO_SRC)
  include(${CMAKE_CURRENT_LIST_DIR}/cmake/RunDatabinder.cmake)
endif()

option(CREATE_DEV_PACKAGE "Create package for development (includes documentation, headers and static libraries)" ON)

include(CMakeDependentOption)
CMAKE_DEPENDENT_OPTION(INSTALL_HELPER_LIBS "Install GenerateUtilitiesLibrary and TestUtilities library" ON
  "CREATE_DEV_PACKAGE" OFF)


# ======================================================================================================
#
# SPINE Datagram library
#
# ======================================================================================================


# Target definition

set (GENERATOR "Eclipse CDT4 - Unix Makefiles")

set(GENERATED_BUILD_DIR   "${CMAKE_CURRENT_BINARY_DIR}/buildGeneratedSpine")
set(GENERATED_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/installGeneratedSpine")

include (ExternalProject)

if (NOT KEO_SRC)
  set(DEPENDS_ON RunSpineDataBinder ${CMAKE_PROJECT_NAME}versionfile)
endif()

ExternalProject_Add(BuildDatagramLibrary
  PREFIX                ${GENERATED_BUILD_DIR}
  DEPENDS               ${DEPENDS_ON}
  TMP_DIR               ${GENERATED_BUILD_DIR}
  STAMP_DIR             ${GENERATED_BUILD_DIR}/buildlogs
  SOURCE_DIR            ${GENERATED_DIR}
  BINARY_DIR            ${GENERATED_BUILD_DIR}
  DOWNLOAD_COMMAND      ""
  UPDATE_COMMAND        ""
  CMAKE_ARGS            "-DKEO_CPACK_NO_DEFAULT_COMPONENTS=ON"
                        "-DKEO_CUSTOM_CPACK=${KEO_CUSTOM_CPACK}"
                        "-DCMAKE_INSTALL_PREFIX=${GENERATED_INSTALL_DIR}"
                        "-DKEO_CMAKE_MODULE_PATH=${KEO_CMAKE_MODULE_PATH}"
                        "-DCMAKE_NON_GEN_BASE_PATH=${CMAKE_CURRENT_LIST_DIR}"
                        "-DSPINE_VERSION_INCLUDE=${GENERATED_INCLUDE_DIR}"
                        "-DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}"
                        "-DKEO_TOOLCHAIN_NAME=${KEO_TOOLCHAIN_NAME}"
                        "-DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}"
                        "-DBS_VERSION_MAJOR=${BS_VERSION_MAJOR}"
                        "-DBS_VERSION_MINOR=${BS_VERSION_MINOR}"
                        "-DBS_VERSION_REVISION=${BS_VERSION_REVISION}"
                        "-DBS_SPINE_VERSION_MAJOR=${BS_SPINE_VERSION_MAJOR}"
                        "-DBS_SPINE_VERSION_MINOR=${BS_SPINE_VERSION_MINOR}"
                        "-DBS_SPINE_VERSION_REVISION=${BS_SPINE_VERSION_REVISION}"
                        "-DBS_SPINE_VERSION_POSTFIX=${BS_SPINE_VERSION_POSTFIX}"
                        "-DCREATE_DOC=${CREATE_DOC}"
                        "-DKEO_SRC=${KEO_SRC}"

  CMAKE_GENERATOR       ${GENERATOR}
  LOG_DOWNLOAD  1
  LOG_UPDATE    1
  LOG_CONFIGURE 1
  LOG_BUILD     1
  LOG_TEST      1
  LOG_INSTALL   1
  )


include (${CMAKE_CURRENT_LIST_DIR}/SpineDatagramDeserializer/CMakeLists.txt)
include (${CMAKE_CURRENT_LIST_DIR}/SpineDatagramLibrary/tests/CMakeLists.txt)

if(${TOOLCHAIN_ARCHITECTURE} STREQUAL "amd64")
    include (${CMAKE_CURRENT_LIST_DIR}/test/CMakeLists.txt)
else()
    MESSAGE(STATUS "Not executing datagram tests.")
endif()

install(DIRECTORY
  ${GENERATED_INSTALL_DIR}/
  DESTINATION .
  USE_SOURCE_PERMISSIONS
  COMPONENT ${CPACK_COMPONENT_DEV_GROUP}
  PATTERN doc EXCLUDE
  )

install(
  FILES       ${GENERATED_SPINE_DIR}/SpineXsd.json ${GENERATED_SPINE_DIR}/KeoSpineClasses.json
  DESTINATION generated
  COMPONENT   ${CPACK_COMPONENT_DEV_GROUP}
  )

# misc generated files
install(DIRECTORY
  ${CMAKE_CURRENT_BINARY_DIR}/include
  DESTINATION generated
  USE_SOURCE_PERMISSIONS
  COMPONENT ${CPACK_COMPONENT_SRC_GROUP}
  )


if (CREATE_DOC)
  add_custom_target(doc)    # add empty target doc to support 'make doc' command
  install(DIRECTORY
    ${GENERATED_INSTALL_DIR}/doc
    DESTINATION .
    USE_SOURCE_PERMISSIONS
    COMPONENT ${CPACK_COMPONENT_DOC_GROUP}
    )
endif()
