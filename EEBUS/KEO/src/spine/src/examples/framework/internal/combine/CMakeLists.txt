

set(DOXYGEN_EXCLUDE ${DOXYGEN_EXCLUDE} ${CMAKE_CURRENT_LIST_DIR})

if (build_examples AND AVAHI_FOUND)

  # ============================================================
  # Framework client
  # ============================================================

  set(keo_target_framework_combine_app "keo_framework_combine_app")
  keo_executable(
    EXECUTABLE_NAME
    ${keo_target_framework_combine_app}

    LIST_SRC
    ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/SpineShipApplication.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/spine/SpineMeasurement.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/spine/MeasurementClientFeature.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/spine/MeasurementServerFeature.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/ArgParser/src/CmdArgImplStl.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/ArgParser/src/ArgParserStl.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/ArgParser/src/ArgParserImplStl.cpp

    LIST_HDR
    ${CMAKE_CURRENT_LIST_DIR}/src/SpineShipApplication.h
    ${CMAKE_CURRENT_LIST_DIR}/src/spine/SpineMeasurement.h
    ${CMAKE_CURRENT_LIST_DIR}/src/spine/MeasurementClientFeature.h
    ${CMAKE_CURRENT_LIST_DIR}/src/spine/MeasurementServerFeature.h
    ${CMAKE_CURRENT_LIST_DIR}/src/ArgParser/include/ArgParserStl.h

    INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_LIST_DIR}/src/ArgParser/include

    LINK_LIBRARIES
    ${keo_target_json_security_handler}
    ${keo_target_simple_ship_transport}
    ${keo_target_ship_discovery}
    ${keo_target_framework}
    ${keo_target_tool}
    keo_datagram::keo_datagram_measurement
    )

  target_compile_definitions(${keo_target_framework_combine_app} PRIVATE LOGGER_ID="combine_app")



keo_googletest(
    TEST_NAME ArgParser

    INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_LIST_DIR}/src/ArgParser/include

    LIST_SRC
    ${CMAKE_CURRENT_LIST_DIR}/src/ArgParser/tests/gtestmain.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/ArgParser/tests/tests_stl.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/ArgParser/src/CmdArgImplStl.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/ArgParser/src/ArgParserStl.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/ArgParser/src/ArgParserImplStl.cpp

    LINK_LIBRARIES 
    ${keo_target_tool}
  )

endif(build_examples AND AVAHI_FOUND)
