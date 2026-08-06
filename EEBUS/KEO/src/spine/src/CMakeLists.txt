cmake_minimum_required(VERSION 3.9)

include(GenerateExportHeader)

# ============================================================
#
# Package
#
# ============================================================

# no default package
set(KEO_CPACK_NO_DEFAULT_COMPONENTS)

# add project defined packages
set(KEO_CUSTOM_CPACK "${CMAKE_CURRENT_LIST_DIR}/cpack/keo_custom_cpack.cmake")


# ============================================================
#
# Debug
#
# ============================================================

option(GENERATE_CMAKE_DEBUG "Create cmake debug output" OFF)
if(GENERATE_CMAKE_DEBUG)
set(CMAKE_DEBUG_TARGET_PROPERTIES
  INCLUDE_DIRECTORIES
  COMPILE_DEFINITIONS
  POSITION_INDEPENDENT_CODE
  CONTAINER_SIZE_REQUIRED
  LIB_VERSION
)
endif(GENERATE_CMAKE_DEBUG)

# ============================================================
#
# Global settings
#
# ============================================================

option(CREATE_KEO_EXAMPLE "Create KEO example application(s)" ON)

if (CREATE_KEO_EXAMPLE)
    if (DATABINDING_FILTER_CONFIG)
      set(build_examples    False)
      message (STATUS "Reduced Datagram Library is configured: Disable build of all examples!")
    else()
      set(build_examples    True)
      message (STATUS "Create KEO example application(s) is enabled.")
    endif()
else()
    message (STATUS "Create KEO example application(s) is disabled.")
    set(build_examples    False)
endif()



# Set cmake module path
set(CMAKE_MODULE_PATH  "${PROJECT_SOURCE_DIR}/cmakemodules")

# If KEO_CMAKE_MODULES_ROOT is set on the command line or in the environment use it with LOWER priority

if (DEFINED KEO_CMAKE_MODULES_ROOT)
  set(KEO_CMAKE_MODULE_PATH ${KEO_CMAKE_MODULES_ROOT})
elseif (NOT $ENV{KEO_CMAKE_MODULES_ROOT} STREQUAL "")
  set(KEO_CMAKE_MODULE_PATH "$ENV{KEO_CMAKE_MODULES_ROOT}")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${KEO_CMAKE_MODULE_PATH})

# ============================================================
#
# Project settings
#
# ============================================================

include(KEOProject)

keo_project(
    PROJECT_NAME  keo_spine
    VERSION_MAJOR ${BS_VERSION_MAJOR}
    VERSION_MINOR ${BS_VERSION_MINOR}
    BUILD_VERSION ${BS_VERSION_REVISION}
)

export(PACKAGE keospine)

if ( NOT GENERATED_INCLUDE_DIR )
  set(GENERATED_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/include")
endif()
include_directories(${GENERATED_INCLUDE_DIR})

# ============================================================
#
# Required packages
#
# ============================================================

# Find avahi
find_package(Avahi)
if(NOT AVAHI_FOUND)
    message(WARNING "***********************************************************************")
    message(WARNING "* Avahi NOT found!                                                    *")
    message(WARNING "* Building WITHOUT keo_ship_discovery and keo_default_ship_transport! *")
    message(WARNING "***********************************************************************")
endif (NOT AVAHI_FOUND)


# Find plantuml
option(CREATE_PLANTUML "Create plantuml images" OFF)

option(CREATE_DOC "Create Doxygen Documentation" ON)
if(CREATE_DOC)
  set(DOXYGEN_INPUT "")
  find_package(Doxygen REQUIRED)

  if(CREATE_PLANTUML)
    find_program(JAVA "java")
    if(JAVA)
      message("-- java detected: ${JAVA}")
      find_program(
        PLANTUML_JAR
        NAMES plantuml.jar
        PATHS /usr/local/bin /usr/local/share/plantuml /usr/share/plantuml
        )
      if(PLANTUML_JAR)
        message("-- plantuml detected: ${PLANTUML_JAR}")
        set (PLANTUML_SOURCES "")
        set (PLANTUML_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/doc/images")
      else(PLANTUML_JAR)
        message(FATAL_ERROR "-- plantuml not found. Cannot create plantuml images")
      endif(PLANTUML_JAR)
    else(JAVA)
      message(FATAL_ERROR "-- java not found. Cannot create plantuml images")
    endif(JAVA)
  endif(CREATE_PLANTUML)
endif(CREATE_DOC)

option(CREATE_GOOGLETEST "Create Unit Tests" ON)

if ((NOT KEO_SRC) AND CREATE_GOOGLETEST)

  include(googletest)

else()

  # Dummy: Unit testing is not supported in the source package
  macro(keo_googletest)
  endmacro(keo_googletest)

endif()

option(CREATE_DOCKER "Create docker images" OFF)

if (NOT KEO_SRC)
  install(DIRECTORY
    ${KEO_SPINE_DATAGRAM_ROOT}/include
    ${KEO_SPINE_DATAGRAM_ROOT}/lib
    ${KEO_SPINE_DATAGRAM_ROOT}/generated
    DESTINATION .
    USE_SOURCE_PERMISSIONS
    COMPONENT ${CPACK_COMPONENT_DEV_GROUP}
  )

  install(DIRECTORY
    ${KEO_SPINE_DATAGRAM_ROOT}/lib
    DESTINATION .
    USE_SOURCE_PERMISSIONS
    COMPONENT ${CPACK_COMPONENT_BIN_GROUP}
  )
endif ()

# ============================================================
#
# libraries
#
# ============================================================

include(${CMAKE_CURRENT_LIST_DIR}/keo_util/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/keo_tool/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/keo_ship_stack/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/keo_spine/CMakeLists.txt)

# ============================================================
#
# commons
#
# ============================================================

include(${CMAKE_CURRENT_LIST_DIR}/commons/keo_spine_connector/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/commons/security/CMakeLists.txt)

# ============================================================
#
# examples
#
# ============================================================



  option(INSTALL_EXAMPLE_SECURITY_SOURCES "Install the source code of the example security handler" OFF)
  option(INSTALL_SHIP_EXAMPLE_SOURCES     "Install the source code of the ship example"             OFF)

  include(${CMAKE_CURRENT_LIST_DIR}/examples/CMakeLists.txt)



# ============================================================
#
# Doxygen Documentation
#
# ============================================================

if (DOXYGEN_FOUND AND CREATE_DOC)

  # GeneratePlantUml target. Generates images

  if(CREATE_PLANTUML AND JAVA AND PLANTUML_JAR)
    add_custom_target(GeneratePlantUml ALL
      COMMAND ${JAVA} -jar ${PLANTUML_JAR} ${PLANTUML_SOURCES} -o ${PLANTUML_OUTPUT_DIR}
      DEPENDS ${PLANTUML_SOURCES}
      COMMENT "Generating plantuml images")
  endif(CREATE_PLANTUML AND JAVA AND PLANTUML_JAR)

  # name settings
  set(DOXYGEN_PROJECT_NAME "KEO SPINE")
  set(DOXYGEN_PROJECT_VERSION "${${PROJECT_NAME}_RELEASE_POSTFIX}")

  # set revision
  set(DOXYGEN_REVISION "")

  # Set logo
  set(DOXYGEN_IMAGE_PATH "${CMAKE_CURRENT_BINARY_DIR}/doc/images")
  set(DOXYGEN_PROJECT_LOGO "${DOXYGEN_IMAGE_PATH}/KEO_Logo.png")
  configure_file(${PROJECT_SOURCE_DIR}/doc/KEO_Logo.png ${DOXYGEN_IMAGE_PATH}/KEO_Logo.png COPYONLY)

  # mainpage
  configure_file(${PROJECT_SOURCE_DIR}/doc/mainpage.md.in ${CMAKE_CURRENT_BINARY_DIR}/doc/mainpage.md)
  set(DOXYGEN_INPUT ${DOXYGEN_INPUT} ${CMAKE_CURRENT_BINARY_DIR}/doc/mainpage.md)

  # common pages
  set(DOXYGEN_MARK_DOWN_PAGES_SOURCES
    ${PROJECT_SOURCE_DIR}/doc/getting-started.md
    ${PROJECT_SOURCE_DIR}/doc/installation.md
    ${PROJECT_SOURCE_DIR}/doc/license.md
    ${PROJECT_SOURCE_DIR}/doc/howto.md
    )

  set(DOXYGEN_EXCLUDE_PATTERN ${DOXYGEN_EXCLUDE_PATTERN} "*/tests/*")
  set(DOXYGEN_INPUT ${DOXYGEN_INPUT} ${keo_target_ship_stack_additional_dox_files})
  set(DOXYGEN_INPUT ${DOXYGEN_INPUT} ${keo_target_framework_additional_dox_files})
  set(DOXYGEN_INPUT ${DOXYGEN_INPUT} ${keo_target_util_additional_dox_files})
  set(DOXYGEN_INPUT ${DOXYGEN_INPUT} ${keo_examples_additional_dox_files})
  set(DOXYGEN_INPUT ${DOXYGEN_INPUT} ${keo_target_spine_datagram_additional_dox_files})

  string (REPLACE ";" " " DOXYGEN_INPUT_STR "${DOXYGEN_INPUT}")
  set(DOXYGEN_INPUT "${DOXYGEN_INPUT_STR}")

  string (REPLACE ";" " " DOXYGEN_STRIP_FROM_INC_PATH_STR "${DOXYGEN_STRIP_FROM_INC_PATH}")
  set(DOXYGEN_STRIP_FROM_INC_PATH ${DOXYGEN_STRIP_FROM_INC_PATH_STR})


  string (REPLACE ";" " " DOXYGEN_EXCLUDE_STR "${DOXYGEN_EXCLUDE}")
  set(DOXYGEN_EXCLUDE "${DOXYGEN_EXCLUDE_STR}")


  message(INFO "DOXYGEN_INPUT ${DOXYGEN_INPUT}")
  set(DOXYGEN_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/doc)

  set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN doc)

  # find Umlet
  find_package(Umlet)

  if(NOT UMLET_FOUND)
    message(FATAL_ERROR "Umlet not found!")
  endif()

  keo_convertUmlet(
    INPUT_FILES ${CMAKE_CURRENT_LIST_DIR}/doc/SPINE_Link_Application.uxf
    OUT_DIR ${DOXYGEN_IMAGE_PATH}
    FORMAT "svg"
    )

  # This line MUST occur AFTER the last add_subdirectory
  configure_file("${PROJECT_SOURCE_DIR}/doc/Template.doxyfile" "${PROJECT_BINARY_DIR}/Doxyfile.cfg")

  add_custom_target(doc ALL ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.cfg)
  add_dependencies(doc ConvertUmlet)

  if(CREATE_PLANTUML AND JAVA AND PLANTUML_JAR)
    add_dependencies(doc GeneratePlantUml)
  endif(CREATE_PLANTUML AND JAVA AND PLANTUML_JAR)

   #  add_dependencies(all doc)
  install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc/html
    DESTINATION doc
    COMPONENT ${CPACK_COMPONENT_DOC_GROUP}
    )

endif (DOXYGEN_FOUND AND CREATE_DOC)

# ============================================================
#
# all the rest
#
# ============================================================

message(INFO "  -- KEO_CMAKE_MODULE_PATH ${KEO_CMAKE_MODULE_PATH}")

install(FILES
    ${KEO_CMAKE_MODULE_PATH}/FindAvahi.cmake
    DESTINATION cmakemodules
    PERMISSIONS OWNER_WRITE OWNER_READ
    GROUP_WRITE GROUP_READ
    WORLD_READ
    COMPONENT ${CPACK_COMPONENT_DEV_GROUP}
    )

install(FILES
    ${GENERATED_INCLUDE_DIR}/keo_spineVersion.h
    DESTINATION include
    PERMISSIONS OWNER_WRITE OWNER_READ GROUP_WRITE GROUP_READ WORLD_READ
    COMPONENT ${CPACK_COMPONENT_DEV_GROUP}
    )

# ============================================================
#
# source package
#
# ============================================================


if (NOT KEO_SRC) # generating src package from src package does not make sense

  # source tree, release notes and scm are private
  INSTALL(DIRECTORY
    ${CMAKE_CURRENT_LIST_DIR}/
    DESTINATION src
    USE_SOURCE_PERMISSIONS
    COMPONENT ${CPACK_COMPONENT_SRC_GROUP}
    PATTERN ReleaseNotes.txt EXCLUDE
    PATTERN ReleaseNotes_src.txt EXCLUDE
    PATTERN Readme_src.txt EXCLUDE
    PATTERN CMakeLists_src.txt EXCLUDE
    PATTERN .git EXCLUDE
    PATTERN .gitignore EXCLUDE
    PATTERN .gitmodules EXCLUDE
    PATTERN .project EXCLUDE
    PATTERN static_code_analysis.md EXCLUDE
    PATTERN sdk_doc EXCLUDE
    PATTERN CMakeLists_for_dev_package.txt EXCLUDE
    )

  set(RELEASE_NOTES ${CMAKE_CURRENT_BINARY_DIR}/ReleaseNotes_for_src_package.txt)
  file(WRITE ${RELEASE_NOTES} "source package")

  install(FILES
    Readme_src.txt
    DESTINATION .
    PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
    COMPONENT ${CPACK_COMPONENT_SRC_GROUP}
    RENAME Readme.txt
    )

  # Replace version information on copy automatically
  configure_file(CMakeLists_src.txt ${CMAKE_CURRENT_BINARY_DIR}/CMakeLists_src.txt @ONLY)

  install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/CMakeLists_src.txt
    DESTINATION .
    PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
    COMPONENT ${CPACK_COMPONENT_SRC_GROUP}
    RENAME CMakeLists.txt
    )

  install(FILES
    ${RELEASE_NOTES}
    DESTINATION src
    PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
    COMPONENT ${CPACK_COMPONENT_SRC_GROUP}
    RENAME ReleaseNotes.txt
    )

  # generated SHIP sources
  install(DIRECTORY
    ${CMAKE_CURRENT_BINARY_DIR}/GeneratedShip
    DESTINATION generated
    USE_SOURCE_PERMISSIONS
    COMPONENT ${CPACK_COMPONENT_SRC_GROUP}
    )

  # misc generated files
  install(DIRECTORY
    ${CMAKE_CURRENT_BINARY_DIR}/include
    DESTINATION generated
    USE_SOURCE_PERMISSIONS
    COMPONENT ${CPACK_COMPONENT_SRC_GROUP}
    )

  install(FILES
    ${KEO_CMAKE_MODULES_ROOT}/FindAvahi.cmake
    ${KEO_CMAKE_MODULES_ROOT}/FindKEOSpine.cmake
    ${KEO_CMAKE_MODULES_ROOT}/KEOCPack.cmake
    ${KEO_CMAKE_MODULES_ROOT}/KEOProject.cmake
    DESTINATION cmake
    PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
    COMPONENT ${CPACK_COMPONENT_SRC_GROUP}
    )

endif()

keo_install_license_txt()
keo_install_readme_md()
keo_install_release_notes()


# ============================================================
#
# SDK
#
# ============================================================
install(DIRECTORY
    ${KEO_SPINE_DATAGRAM_ROOT}/include
    ${KEO_SPINE_DATAGRAM_ROOT}/lib
    DESTINATION .
    USE_SOURCE_PERMISSIONS
    COMPONENT ${CPACK_COMPONENT_SDK_GROUP}
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/generated/keo_spineConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/generated/keo_spineConfigVersion.cmake
    PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ
    DESTINATION lib/cmake/keo_spine
    COMPONENT ${CPACK_COMPONENT_SDK_GROUP}
)

install(FILES
    ${KEO_CMAKE_MODULES_ROOT}/FindAvahi.cmake
    DESTINATION cmakemodules
    PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
    COMPONENT ${CPACK_COMPONENT_SDK_GROUP}
)
