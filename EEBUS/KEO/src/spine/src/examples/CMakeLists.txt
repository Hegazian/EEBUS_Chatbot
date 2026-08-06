if (build_examples)

#
# KEO Spine Datagram Measurement Plugin
#

find_package(keo_datagram_measurement
  CONFIG
  REQUIRED
  PATHS ${KEO_SPINE_DATAGRAM_ROOT}
  )

include(${CMAKE_CURRENT_LIST_DIR}/framework/internal/CMakeLists.txt)

set(DOXYGEN_INPUT ${DOXYGEN_INPUT} ${CMAKE_CURRENT_LIST_DIR}/doc/module-examples.dox)


# ============================================================
#
# Framework examples
#
# ============================================================

# ============================================================
# Framework simple client
# ============================================================

set(DOXYGEN_STRIP_FROM_INC_PATH "${DOXYGEN_STRIP_FROM_INC_PATH} ${CMAKE_CURRENT_LIST_DIR}/framework/simpleExample/client/src")

if (AVAHI_FOUND)
  set(keo_target_framework_example_client "keo_framework_example_simple_client")
  keo_executable(
    EXECUTABLE_NAME
    ${keo_target_framework_example_client}

    LIST_SRC
    ${CMAKE_CURRENT_LIST_DIR}/framework/simpleExample/client/src/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/framework/simpleExample/client/src/ExampleClientApplication.cpp
    ${CMAKE_CURRENT_LIST_DIR}/framework/simpleExample/client/src/MeasurementClientFeature.cpp
    ${CMAKE_CURRENT_LIST_DIR}/framework/simpleExample/client/src/AutoConnectTrustAllShipConnectorHandler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/framework/simpleExample/client/src/AppConfiguration.cpp

    LIST_HDR
    ${CMAKE_CURRENT_LIST_DIR}/framework/simpleExample/client/src/ExampleClientApplication.h
    ${CMAKE_CURRENT_LIST_DIR}/framework/simpleExample/client/src/MeasurementClientFeature.h
    ${CMAKE_CURRENT_LIST_DIR}/framework/simpleExample/client/src/AutoConnectTrustAllShipConnectorHandler.h
    ${CMAKE_CURRENT_LIST_DIR}/framework/simpleExample/client/src/AppConfiguration.h

    LINK_LIBRARIES
    ${keo_target_json_security_handler}
    ${keo_target_simple_ship_transport}
    ${keo_target_ship_discovery}
    ${keo_target_framework}
    keo_datagram::keo_datagram_measurement

    SDK
    )

  install(TARGETS ${keo_target_framework_example_client}
    PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ
    LIBRARY DESTINATION lib COMPONENT ${CPACK_COMPONENT_DEV_GROUP}
    ARCHIVE DESTINATION lib COMPONENT ${CPACK_COMPONENT_DEV_GROUP}
    RUNTIME DESTINATION bin COMPONENT ${CPACK_COMPONENT_DEV_GROUP}
    )

  target_compile_definitions(${keo_target_framework_example_client} PRIVATE LOGGER_ID="example_client")

  # Install CMakeLists.txt in example package
if (NOT KEO_SRC)
  install(FILES
    ${CMAKE_CURRENT_LIST_DIR}/framework/simpleExample/client/CMakeLists_for_dev_package.txt
    DESTINATION examples/spine/simple/client
    COMPONENT ${CPACK_COMPONENT_DEV_GROUP}
    RENAME CMakeLists.txt
    )

  install(FILES
    ${CMAKE_CURRENT_LIST_DIR}/framework/simpleExample/client/CMakeLists_for_dev_package.txt
    DESTINATION examples/spine/simple/client
    COMPONENT ${CPACK_COMPONENT_SDK_GROUP}
    RENAME CMakeLists.txt
    )
endif(NOT KEO_SRC)

  install(FILES
    ${CMAKE_CURRENT_LIST_DIR}/framework/simpleExample/client/logging_client.conf
    ${CMAKE_CURRENT_LIST_DIR}/framework/simpleExample/client/client.cfg
    PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ
    DESTINATION bin
    COMPONENT ${CPACK_COMPONENT_DEV_GROUP}
    )

  install(FILES
    ${CMAKE_CURRENT_LIST_DIR}/framework/simpleExample/client/logging_client.conf
    ${CMAKE_CURRENT_LIST_DIR}/framework/simpleExample/client/client.cfg
    PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ
    DESTINATION bin
    COMPONENT ${CPACK_COMPONENT_SDK_GROUP}
    )

  install(FILES
    ${CMAKE_CURRENT_LIST_DIR}/framework/simpleExample/client/runclient.sh
    PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ
    DESTINATION bin
    COMPONENT ${CPACK_COMPONENT_DEV_GROUP}
    )

  install(FILES
    ${CMAKE_CURRENT_LIST_DIR}/framework/simpleExample/client/runclient.sh
    PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ
    DESTINATION bin
    COMPONENT ${CPACK_COMPONENT_SDK_GROUP}
    )

  # Install example sources in example package
  get_target_property(
    FILES_TO_INSTALL
    ${keo_target_framework_example_client}
    SOURCES
    )

  install(FILES
    ${FILES_TO_INSTALL}
    PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ
    DESTINATION examples/spine/simple/client
    COMPONENT ${CPACK_COMPONENT_DEV_GROUP}
    )

  install(FILES
    ${FILES_TO_INSTALL}
    PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ
    DESTINATION examples/spine/simple/client
    COMPONENT ${CPACK_COMPONENT_SDK_GROUP}
    )

  # Docker
  if(CREATE_DOCKER)
    keo_docker(
      IMAGE_NAME                     "${keo_target_framework_example_client}"
      FROM                           "ubuntu:14.04"
      FILES_DIRECTORY                "framework/simpleExample/client/docker"
      ADDITIONAL_PROVISIONING_STEPS  "COPY docker/* /tmp/\n"
      )
  endif(CREATE_DOCKER)

  # ============================================================
  # Framework simple server
  # ============================================================

  set(DOXYGEN_STRIP_FROM_INC_PATH "${DOXYGEN_STRIP_FROM_INC_PATH} ${CMAKE_CURRENT_LIST_DIR}/framework/simpleExample/server/src")

  set(keo_target_framework_example_server "keo_framework_example_simple_server")
  keo_executable(
    EXECUTABLE_NAME
    ${keo_target_framework_example_server}

    LIST_SRC
    ${CMAKE_CURRENT_LIST_DIR}/framework/simpleExample/server/src/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/framework/simpleExample/server/src/ExampleServerApplication.cpp
    ${CMAKE_CURRENT_LIST_DIR}/framework/simpleExample/server/src/MeasurementServerFeature.cpp
    ${CMAKE_CURRENT_LIST_DIR}/framework/simpleExample/server/src/TrustAllShipTransportConnector.cpp

    LIST_HDR
    ${CMAKE_CURRENT_LIST_DIR}/framework/simpleExample/server/src/ExampleServerApplication.h
    ${CMAKE_CURRENT_LIST_DIR}/framework/simpleExample/server/src/MeasurementServerFeature.h
    ${CMAKE_CURRENT_LIST_DIR}/framework/simpleExample/server/src/TrustAllShipTransportConnector.h

    LINK_LIBRARIES
    ${keo_target_json_security_handler}
    ${keo_target_default_ship_transport}
    ${keo_target_framework}
    ${keo_target_ship_discovery}
    keo_datagram::keo_datagram_measurement

    SDK
    )

  target_compile_definitions(${keo_target_framework_example_server} PRIVATE LOGGER_ID="example_server")

  install(TARGETS ${keo_target_framework_example_server}
    PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ
    LIBRARY DESTINATION lib COMPONENT ${CPACK_COMPONENT_DEV_GROUP}
    ARCHIVE DESTINATION lib COMPONENT ${CPACK_COMPONENT_DEV_GROUP}
    RUNTIME DESTINATION bin COMPONENT ${CPACK_COMPONENT_DEV_GROUP}
    )

  # Install CMakeLists.txt in dev package
if (NOT KEO_SRC)
  install(FILES
    ${CMAKE_CURRENT_LIST_DIR}/framework/simpleExample/server/CMakeLists_for_dev_package.txt
    DESTINATION examples/spine/simple/server
    COMPONENT ${CPACK_COMPONENT_DEV_GROUP}
    RENAME CMakeLists.txt
    )

  install(FILES
    ${CMAKE_CURRENT_LIST_DIR}/framework/simpleExample/server/CMakeLists_for_dev_package.txt
    DESTINATION examples/spine/simple/server
    COMPONENT ${CPACK_COMPONENT_SDK_GROUP}
    RENAME CMakeLists.txt
    )
endif(NOT KEO_SRC)

  install(FILES
    ${CMAKE_CURRENT_LIST_DIR}/framework/simpleExample/server/logging_server.conf
    ${CMAKE_CURRENT_LIST_DIR}/framework/simpleExample/server/server.cfg
    PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ
    DESTINATION bin
    COMPONENT ${CPACK_COMPONENT_DEV_GROUP}
    )

  install(FILES
    ${CMAKE_CURRENT_LIST_DIR}/framework/simpleExample/server/runserver.sh
    PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ
    DESTINATION bin
    COMPONENT ${CPACK_COMPONENT_DEV_GROUP}
    )

  install(FILES
    ${CMAKE_CURRENT_LIST_DIR}/framework/simpleExample/server/logging_server.conf
    ${CMAKE_CURRENT_LIST_DIR}/framework/simpleExample/server/server.cfg
    PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ
    DESTINATION bin
    COMPONENT ${CPACK_COMPONENT_SDK_GROUP}
    )

  install(FILES
    ${CMAKE_CURRENT_LIST_DIR}/framework/simpleExample/server/runserver.sh
    PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ
    DESTINATION bin
    COMPONENT ${CPACK_COMPONENT_SDK_GROUP}
    )

  # Install example sources in dev package
  get_target_property(
    FILES_TO_INSTALL
    ${keo_target_framework_example_server}
    SOURCES
    )

  install(FILES
    ${FILES_TO_INSTALL}
    PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ
    DESTINATION examples/spine/simple/server
    COMPONENT ${CPACK_COMPONENT_DEV_GROUP}
    )

  install(FILES
    ${FILES_TO_INSTALL}
    PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ
    DESTINATION examples/spine/simple/server
    COMPONENT ${CPACK_COMPONENT_SDK_GROUP}
    )

  # Docker
  if(CREATE_DOCKER)
    keo_docker(
      IMAGE_NAME                     "${keo_target_framework_example_server}"
      FROM                           "ubuntu:14.04"
      FILES_DIRECTORY                "framework/simpleExample/server/docker"
      ADDITIONAL_PROVISIONING_STEPS  "COPY docker/* /tmp/\n"
      )
  endif(CREATE_DOCKER)


endif (AVAHI_FOUND)


# ============================================================
# Install
# ============================================================

# Install CMakeLists.txt
if (NOT KEO_SRC)
install(FILES
  ${CMAKE_CURRENT_LIST_DIR}/CMakeLists_for_dev_package.txt
  DESTINATION examples
  COMPONENT ${CPACK_COMPONENT_DEV_GROUP}
  RENAME CMakeLists.txt
  )

install(FILES
  ${CMAKE_CURRENT_LIST_DIR}/CMakeLists_for_dev_package.txt
  DESTINATION examples
  COMPONENT ${CPACK_COMPONENT_SDK_GROUP}
  RENAME CMakeLists.txt
  )
endif(NOT KEO_SRC)

# Install build script
install(FILES
  ${CMAKE_CURRENT_LIST_DIR}/build_cmake.sh
  DESTINATION examples
  PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ
  COMPONENT ${CPACK_COMPONENT_DEV_GROUP}
  )

install(FILES
  ${CMAKE_CURRENT_LIST_DIR}/build_cmake.sh
  DESTINATION examples
  PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ
  COMPONENT ${CPACK_COMPONENT_SDK_GROUP}
  )
endif(build_examples)
