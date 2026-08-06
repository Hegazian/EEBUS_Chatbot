cmake_minimum_required(VERSION 3.9)

set(GENERATED_SPINE_DIR ${CMAKE_CURRENT_LIST_DIR}/src/GeneratedSpine)
set(GENERATED_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/generated/include)
set(SPINE_VERSION_INCLUDE ${CMAKE_CURRENT_LIST_DIR}/generated/include)
set(CMAKE_NON_GEN_BASE_PATH ${CMAKE_CURRENT_LIST_DIR}/src/keo_spine_datagram)
set(KEO_CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake )
set(BS_VERSION_MAJOR 12)
set(BS_VERSION_MINOR 0)
set(BS_VERSION_REVISION 2)

set(KEO_SRC ON)

option(CREATE_GOOGLETEST "Create Unit Tests" OFF)
option(CREATE_DOC "Create Doxygen Documentation" OFF)


include(${CMAKE_CURRENT_LIST_DIR}/src/CMakeLists.txt)
