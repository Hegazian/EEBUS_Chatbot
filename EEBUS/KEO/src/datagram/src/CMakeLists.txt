cmake_minimum_required(VERSION 3.9)

include(GenerateExportHeader)
include(CMakePackageConfigHelpers)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${KEO_CMAKE_MODULE_PATH})

set(CMAKE_C_FLAGS_RELEASE       "${CMAKE_C_FLAGS_RELEASE}       -s")
set(CMAKE_CXX_FLAGS_RELEASE     "${CMAKE_CXX_FLAGS_RELEASE}     -s")
set(CMAKE_C_FLAGS_MINSIZE_REL   "${CMAKE_C_FLAGS_MINSIZE_REL}   -s")
set(CMAKE_CXX_FLAGS_MINSIZE_REL "${CMAKE_CXX_FLAGS_MINSIZE_REL} -s")

option(CREATE_DOC "Create Doxygen Documentation" ON)
if(CREATE_DOC)
  set(DOXYGEN_INPUT "")
  find_package(Doxygen REQUIRED)
endif()


include(KEOProject)

keo_project(
    PROJECT_NAME  keo_spine_datagram
    VERSION_MAJOR ${BS_VERSION_MAJOR}
    VERSION_MINOR ${BS_VERSION_MINOR}
    BUILD_VERSION ${BS_VERSION_REVISION}
)

set(INCLUDES_PUBLIC
)

set(INCLUDES_PRIVATE
    ${SPINE_VERSION_INCLUDE}
    ${CMAKE_CURRENT_LIST_DIR}/core/src
)

set(INCLUDES_DATAGRAM_CORE_LIBRARY
    ${CMAKE_CURRENT_LIST_DIR}/core/include
)


# libraries
include(${CMAKE_CURRENT_LIST_DIR}/actuator/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/alarm/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/bill/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/core/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/datatunneling/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/deviceconfiguration/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/devicediagnosis/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/directcontrol/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/electricalconnection/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/hvac/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/identification/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/incentivetable/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/loadcontrol/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/measurement/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/messaging/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/operatingconstraints/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/sensing/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/setpoint/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/smartenergymanagementps/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/supplycondition/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/taskmanagement/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/threshold/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/timeinformation/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/timeseries/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/timetable/CMakeLists.txt)

# ============================================================
#
# Doxygen Documentation
#
# ============================================================

if(CREATE_DOC)
  # GeneratePlantUml target. Generates images

  if(CREATE_PLANTUML AND JAVA AND PLANTUML_JAR)
    add_custom_target(GeneratePlantUml ALL
      COMMAND ${JAVA} -jar ${PLANTUML_JAR} ${PLANTUML_SOURCES} -o ${PLANTUML_OUTPUT_DIR}
      DEPENDS ${PLANTUML_SOURCES}
      COMMENT "Generating plantuml images")
  endif(CREATE_PLANTUML AND JAVA AND PLANTUML_JAR)

  # name settings
  set(DOXYGEN_PROJECT_NAME "KEO SPINE Datagram Library")
  set(DOXYGEN_PROJECT_VERSION "${${PROJECT_NAME}_RELEASE_POSTFIX}")

  # set include path
  set(DOXYGEN_STRIP_FROM_INC_PATH 
     " ${CMAKE_CURRENT_LIST_DIR} "
     " ${CMAKE_CURRENT_LIST_DIR}/actuator/include "
     " ${CMAKE_CURRENT_LIST_DIR}/alarm/include "
     " ${CMAKE_CURRENT_LIST_DIR}/bill/include "
     " ${CMAKE_CURRENT_LIST_DIR}/core/include "
     " ${CMAKE_CURRENT_LIST_DIR}/datatunneling/include "
     " ${CMAKE_CURRENT_LIST_DIR}/deviceconfiguration/include "
     " ${CMAKE_CURRENT_LIST_DIR}/devicediagnosis/include "
     " ${CMAKE_CURRENT_LIST_DIR}/directcontrol/include "
     " ${CMAKE_CURRENT_LIST_DIR}/electricalconnection/include "
     " ${CMAKE_CURRENT_LIST_DIR}/hvac/include "
     " ${CMAKE_CURRENT_LIST_DIR}/identification/include "
     " ${CMAKE_CURRENT_LIST_DIR}/incentivetable/include "
     " ${CMAKE_CURRENT_LIST_DIR}/loadcontrol/include "
     " ${CMAKE_CURRENT_LIST_DIR}/measurement/include "
     " ${CMAKE_CURRENT_LIST_DIR}/messaging/include "
     " ${CMAKE_CURRENT_LIST_DIR}/operatingconstraints/include "
     " ${CMAKE_CURRENT_LIST_DIR}/sensing/include "
     " ${CMAKE_CURRENT_LIST_DIR}/setpoint/include "
     " ${CMAKE_CURRENT_LIST_DIR}/smartenergymanagementps/include "
     " ${CMAKE_CURRENT_LIST_DIR}/supplycondition/include "
     " ${CMAKE_CURRENT_LIST_DIR}/taskmanagement/include "
     " ${CMAKE_CURRENT_LIST_DIR}/threshold/include "
     " ${CMAKE_CURRENT_LIST_DIR}/timeinformation/include "
     " ${CMAKE_CURRENT_LIST_DIR}/timeseries/include "
     " ${CMAKE_CURRENT_LIST_DIR}/timetable/include "
     )

  # set revision
  set(DOXYGEN_REVISION "")

  # Set logo
  set(DOXYGEN_IMAGE_PATH "${CMAKE_CURRENT_BINARY_DIR}/doc/images")
  set(DOXYGEN_PROJECT_LOGO "${DOXYGEN_IMAGE_PATH}/KEO_Logo.png")
  configure_file(${PROJECT_SOURCE_DIR}/doc/KEO_Logo.png ${DOXYGEN_IMAGE_PATH}/KEO_Logo.png COPYONLY)

  # mainpage
  set(DOXYGEN_INPUT ${DOXYGEN_INPUT} ${CMAKE_CURRENT_SOURCE_DIR}/doc/mainpage.md)
  # library definitions
  set(DOXYGEN_INPUT ${DOXYGEN_INPUT} ${CMAKE_CURRENT_SOURCE_DIR}/Library.dox)
  # license
  set(DOXYGEN_INPUT ${DOXYGEN_INPUT} ${CMAKE_CURRENT_SOURCE_DIR}/License.md)

  set(DOXYGEN_EXCLUDE_PATTERN ${DOXYGEN_EXCLUDE_PATTERN} "*/tests/*")
  set(DOXYGEN_INPUT ${DOXYGEN_INPUT} ${keo_target_spine_datagram_additional_dox_files})

  string (REPLACE ";" " " DOXYGEN_INPUT_STR "${DOXYGEN_INPUT}")
  set(DOXYGEN_INPUT "${DOXYGEN_INPUT_STR}")

  string (REPLACE ";" " " DOXYGEN_EXCLUDE_STR "${DOXYGEN_EXCLUDE}")
  set(DOXYGEN_EXCLUDE "${DOXYGEN_EXCLUDE_STR}")


  message(INFO "DOXYGEN_INPUT ${DOXYGEN_INPUT}")
  set(DOXYGEN_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/doc)


  #  add_dependencies(all doc)
  install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc/html
    DESTINATION doc
    COMPONENT ${CPACK_COMPONENT_DOC_GROUP}
    )

  # This line MUST occur AFTER the last add_subdirectory
  configure_file("${PROJECT_SOURCE_DIR}/doc/doxygen.cfg.in" "${PROJECT_BINARY_DIR}/doxygen.cfg")
  
  add_custom_target(doxygen ALL ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/doxygen.cfg)

endif (CREATE_DOC)