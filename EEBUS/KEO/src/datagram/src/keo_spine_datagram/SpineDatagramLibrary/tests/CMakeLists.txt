# ======================================================================================================
#
# SPINE Datagram google tests
#
# ======================================================================================================

keo_googletest(
    TEST_NAME BuildDatagramLibrary

    LIST_SRC
    ${CMAKE_CURRENT_LIST_DIR}/gTestMain.cpp
    ${CMAKE_CURRENT_LIST_DIR}/DatagramHelperTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/DatagramTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/CmdTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/HeaderTests.cpp
    ${CMAKE_CURRENT_LIST_DIR}/FeatureAddressTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/AbsoluteOrRelativeTimeTests.cpp
    ${CMAKE_CURRENT_LIST_DIR}/DestinationListTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/DetailedDiscoveryTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/DetailedDiscoveryPartialTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/UseCaseDiscoveryTests.cpp
    ${CMAKE_CURRENT_LIST_DIR}/KeoScaledNumberTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/KeoDurationTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/KeoTimeTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/KeoDateTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/KeoDateTimeTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/KeoByteArrayTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/FilterTests.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SelectorsTests.cpp
    ${CMAKE_CURRENT_LIST_DIR}/DatagramJsonTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/DatagramParseTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/GeneratedClassesTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/KeoJsonTransformationTests.cpp
    ${CMAKE_CURRENT_LIST_DIR}/EnumTest.cpp

    INCLUDE_DIRECTORIES
    ${GENERATED_INSTALL_DIR}/include
    # Allow to unittest private classes
    ${GENERATED_DIR}/

    LINK_LIBRARIES
    ${GENERATED_INSTALL_DIR}/lib/libkeo_datagram_core.so
    ${GENERATED_INSTALL_DIR}/lib/libkeo_datagram_incentivetable.so
    ${GENERATED_INSTALL_DIR}/lib/libkeo_datagram_hvac.so
    ${GENERATED_INSTALL_DIR}/lib/libkeo_datagram_devicediagnosis.so
    ${GENERATED_INSTALL_DIR}/lib/libkeo_datagram_deviceconfiguration.so
    ${GENERATED_INSTALL_DIR}/lib/libkeo_datagram_smartenergymanagementps.so
    ${GENERATED_INSTALL_DIR}/lib/libkeo_datagram_timeinformation.so
    ${GENERATED_INSTALL_DIR}/lib/libkeo_datagram_timetable.so
    ${GENERATED_INSTALL_DIR}/lib/libkeo_datagram_measurement.so
    ${GENERATED_INSTALL_DIR}/lib/libkeo_datagram_operatingconstraints.so
    pthread
    )

add_dependencies(BuildDatagramLibrary_test BuildDatagramLibrary)
