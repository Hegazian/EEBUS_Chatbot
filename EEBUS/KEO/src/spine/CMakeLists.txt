cmake_minimum_required(VERSION 3.9)

set(GENERATED_SHIP_DIR ${CMAKE_CURRENT_LIST_DIR}/generated/GeneratedShip)
set(GENERATED_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/generated/include)
set(KEO_CMAKE_MODULES_ROOT ${CMAKE_CURRENT_LIST_DIR}/cmake )
set(BS_VERSION_MAJOR    12)
set(BS_VERSION_MINOR    0)
set(BS_VERSION_REVISION 3)

set(KEO_SRC ON)
option(CREATE_GOOGLETEST "Create Unit Tests" OFF)
option(CREATE_DOC "Create Doxygen Documentation" OFF)


include(${CMAKE_CURRENT_LIST_DIR}/src/CMakeLists.txt)
