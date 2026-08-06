
set (CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH} ${GENERATED_INSTALL_DIR} ${GENERATED_BUILD_DIR}")

set(keo_target_spine_datagram_deserializer "spine_datagram_deserializer")

keo_executable(
    EXECUTABLE_NAME
        ${keo_target_spine_datagram_deserializer}

    NO_DOC

    LIST_SRC
        ${CMAKE_CURRENT_LIST_DIR}/main.cpp
        ${CMAKE_CURRENT_LIST_DIR}/FileUtilities.cpp

    LIST_HDR
        ${CMAKE_CURRENT_LIST_DIR}/FileUtilities.h

    LINK_LIBRARIES
        ${GENERATED_INSTALL_DIR}/lib/libkeo_datagram_core.so
    )


target_include_directories(
        ${keo_target_spine_datagram_deserializer}
        PUBLIC
        ${GENERATED_INSTALL_DIR}/include)

add_dependencies(
        ${keo_target_spine_datagram_deserializer}
        BuildDatagramLibrary)
