set(keo_target_framework "keo_framework")


# ============================================================
#
# Required packages
#
# ============================================================

find_package(keo_datagram_core
  CONFIG
  REQUIRED
  PATHS ${KEO_SPINE_DATAGRAM_ROOT}
  )

# ============================================================
#
# SPINE Framework
#
# ============================================================

keo_library(
  LIBRARY_NAME 
    ${keo_target_framework}
  
  LIBRARY_TYPE 
    SHARED
  
  EXPORT_NAME  
    ${targets_export_name}

  LIST_SRC
    ${CMAKE_CURRENT_LIST_DIR}/src/ClientFeature.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/DatagramMemo.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/DatagramRecord.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/DeviceClassificationFeature.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/DeviceTransportIdHandler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Entity.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Feature.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/PrimaryDeviceInformationEntity.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/PrimaryNodeManagementFeature.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/ServerFeature.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/SmartDevice.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/SmartDevicePriv.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/SpineLink.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/EntityHandler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/DeviceDefinition.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/TimeoutService.cpp

  LIST_HDR_PRIVATE

  LIST_HDR_PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include/keo_spine/ClientFeature.h
    ${CMAKE_CURRENT_LIST_DIR}/include/keo_spine/DatagramMemo.h
    ${CMAKE_CURRENT_LIST_DIR}/include/keo_spine/DatagramRecord.h
    ${CMAKE_CURRENT_LIST_DIR}/include/keo_spine/DeviceCallbackInterface.h
    ${CMAKE_CURRENT_LIST_DIR}/include/keo_spine/DeviceClassificationFeature.h
    ${CMAKE_CURRENT_LIST_DIR}/include/keo_spine/DeviceDefinition.h
    ${CMAKE_CURRENT_LIST_DIR}/include/keo_spine/DeviceSendServiceInterface.h
    ${CMAKE_CURRENT_LIST_DIR}/include/keo_spine/Entity.h
    ${CMAKE_CURRENT_LIST_DIR}/include/keo_spine/Feature.h
    ${CMAKE_CURRENT_LIST_DIR}/include/keo_spine/GatewayDevice.h
    ${CMAKE_CURRENT_LIST_DIR}/include/keo_spine/PrimaryDeviceInformationEntity.h
    ${CMAKE_CURRENT_LIST_DIR}/include/keo_spine/PrimaryNodeManagementFeature.h
    ${CMAKE_CURRENT_LIST_DIR}/include/keo_spine/PrimaryNodeManagementInterface.h
    ${CMAKE_CURRENT_LIST_DIR}/include/keo_spine/SendServiceInterface.h
    ${CMAKE_CURRENT_LIST_DIR}/include/keo_spine/ServerFeature.h
    ${CMAKE_CURRENT_LIST_DIR}/include/keo_spine/SmartDevice.h
    ${CMAKE_CURRENT_LIST_DIR}/include/keo_spine/SpineLink.h
    ${CMAKE_CURRENT_LIST_DIR}/include/keo_spine/SpineLinkDevice.h
    ${CMAKE_CURRENT_LIST_DIR}/include/keo_spine/SpineLinkReceiveServiceInterface.h
    ${CMAKE_CURRENT_LIST_DIR}/include/keo_spine/SpineLinkSendServiceInterface.h
    ${CMAKE_CURRENT_LIST_DIR}/include/keo_spine/TransportConnection.h


  LIST_HDR_INTERFACE

  INCLUDE_DIRECTORIES_PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src

  INCLUDE_DIRECTORIES_PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include

  INCLUDE_DIRECTORIES_INTERFACE

  HDR_INSTALL_DIR 
    include/keo_spine

  LINK_LIBRARIES_PUBLIC
    keo_datagram::keo_datagram_core
    ${keo_target_util}

  LINK_LIBRARIES_PRIVATE
    ${keo_target_tool}

  SDK
  )

generate_export_header(${keo_target_framework})

set(keo_target_spine_additional_dox_files "")

target_compile_definitions(${keo_target_framework} PRIVATE LOGGER_ID="keo_spine")

# ============================================================
# Install
# ============================================================
set (FILES_TO_INSTALL
  ${CMAKE_CURRENT_LIST_DIR}/scripts/generateKeys.sh
  )

install(FILES
  ${FILES_TO_INSTALL}
  PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ
  DESTINATION bin
  COMPONENT ${CPACK_COMPONENT_BIN_GROUP}
  )

install(FILES
  ${FILES_TO_INSTALL}
  PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ
  DESTINATION bin
  COMPONENT ${CPACK_COMPONENT_DEV_GROUP}
  )

install(FILES
  ${FILES_TO_INSTALL}
  PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ
  DESTINATION bin
  COMPONENT ${CPACK_COMPONENT_SDK_GROUP}
  )

# ============================================================
# Doxygen
# ============================================================

if (doxygen_input_manual)
  set(DOXYGEN_INPUT ${DOXYGEN_INPUT} ${CMAKE_CURRENT_LIST_DIR}/include/keo_spine)
endif()

set(DOXYGEN_STRIP_FROM_INC_PATH "${DOXYGEN_STRIP_FROM_INC_PATH} ${CMAKE_CURRENT_LIST_DIR}/include")
set(DOXYGEN_INPUT "${DOXYGEN_INPUT} ${CMAKE_CURRENT_LIST_DIR}/doc/modules.dox")

set(PLANTUML_SOURCES ${PLANTUML_SOURCES}
  ${CMAKE_CURRENT_LIST_DIR}/doc/plantuml/ExampleClient_Object.plantuml
  ${CMAKE_CURRENT_LIST_DIR}/doc/plantuml/ExampleClient_Component.plantuml
  ${CMAKE_CURRENT_LIST_DIR}/doc/plantuml/ExampleClient_SmartDeviceApplication_Component.plantuml
  ${CMAKE_CURRENT_LIST_DIR}/doc/plantuml/ExampleClient_SmartDeviceApplication_Object.plantuml
  )

# ============================================================
#
# Unit tests
#
# ============================================================

keo_googletest(
    TEST_NAME ${keo_target_framework}

    LIST_SRC
    ${CMAKE_CURRENT_LIST_DIR}/tests/gtest_main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/tests/DeviceCallbackListener.cpp
    ${CMAKE_CURRENT_LIST_DIR}/tests/GenericClientFeature.cpp
    ${CMAKE_CURRENT_LIST_DIR}/tests/SmartDeviceHelper.cpp
    ${CMAKE_CURRENT_LIST_DIR}/tests/TestClientFeature.cpp
    ${CMAKE_CURRENT_LIST_DIR}/tests/TestServerFeature.cpp
    ${CMAKE_CURRENT_LIST_DIR}/tests/TestSendService.cpp
    ${CMAKE_CURRENT_LIST_DIR}/tests/TestPrimaryNodeManagementFeature.cpp
    ${CMAKE_CURRENT_LIST_DIR}/tests/EntityHandlerTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/tests/EntityTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/tests/ClientFeatureTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/tests/ServerFeatureTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/tests/SmartDeviceTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/tests/PrimaryNodeManagementFeatureTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/tests/TimeoutService_test.cpp
    ${CMAKE_CURRENT_LIST_DIR}/tests/DeviceTransportIdHandlerTest.cpp

    LIST_HDR
    ${CMAKE_CURRENT_LIST_DIR}/tests/DeviceCallbackListener.h
    ${CMAKE_CURRENT_LIST_DIR}/tests/GenericClientFeature.h
    ${CMAKE_CURRENT_LIST_DIR}/tests/SmartDeviceHelper.h
    ${CMAKE_CURRENT_LIST_DIR}/tests/TestClientFeature.h
    ${CMAKE_CURRENT_LIST_DIR}/tests/TestServerFeature.h
    ${CMAKE_CURRENT_LIST_DIR}/tests/TestSendService.h

    INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_LIST_DIR}/src
    ${CMAKE_CURRENT_LIST_DIR}/include

    COMPILE_DEFINITIONS
        LOGGER_ID="${keo_target_framework}_test"

    LINK_LIBRARIES ${keo_target_util} ${keo_target_spine_datagram} ${keo_target_framework}
  )
