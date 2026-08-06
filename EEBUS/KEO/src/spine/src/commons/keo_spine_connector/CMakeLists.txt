if (AVAHI_FOUND)
    include(${CMAKE_CURRENT_LIST_DIR}/defaultshiptransport/CMakeLists.txt)
endif (AVAHI_FOUND)

include(${CMAKE_CURRENT_LIST_DIR}/simpleshiptransport/CMakeLists.txt)
