

# ============================================================
#
# Library ship transport with SHIP discovery
#
# ============================================================

set(keo_target_default_ship_transport "keo_default_ship_transport")

SET (KEO_DEFAULT_SHIP_TRANSPORT_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/src/ShipConnectionHandler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/ShipConnectionImplementation.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/ShipTransportConfiguration.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/ShipTransportConnector.cpp
)

SET (KEO_DEFAULT_SHIP_TRANSPORT_PRIVATE_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/src/ShipConnectionHandler.h
    ${CMAKE_CURRENT_LIST_DIR}/src/ShipConnectionImplementation.h
    ${CMAKE_CURRENT_LIST_DIR}/src/ShipControlInterface.h
)

SET (KEO_DEFAULT_SHIP_TRANSPORT_PUBLIC_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/include/keo_default_ship_transport/ShipTransportConfiguration.h
    ${CMAKE_CURRENT_LIST_DIR}/include/keo_default_ship_transport/ShipTransportConnector.h
)

SET (KEO_DEFAULT_SHIP_TRANSPORT_PUBLIC_HEADER_INSTALL_DIR "include/keo_default_ship_transport")

keo_library(
  LIBRARY_NAME ${keo_target_default_ship_transport}

  LIBRARY_TYPE SHARED

  EXPORT_NAME  ${targets_export_name}

  LIST_SRC
  ${KEO_DEFAULT_SHIP_TRANSPORT_SOURCES}

  LIST_HDR_PRIVATE
  ${KEO_DEFAULT_SHIP_TRANSPORT_PRIVATE_HEADERS}

  LIST_HDR_PUBLIC
  ${KEO_DEFAULT_SHIP_TRANSPORT_PUBLIC_HEADERS}

  LIST_HDR_INTERFACE

  INCLUDE_DIRECTORIES_PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/src

  INCLUDE_DIRECTORIES_PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/include

  INCLUDE_DIRECTORIES_INTERFACE

  HDR_INSTALL_DIR ${KEO_DEFAULT_SHIP_TRANSPORT_PUBLIC_HEADER_INSTALL_DIR}


  LINK_LIBRARIES
  ${keo_target_framework}
  ${keo_target_ship}
  ${keo_target_ship_discovery}

  SDK
  )

target_compile_definitions(${keo_target_default_ship_transport} PRIVATE LOGGER_ID="keo_spine_transport")


# ============================================================
#
# Package configuration
#
# ============================================================

SET (KEO_DEFAULT_SHIP_TRANSPORT_EXAMPLE_DIR "examples/spine/defaultshiptransport")

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
    DESTINATION ${KEO_DEFAULT_SHIP_TRANSPORT_EXAMPLE_DIR}
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
    DESTINATION ${KEO_DEFAULT_SHIP_TRANSPORT_EXAMPLE_DIR}
    COMPONENT ${CPACK_COMPONENT_DEV_GROUP}
    RENAME CMakeLists.txt
    )
endif(NOT KEO_SRC)


