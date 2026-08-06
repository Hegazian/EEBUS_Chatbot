

# ============================================================
#
# Library json based security store
#
# ============================================================

# Default security handler file based
# Do this one first because the other examples require headers from here
set(keo_target_json_security_handler "keo_json_security_handler")

set(DOXYGEN_STRIP_FROM_INC_PATH "${DOXYGEN_STRIP_FROM_INC_PATH} ${CMAKE_CURRENT_LIST_DIR}/json_security_handler/include")

keo_library(
    LIBRARY_NAME ${keo_target_json_security_handler}
    LIBRARY_TYPE SHARED
    EXPORT_NAME ${targets_export_name}

    LIST_SRC
    ${CMAKE_CURRENT_LIST_DIR}/json_security_handler/src/JsonSecurityHandler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/json_security_handler/src/JsonTrustStore.cpp
    ${CMAKE_CURRENT_LIST_DIR}/json_security_handler/src/KEByteArray.cpp
    ${CMAKE_CURRENT_LIST_DIR}/json_security_handler/src/json/jsoncpp.cpp

    LIST_HDR_PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/json_security_handler/src/JsonTrustStore.h
    ${CMAKE_CURRENT_LIST_DIR}/json_security_handler/src/KEByteArray.h
    ${CMAKE_CURRENT_LIST_DIR}/json_security_handler/src/json/json.h
    ${CMAKE_CURRENT_LIST_DIR}/json_security_handler/src/json/json-forwards.h

    LIST_HDR_PUBLIC

    LIST_HDR_INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/json_security_handler/include/keo_json_security_handler/JsonSecurityHandler.h

    INCLUDE_DIRECTORIES_PRIVATE
    ${${keo_target_util}_interface_include_directories}
    ${${keo_target_ship}_interface_include_directories}

    INCLUDE_DIRECTORIES_PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/json_security_handler/include

    INCLUDE_DIRECTORIES_INTERFACE

    HDR_INSTALL_DIR include/keo_json_security_handler

    LINK_LIBRARIES
    ${keo_target_ship}

    SDK
)

target_compile_definitions(${keo_target_json_security_handler} PRIVATE LOGGER_ID="json_security_handler")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  if(NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 7.0.0)
    set_source_files_properties(
      ${CMAKE_CURRENT_LIST_DIR}/json_security_handler/src/json/jsoncpp.cpp
      PROPERTIES COMPILE_FLAGS -Wno-error=implicit-fallthrough)
  endif()
endif()

# ============================================================
#
# Google teset
#
# ============================================================

add_definitions(-DTC_SAMPLES_DIR="${CMAKE_CURRENT_LIST_DIR}/json_security_handler/tests/samples/")
keo_googletest(
    TEST_NAME ${keo_target_json_security_handler}

    LIST_SRC
    ${CMAKE_CURRENT_LIST_DIR}/json_security_handler/tests/gtest_main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/json_security_handler/tests/JsonSecurityHandlerTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/json_security_handler/tests/JsonTruststoreTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/json_security_handler/tests/KEByteArrayTest.cpp

    LIST_HDR

    INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_LIST_DIR}/json_security_handler/src

    LINK_LIBRARIES
    ${keo_target_json_security_handler}
  )

set(DOXYGEN_INPUT ${DOXYGEN_INPUT} ${CMAKE_CURRENT_LIST_DIR}/doc/security.dox)

# ============================================================
#
# Package configuration
#
# ============================================================

set(KEO_JSON_SECURITY_HANDLER_PACKAGE_DESTINATION examples/security/json_security_handler)

# SDK package
install(DIRECTORY
    ${CMAKE_CURRENT_LIST_DIR}
    DESTINATION examples
    USE_SOURCE_PERMISSIONS
    COMPONENT ${CPACK_COMPONENT_SDK_GROUP}
    PATTERN CMakeLists_for_dev_package.txt EXCLUDE
    PATTERN CMakeLists.txt EXCLUDE
    PATTERN doc EXCLUDE
    PATTERN tests EXCLUDE
)

if (NOT KEO_SRC)
install(FILES
    ${CMAKE_CURRENT_LIST_DIR}/json_security_handler/CMakeLists_for_dev_package.txt
    DESTINATION ${KEO_JSON_SECURITY_HANDLER_PACKAGE_DESTINATION}
    COMPONENT ${CPACK_COMPONENT_SDK_GROUP}
    RENAME CMakeLists.txt
    )
endif(NOT KEO_SRC)

# dev package
install(DIRECTORY
    ${CMAKE_CURRENT_LIST_DIR}
    DESTINATION examples
    USE_SOURCE_PERMISSIONS
    COMPONENT ${CPACK_COMPONENT_DEV_GROUP}
    PATTERN CMakeLists_for_dev_package.txt EXCLUDE
    PATTERN CMakeLists.txt EXCLUDE
    PATTERN doc EXCLUDE
    PATTERN tests EXCLUDE
)

if (NOT KEO_SRC)
install(FILES
    ${CMAKE_CURRENT_LIST_DIR}/json_security_handler/CMakeLists_for_dev_package.txt
    DESTINATION ${KEO_JSON_SECURITY_HANDLER_PACKAGE_DESTINATION}
    COMPONENT ${CPACK_COMPONENT_DEV_GROUP}
    RENAME CMakeLists.txt
    )
endif(NOT KEO_SRC)
