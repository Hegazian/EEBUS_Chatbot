
set(keo_target_ship "keo_ship")

# ============================================================
#
# Ship discovery
#
# ============================================================

if (AVAHI_FOUND)
    include(${CMAKE_CURRENT_LIST_DIR}/discovery/CMakeLists.txt)
endif (AVAHI_FOUND)

# ============================================================
#
# Project settings
#
# ============================================================

if ( NOT GENERATED_SHIP_DIR )
  set(GENERATED_SHIP_DIR    "${CMAKE_CURRENT_BINARY_DIR}/GeneratedShip")
endif()

# ============================================================
#
# Required packages
#
# ============================================================

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

if (NOT KEO_SRC)
  # prepare renaming the databinder
  if ((NOT SHIP_DATABINDER_ROOT) AND KEO_SHIP_DATABINDER_ROOT)
    set(SHIP_DATABINDER_ROOT ${KEO_SHIP_DATABINDER_ROOT})
  endif()

  find_package(ShipDatabinder)
  if( NOT SHIP_DATABINDER_FOUND )
    message(FATAL_ERROR "ShipDatabinder not found. Try to set SHIP_DATABINDER_ROOT.")
  endif()
else()

  set(SHIP_GENERATED_LIST_FILES
    ${GENERATED_SHIP_DIR}/src/ship/Classes.cpp
    ${GENERATED_SHIP_DIR}/src/ship/ShipDataType.cpp
    ${GENERATED_SHIP_DIR}/src/ship/ShipDataUtilities.cpp

    ${GENERATED_SHIP_DIR}/include/keo_ship/AccessMethods.h
    ${GENERATED_SHIP_DIR}/include/keo_ship/AccessMethodsRequest.h
    ${GENERATED_SHIP_DIR}/include/keo_ship/ClassDnsSd_mDns.h
    ${GENERATED_SHIP_DIR}/include/keo_ship/ClassVersion.h
    ${GENERATED_SHIP_DIR}/include/keo_ship/ConnectionClose.h
    ${GENERATED_SHIP_DIR}/include/keo_ship/ConnectionClosePhase.h
    ${GENERATED_SHIP_DIR}/include/keo_ship/ConnectionCloseReason.h
    ${GENERATED_SHIP_DIR}/include/keo_ship/ConnectionHello.h
    ${GENERATED_SHIP_DIR}/include/keo_ship/ConnectionHelloPhase.h
    ${GENERATED_SHIP_DIR}/include/keo_ship/ConnectionPinError.h
    ${GENERATED_SHIP_DIR}/include/keo_ship/ConnectionPinInput.h
    ${GENERATED_SHIP_DIR}/include/keo_ship/ConnectionPinState.h
    ${GENERATED_SHIP_DIR}/include/keo_ship/Extension.h
    ${GENERATED_SHIP_DIR}/include/keo_ship/GenerateComparison.h
    ${GENERATED_SHIP_DIR}/include/keo_ship/GenerateMessageOutput.h
    ${GENERATED_SHIP_DIR}/include/keo_ship/GenerateRandom.h
    ${GENERATED_SHIP_DIR}/include/keo_ship/Header.h
    ${GENERATED_SHIP_DIR}/include/keo_ship/MessageProtocolFormats.h
    ${GENERATED_SHIP_DIR}/include/keo_ship/MessageProtocolHandshakeError.h
    ${GENERATED_SHIP_DIR}/include/keo_ship/MessageProtocolHandshake.h
    ${GENERATED_SHIP_DIR}/include/keo_ship/PinInputPermission.h
    ${GENERATED_SHIP_DIR}/include/keo_ship/PinState.h
    ${GENERATED_SHIP_DIR}/include/keo_ship/ProtocolHandshakeType.h
    ${GENERATED_SHIP_DIR}/include/keo_ship/ShipDataType.h
    ${GENERATED_SHIP_DIR}/include/keo_ship/ShipDataUtilities.h
    ${GENERATED_SHIP_DIR}/include/keo_ship/ShipHeader.h
    ${GENERATED_SHIP_DIR}/include/keo_ship/ShipXsdVersion.h
    )

endif()

# ============================================================
#
# Run SHIP Databinder
#
# ============================================================

set(SHIP_XSD_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/xsd")

if (NOT KEO_SRC)
  include(RunShipDatabinder)
endif()

set(DOXYGEN_STRIP_FROM_INC_PATH "${DOXYGEN_STRIP_FROM_INC_PATH} ${CMAKE_CURRENT_LIST_DIR}/include")
set(DOXYGEN_INPUT "${DOXYGEN_INPUT} ${CMAKE_CURRENT_LIST_DIR}/doc/modules.dox")

# ============================================================
#
# SHIP Stack
#
# ============================================================

keo_library(
  LIBRARY_NAME ${keo_target_ship}

  LIBRARY_TYPE SHARED

  EXPORT_NAME  ${targets_export_name}

  LIST_SRC
    ${CMAKE_CURRENT_LIST_DIR}/messageexchange/src/TrustLevel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messageexchange/src/ProtocolConfig.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messageexchange/src/ShipMessageExchange.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messageexchange/src/internal/ConnectionStateHandler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messageexchange/src/internal/StateHandler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messageexchange/src/internal/StateInfo.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messageexchange/src/ShipStringUtil.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messageexchange/src/ShipByteArray.cpp
    ${CMAKE_CURRENT_LIST_DIR}/stack/src/ShipNode.cpp
    ${CMAKE_CURRENT_LIST_DIR}/stack/src/ShipStack.cpp
    ${CMAKE_CURRENT_LIST_DIR}/stack/src/SocketConnectionHandler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/security/src/X509Certificate.cpp
    ${CMAKE_CURRENT_LIST_DIR}/transformer/CShipDataClass.cpp
    ${CMAKE_CURRENT_LIST_DIR}/transformer/CShipListClass.cpp
    ${CMAKE_CURRENT_LIST_DIR}/transformer/ClassBuilder.cpp
    ${CMAKE_CURRENT_LIST_DIR}/transformer/Data.cpp
    ${CMAKE_CURRENT_LIST_DIR}/transformer/ClassBuilder.cpp
    ${CMAKE_CURRENT_LIST_DIR}/transformer/JsonBuilder.cpp
    ${CMAKE_CURRENT_LIST_DIR}/transformer/JsonParser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/transformer/ShipDataUtility.cpp
    ${CMAKE_CURRENT_LIST_DIR}/transformer/ShipControlTransformer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/transformer/ShipDataTransformer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/transport/src/ShipSocket.cpp
    ${CMAKE_CURRENT_LIST_DIR}/transport/src/ShipWss.cpp
    ${CMAKE_CURRENT_LIST_DIR}/transport/src/WebSocket.cpp
    ${CMAKE_CURRENT_LIST_DIR}/transport/src/SocketServer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/transport/src/base64/base64.cpp
    ${CMAKE_CURRENT_LIST_DIR}/transport/src/WebSocketParser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/transport/src/tls/OpenSSLManager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/transport/src/tls/ShipOpenSSL.cpp
    ${CMAKE_CURRENT_LIST_DIR}/transport/src/tls/ShipOpenSSLCallbacks.cpp
    ${CMAKE_CURRENT_LIST_DIR}/transport/src/tls/OpenSSLConnection.cpp
    ${CMAKE_CURRENT_LIST_DIR}/util/src/Ski.cpp
    ${CMAKE_CURRENT_LIST_DIR}/util/src/ShipTimerController.cpp
    ${CMAKE_CURRENT_LIST_DIR}/util/src/ShipTimer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/util/src/Uri.cpp
    ${CMAKE_CURRENT_LIST_DIR}/util/src/UriInternal.cpp
    ${SHIP_GENERATED_LIST_FILES}

  LIST_HDR_PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/messageexchange/src/ConnectionStateHandlerListener.h
    ${CMAKE_CURRENT_LIST_DIR}/messageexchange/src/NodeEvent.h
    ${CMAKE_CURRENT_LIST_DIR}/messageexchange/src/ShipMessageExchange.h
    ${CMAKE_CURRENT_LIST_DIR}/messageexchange/src/ShipMessageExchangeConnectionConfirmedListener.h
    ${CMAKE_CURRENT_LIST_DIR}/messageexchange/src/ShipStringUtil.h
    ${CMAKE_CURRENT_LIST_DIR}/messageexchange/src/ShipByteArray.h
    ${CMAKE_CURRENT_LIST_DIR}/messageexchange/src/internal/ActionState.h
    ${CMAKE_CURRENT_LIST_DIR}/messageexchange/src/internal/ConnectionStateHandler.h
    ${CMAKE_CURRENT_LIST_DIR}/messageexchange/src/internal/NodeInfo.h
    ${CMAKE_CURRENT_LIST_DIR}/messageexchange/src/internal/ShipMessageType.h
    ${CMAKE_CURRENT_LIST_DIR}/messageexchange/src/internal/SmeConnectionState.h
    ${CMAKE_CURRENT_LIST_DIR}/messageexchange/src/internal/SmeConnectionStateOverview.h
    ${CMAKE_CURRENT_LIST_DIR}/messageexchange/src/internal/StateHandler.h
    ${CMAKE_CURRENT_LIST_DIR}/messageexchange/src/internal/StateInfo.h
    ${CMAKE_CURRENT_LIST_DIR}/stack/src/SocketConnectionHandler.h
    ${CMAKE_CURRENT_LIST_DIR}/transformer/ClassBuilder.h
    ${CMAKE_CURRENT_LIST_DIR}/transformer/JsonBuilder.h
    ${CMAKE_CURRENT_LIST_DIR}/transformer/JsonParser.h
    ${CMAKE_CURRENT_LIST_DIR}/transformer/ShipDataUtility.h
    ${CMAKE_CURRENT_LIST_DIR}/transformer/ShipControlTransformer.h
    ${CMAKE_CURRENT_LIST_DIR}/transformer/ShipDataTransformer.h
    ${CMAKE_CURRENT_LIST_DIR}/transformer/include/keo_ship/CShipDataClass.h
    ${CMAKE_CURRENT_LIST_DIR}/transformer/include/keo_ship/CShipListClass.h
    ${CMAKE_CURRENT_LIST_DIR}/transformer/include/keo_ship/Data.h
    ${CMAKE_CURRENT_LIST_DIR}/transport/src/ShipSocket.h
    ${CMAKE_CURRENT_LIST_DIR}/transport/src/ShipWss.h
    ${CMAKE_CURRENT_LIST_DIR}/transport/src/WebSocket.h
    ${CMAKE_CURRENT_LIST_DIR}/transport/src/SocketServer.h
    ${CMAKE_CURRENT_LIST_DIR}/transport/src/base64/base64.h
    ${CMAKE_CURRENT_LIST_DIR}/transport/src/tls/ShipOpenSSL.h
    ${CMAKE_CURRENT_LIST_DIR}/transport/src/tls/OpenSSLConnection.h
    ${CMAKE_CURRENT_LIST_DIR}/util/src/ShipTimer.h
    ${CMAKE_CURRENT_LIST_DIR}/util/src/UriInternal.h

  LIST_HDR_PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include/keo_ship/ShipSecurity.h
    ${CMAKE_CURRENT_LIST_DIR}/include/keo_ship/ShipStack.h
    ${CMAKE_CURRENT_LIST_DIR}/include/keo_ship/Uri.h

  LIST_HDR_INTERFACE

  INCLUDE_DIRECTORIES_PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/messageexchange/src
    ${CMAKE_CURRENT_LIST_DIR}/transformer
    ${CMAKE_CURRENT_LIST_DIR}/transformer/include
    ${CMAKE_CURRENT_LIST_DIR}/transformer/include/keo_ship/
    ${CMAKE_CURRENT_LIST_DIR}/transport/src
    ${CMAKE_CURRENT_LIST_DIR}/util/src/
    ${GENERATED_SHIP_DIR}/include
    ${PROJECT_BINARY_DIR}/include

  INCLUDE_DIRECTORIES_PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include

  INCLUDE_DIRECTORIES_INTERFACE

  HDR_INSTALL_DIR include/keo_ship

  LINK_LIBRARIES_PRIVATE
    ${keo_target_tool}
    ${OPENSSL_LIBRARIES}
    pthread

  LINK_LIBRARIES_PUBLIC
    ${keo_target_util}

  LINK_LIBRARIES_INTERFACE

  SDK
)

target_compile_definitions(${keo_target_ship} PRIVATE LOGGER_ID="keo_ship_stack")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  if(NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 7.0.0)
    set_source_files_properties(
      ${CMAKE_CURRENT_LIST_DIR}/messageexchange/src/internal/ConnectionStateHandler.cpp
      ${CMAKE_CURRENT_LIST_DIR}/transport/src/WebSocket.cpp
      ${CMAKE_CURRENT_LIST_DIR}/discovery/src/internal/KEOZeroconf.cpp
      PROPERTIES COMPILE_FLAGS -Wno-error=implicit-fallthrough)
  endif()
endif()


# ============================================================
# Options
# ============================================================

option (SSL_CLOSE_NOTIFY "Use Ship_Security Output Strings" ON)
if (SSL_CLOSE_NOTIFY)
    target_compile_definitions(${keo_target_ship} PRIVATE SSL_CLOSE_NOTIFY)
endif (SSL_CLOSE_NOTIFY)


if (NOT KEO_SRC)
  add_dependencies(${keo_target_ship} ${KEO_PROJECT_PROJECT_NAME}versionfile)
  add_dependencies(${keo_target_ship} RunShipDataBinder)
endif()


# ============================================================
#
# Unit tests
#
# ============================================================
keo_googletest(
    TEST_NAME ${keo_target_ship}_message_exchange

    LIST_SRC
    ${CMAKE_CURRENT_LIST_DIR}/messageexchange/tests/gtest_main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messageexchange/tests/ConnectionStateHandlerExtend.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messageexchange/tests/ConnectionStateHandlerListenerImpl.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messageexchange/tests/ConnectionStateHandlerTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messageexchange/tests/MessageExchangeTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messageexchange/tests/ProtocolConfigTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messageexchange/tests/StateHandlerTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messageexchange/tests/ShipStringUtilTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/messageexchange/tests/ShipByteArrayTest.cpp

    INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_LIST_DIR}/messageexchange/src
    ${CMAKE_CURRENT_LIST_DIR}/messageexchange/src/internal
    ${CMAKE_CURRENT_LIST_DIR}/transformer
    ${CMAKE_CURRENT_LIST_DIR}/transformer/include
    ${CMAKE_CURRENT_LIST_DIR}/transformer/include/keo_ship
    ${CMAKE_CURRENT_LIST_DIR}/util/src
    ${GENERATED_SHIP_DIR}/include

    COMPILE_DEFINITIONS
        LOGGER_ID="${keo_target_ship}_message_exchange_test"

    LINK_LIBRARIES
    ${keo_target_util}
    ${keo_target_ship}
    pthread
    )

keo_googletest(
    TEST_NAME X509Certificate

    LIST_SRC
    ${CMAKE_CURRENT_LIST_DIR}/security/tests/gtest_main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/security/tests/X509CertificateTest.cpp

    COMPILE_DEFINITIONS
    X509_SAMPLES_DIR="${CMAKE_CURRENT_LIST_DIR}/security/tests/samples/"

    INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_LIST_DIR}/messageexchange/src
    ${CMAKE_CURRENT_LIST_DIR}/messageexchange/src/internal
    ${CMAKE_CURRENT_LIST_DIR}/transformer
    ${CMAKE_CURRENT_LIST_DIR}/transformer/include
    ${CMAKE_CURRENT_LIST_DIR}/transformer/include/keo_ship
    ${GENERATED_SHIP_DIR}/include

    COMPILE_DEFINITIONS
        LOGGER_ID="X509Certificate_test"

    LINK_LIBRARIES
    ${keo_target_ship}
    pthread
    )


keo_googletest(
    TEST_NAME ${keo_target_ship}

    LIST_SRC
    ${CMAKE_CURRENT_LIST_DIR}/stack/tests/gtest_main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/stack/tests/StackTest.cpp

    LINK_LIBRARIES
    ${keo_target_ship}
    pthread
    )

keo_googletest(
    TEST_NAME ${keo_target_ship}_transformer

    LIST_SRC
    ${CMAKE_CURRENT_LIST_DIR}/transformer/tests/gtest_main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/transformer/tests/TransformerTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/transformer/tests/ShipMessageTest.cpp

    INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_LIST_DIR}/messageexchange/src
    ${CMAKE_CURRENT_LIST_DIR}/transformer
    ${CMAKE_CURRENT_LIST_DIR}/transformer/include
    ${CMAKE_CURRENT_LIST_DIR}/transformer/include/keo_ship
    ${GENERATED_SHIP_DIR}/include

    LINK_LIBRARIES
    ${keo_target_ship}
    pthread
    )

keo_googletest(
    TEST_NAME ${keo_target_ship}_util

    LIST_SRC
    ${CMAKE_CURRENT_LIST_DIR}/util/tests/gtest_main.cpp
#    ${CMAKE_CURRENT_LIST_DIR}/util/tests/JobStopperTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/util/tests/SkiTest.cpp
#    ${CMAKE_CURRENT_LIST_DIR}/util/tests/ThreadPoolTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/util/tests/UriTest.cpp

    INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_LIST_DIR}/util/src

    LINK_LIBRARIES
    ${keo_target_ship}
    pthread
    )

### RSP ### Disabled for now, until the examples are reordered properly
# set(${TEST_TARGET_NAME}_client_test_key_dir "${CMAKE_CURRENT_BINARY_DIR}/keys/ShipWssTest/client")
# set(${TEST_TARGET_NAME}_server_test_key_dir "${CMAKE_CURRENT_BINARY_DIR}/keys/ShipWssTest/server")
# set(TEST_TARGET_NAME_KEY_MATERIAL_SERVER "${TEST_TARGET_NAME}_test_keys_server")
# set(TEST_TARGET_NAME_KEY_MATERIAL_CLIENT "${TEST_TARGET_NAME}_test_keys_client")
# set(TEST_TARGET_NAME_TRUST_STORE_CLIENT "${TEST_TARGET_NAME}_test_trust_store_client")
# set(TEST_TARGET_NAME_TRUST_STORE_SERVER "${TEST_TARGET_NAME}_test_trust_store_server")

# generate_keymaterial(
#     TARGET ${TEST_TARGET_NAME_KEY_MATERIAL_SERVER}
#     PREFIX server
#     OUTPUT_DIR ${${TEST_TARGET_NAME}_server_test_key_dir}
# )

# generate_keymaterial(
#     TARGET ${TEST_TARGET_NAME_KEY_MATERIAL_CLIENT}
#     PREFIX client
#     OUTPUT_DIR ${${TEST_TARGET_NAME}_client_test_key_dir}
# )

# add_custom_command(
#     OUTPUT  ${${TEST_TARGET_NAME}_client_test_key_dir}/client.truststore.json
#     COMMAND ${CMAKE_COMMAND} -E copy
#             ${CMAKE_CURRENT_LIST_DIR}/empty_trust_entries.json
#             ${${TEST_TARGET_NAME}_client_test_key_dir}/client.truststore.json
#     COMMENT "Copy client truststore"
# )

# add_custom_target(
#     ${TEST_TARGET_NAME_TRUST_STORE_CLIENT}
#     DEPENDS ${${TEST_TARGET_NAME}_client_test_key_dir}/client.truststore.json
# )

# add_custom_command(
#     OUTPUT  ${${TEST_TARGET_NAME}_server_test_key_dir}/server.truststore.json
#     COMMAND ${CMAKE_COMMAND} -E copy
#             ${CMAKE_CURRENT_LIST_DIR}/empty_trust_entries.json
#             ${${TEST_TARGET_NAME}_server_test_key_dir}/server.truststore.json
#     COMMENT "Copy server truststore"
# )

# add_custom_target(
#     ${TEST_TARGET_NAME_TRUST_STORE_SERVER}
#     DEPENDS ${${TEST_TARGET_NAME}_server_test_key_dir}/server.truststore.json
# )
