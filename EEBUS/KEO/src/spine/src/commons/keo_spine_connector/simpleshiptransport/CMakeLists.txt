

# ============================================================
#
# Library ship transport without SHIP discovery
#
# ============================================================

set(keo_target_simple_ship_transport "keo_simple_ship_transport")

SET (KEO_SIMPLE_SHIP_TRANSPORT_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/src/SimpleShipConnection.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/SimpleShipTransportConnector.cpp
)

SET (KEO_SIMPLE_SHIP_TRANSPORT_PRIVATE_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/src/SimpleShipConnection.h
    ${CMAKE_CURRENT_LIST_DIR}/src/ShipTransportConnectionCreator.h
)

SET (KEO_SIMPLE_SHIP_TRANSPORT_PUBLIC_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/include/keo_simple_ship_transport/SimpleShipTransportConnector.h
)

keo_library(
  LIBRARY_NAME ${keo_target_simple_ship_transport}

  LIBRARY_TYPE SHARED

  EXPORT_NAME  ${targets_export_name}

  LIST_SRC
  ${KEO_SIMPLE_SHIP_TRANSPORT_SOURCES}

  LIST_HDR_PRIVATE
  ${KEO_SIMPLE_SHIP_TRANSPORT_PRIVATE_HEADERS}

  LIST_HDR_PUBLIC
  ${KEO_SIMPLE_SHIP_TRANSPORT_PUBLIC_HEADERS}


  LIST_HDR_INTERFACE

  INCLUDE_DIRECTORIES_PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/src

  INCLUDE_DIRECTORIES_PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/include

  INCLUDE_DIRECTORIES_INTERFACE

  HDR_INSTALL_DIR include/keo_simple_ship_transport


  LINK_LIBRARIES
  ${keo_target_framework}
  ${keo_target_ship}

  SDK
  )

target_compile_definitions(${keo_target_simple_ship_transport} PRIVATE LOGGER_ID="keo_spine_transport")


# ============================================================
#
# Package configuration
#
# ============================================================

SET (KEO_SIMPLE_SHIP_TRANSPORT_EXAMPLE_DIR "examples/spine/simpleshiptransport")

# SDK package
install(DIRECTORY
    ${CMAKE_CURRENT_LIST_DIR}
    DESTINATION examples/spine
    USE_SOURCE_PERMISSIONS
    COMPONENT ${CPACK_COMPONENT_SDK_GROUP}
    PATTERN CMakeLists_for_dev_package.txt EXCLUDE
    PATTERN CMakeLists.txt EXCLUDE
)

if (NOT KEO_SRC)
install(FILES
    ${CMAKE_CURRENT_LIST_DIR}/CMakeLists_for_dev_package.txt
    DESTINATION ${KEO_SIMPLE_SHIP_TRANSPORT_EXAMPLE_DIR}
    COMPONENT ${CPACK_COMPONENT_SDK_GROUP}
    RENAME CMakeLists.txt
    )
endif(NOT KEO_SRC)

# dev package
install(DIRECTORY
    ${CMAKE_CURRENT_LIST_DIR}
    DESTINATION examples/spine
    USE_SOURCE_PERMISSIONS
    COMPONENT ${CPACK_COMPONENT_DEV_GROUP}
    PATTERN CMakeLists_for_dev_package.txt EXCLUDE
    PATTERN CMakeLists.txt EXCLUDE
)

if (NOT KEO_SRC)
install(FILES
    ${CMAKE_CURRENT_LIST_DIR}/CMakeLists_for_dev_package.txt
    DESTINATION ${KEO_SIMPLE_SHIP_TRANSPORT_EXAMPLE_DIR}
    COMPONENT ${CPACK_COMPONENT_DEV_GROUP}
    RENAME CMakeLists.txt
    )
endif(NOT KEO_SRC)



