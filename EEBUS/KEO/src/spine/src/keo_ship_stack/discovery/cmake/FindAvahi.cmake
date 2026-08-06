# FindAvahi.cmake

# Find Avahi headers
find_path(AVAHI_INCLUDE_DIR
    NAMES avahi-client/client.h avahi-common/defs.h
    PATHS /usr/include /usr/local/include
)

# Find Avahi client library
find_library(AVAHI_CLIENT_LIBRARIES
    NAMES avahi-client
    PATHS /usr/lib /usr/local/lib
)

# Find Avahi common library
find_library(AVAHI_COMMON_LIBRARIES
    NAMES avahi-common
    PATHS /usr/lib /usr/local/lib
)

# Combine libraries
set(AVAHI_LIBRARIES ${AVAHI_CLIENT_LIBRARIES} ${AVAHI_COMMON_LIBRARIES})

# Handle the QUIETLY and REQUIRED arguments
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Avahi DEFAULT_MSG
    AVAHI_LIBRARIES
    AVAHI_INCLUDE_DIR
)

mark_as_advanced(
    AVAHI_INCLUDE_DIR
    AVAHI_LIBRARIES
    AVAHI_CLIENT_LIBRARIES
    AVAHI_COMMON_LIBRARIES
)