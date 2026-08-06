
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(keo_target_ship_discovery "keo_ship_discovery")

# ============================================================
#
# Required packages
#
# ============================================================

find_package(Avahi)
if(NOT AVAHI_FOUND)
    message(FATAL_ERROR "Avahi not found.")
endif (NOT AVAHI_FOUND)

# ============================================================
#
# SHIP discovery
#
# ============================================================

set(DOXYGEN_STRIP_FROM_INC_PATH "${DOXYGEN_STRIP_FROM_INC_PATH} ${CMAKE_CURRENT_LIST_DIR}/include")

keo_library(
    LIBRARY_NAME ${keo_target_ship_discovery}

    LIBRARY_TYPE SHARED

    EXPORT_NAME  ${targets_export_name}

    LIST_SRC
        ${CMAKE_CURRENT_LIST_DIR}/src/internal/ShipServiceInternal.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/internal/ShipDiscoveryInterfaceInternal.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/internal/ShipDiscoveryInternal.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/internal/KEOZeroconfCallbackIf.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/internal/KEOZeroconf.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/internal/KEOZeroconfService.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/ShipService.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/ShipDiscovery.cpp


    LIST_HDR_PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/src/internal/ShipServiceInternal.h
        ${CMAKE_CURRENT_LIST_DIR}/src/internal/ShipDiscoveryInterfaceInternal.h
        ${CMAKE_CURRENT_LIST_DIR}/src/internal/ShipDiscoveryInternal.h
        ${CMAKE_CURRENT_LIST_DIR}/src/internal/KEOZeroconf.h
        ${CMAKE_CURRENT_LIST_DIR}/src/internal/KEOZeroconfCallbackIf.h
        ${CMAKE_CURRENT_LIST_DIR}/src/internal/KEOZeroconfService.h


    LIST_HDR_PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include/keo_ship_discovery/ShipDiscovery.h


    LIST_HDR_INTERFACE


    INCLUDE_DIRECTORIES_PRIVATE
        ${AVAHI_INCLUDE_DIR}


    INCLUDE_DIRECTORIES_PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include


    INCLUDE_DIRECTORIES_INTERFACE


    HDR_INSTALL_DIR include/keo_ship_discovery


    LINK_LIBRARIES_PRIVATE
        ${keo_target_util}
        ${AVAHI_LIBRARIES}

    SDK
    )

target_compile_definitions(${keo_target_ship_discovery} PRIVATE LOGGER_ID="keo_ship_discovery")


#
# KEOZeroconf examples
#

# publishService
set(keo_target_zeroconf_example_publish_service "publishService")
keo_executable(
    EXECUTABLE_NAME ${keo_target_zeroconf_example_publish_service}

    LIST_SRC        ${CMAKE_CURRENT_LIST_DIR}/examples/publishService.cpp

    LIST_HDR

    INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_LIST_DIR}/src/internal
        ${AVAHI_INCLUDE_DIR}

    LINK_LIBRARIES
        ${keo_target_ship_discovery}
        ${keo_target_util}
)
target_compile_definitions(${keo_target_zeroconf_example_publish_service} PRIVATE LOGGER_ID="zeroconf_example_publish_service")


# browseService
set(keo_target_zeroconf_example_browse_service "browseService")
keo_executable(
    EXECUTABLE_NAME ${keo_target_zeroconf_example_browse_service}

    LIST_SRC        ${CMAKE_CURRENT_LIST_DIR}/examples/browseService.cpp

    LIST_HDR

    INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_LIST_DIR}/src/internal
        ${AVAHI_INCLUDE_DIR}

    LINK_LIBRARIES
        ${keo_target_ship_discovery}
        ${keo_target_util}
)
target_compile_definitions(${keo_target_zeroconf_example_browse_service} PRIVATE LOGGER_ID="zeroconf_example_browse_service")


#
# Unit tests
#

keo_googletest(
    TEST_NAME ${keo_target_ship_discovery}_discovery

    LIST_SRC
        ${CMAKE_CURRENT_LIST_DIR}/tests/gtest_main.cpp
        ${CMAKE_CURRENT_LIST_DIR}/tests/DiscoveryTest.cpp
        ${CMAKE_CURRENT_LIST_DIR}/tests/zeroconf_test.cpp

    INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_LIST_DIR}/src/internal
        ${AVAHI_INCLUDE_DIR}

    COMPILE_DEFINITIONS
        LOGGER_ID="keo_ship_discovery"

    LINK_LIBRARIES
    ${keo_target_util}
    ${keo_target_ship_discovery}
    )
