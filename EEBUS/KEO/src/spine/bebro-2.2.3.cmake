SET( SDK_BASE               "/opt/toolchain/sysroots" )
SET( SDK_TARGET_SYSROOT     "${SDK_BASE}/cortexa9hf-neon-bebro-linux-gnueabi" )
SET( SDK_NATIVE_SYSROOT     "${SDK_BASE}/x86_64-plasystemddevsdk-linux" )
SET( SDK_TOOLCHAIN_BASE     "${SDK_NATIVE_SYSROOT}/usr/bin/arm-bebro-linux-gnueabi" )
SET( CHOST                  "arm-bebro-linux-gnueabi" )
SET( TOOLCHAIN_ARCHITECTURE "armv7-a" )
SET( CMAKE_SYSROOT          ${SDK_BASE})

INCLUDE(CMakeForceCompiler)
SET( CMAKE_C_COMPILER ${SDK_TOOLCHAIN_BASE}/${CHOST}-gcc CACHE STRING "C compiler" FORCE )
SET( CMAKE_CXX_COMPILER ${SDK_TOOLCHAIN_BASE}/${CHOST}-g++ CACHE STRING "C++ compiler" FORCE )
SET( CMAKE_C_COMPILER_VERSION   "6.4.0")
SET( CMAKE_CXX_COMPILER_VERSION "6.4.0")
# mandatory
SET( CMAKE_SYSTEM_NAME          Linux)
SET( CMAKE_FIND_ROOT_PATH       "${SDK_TARGET_SYSROOT}" "${SDK_TOOLCHAIN_BASE}" "${SDK_TOOLCHAIN_BASE}/usr/share/aclocal")
SET( CMAKE_PREFIX_PATH           ${SDK_BASE})

set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -march=armv7-a -marm -mfpu=neon  -mfloat-abi=hard -mcpu=cortex-a9 --sysroot=${SDK_TARGET_SYSROOT}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=armv7-a -marm -mfpu=neon  -mfloat-abi=hard -mcpu=cortex-a9 --sysroot=${SDK_TARGET_SYSROOT}")

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER CACHE STRING
    ""
    FORCE )
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY BOTH CACHE STRING
    ""
    FORCE )
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE BOTH CACHE STRING
    ""
    FORCE )

set(LINUX_SOURCE_DIR ${SDK_BASE}/usr/include/linux)

SET(ENV{PKG_CONFIG_PATH} "$ENV{PKG_CONFIG_PATH}:${SDK_BASE}/cortexa9hf-neon-poky-linux-gnueabi/usr/lib/pkgconfig")

# this must not be skipped!
set(CMAKE_C_FLAGS "  ${CMAKE_C_FLAGS}"   CACHE STRING "compiler flags for compiling C sources."   FORCE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" CACHE STRING "compiler flags for compiling CXX sources." FORCE)

MESSAGE(STATUS "CMAKE_TOOLCHAIN_FILE           :  ${CMAKE_TOOLCHAIN_FILE}" )
MESSAGE(STATUS "CMAKE_C_COMPILER_VERSION       :  ${CMAKE_C_COMPILER_VERSION}" )
MESSAGE(STATUS "CMAKE_CXX_COMPILER_VERSION     :  ${CMAKE_CXX_COMPILER_VERSION}" )
MESSAGE(STATUS "CMAKE_EXECUTABLE_FORMAT        :  ${CMAKE_EXECUTABLE_FORMAT}")
MESSAGE(STATUS "CMAKE_FIND_ROOT_PATH           :  ${CMAKE_FIND_ROOT_PATH}" )
