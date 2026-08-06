cmake_minimum_required(VERSION 3.9)

include(CMakeParseArguments)

macro(keo_project)
  #message(DEBUG "---- processing keo_project")

  set(options
    DEBUG
  )

  set(oneValueArgs
    PROJECT_NAME
    VERSION_MAJOR
    VERSION_MINOR
    BUILD_VERSION
    DESCRIPTION
    PACKAGE_NAME
    )

  set(multiValueArgs LANGUAGES)

  CMAKE_PARSE_ARGUMENTS(
    KEO_PROJECT
    "${options}"
    "${oneValueArgs}"
    "${multiValueArgs}"
    ${ARGN}
    )

  if(KEO_PROJECT_DEBUG)
    message(DEBUG " oneValueArgs                  ${oneValueArgs}")
    message(DEBUG " KEO_PROJECT_PROJECT_NAME      ${KEO_PROJECT_PROJECT_NAME}")
    message(DEBUG " KEO_PROJECT_VERSION_MAJOR     ${KEO_PROJECT_VERSION_MAJOR}")
    message(DEBUG " KEO_PROJECT_VERSION_MINOR     ${KEO_PROJECT_VERSION_MINOR}")
    message(DEBUG " KEO_PROJECT_BUILD_VERSION     ${KEO_PROJECT_BUILD_VERSION}")
    message(DEBUG " KEO_PROJECT_PACKAGE_NAME      ${KEO_PROJECT_PACKAGE_NAME}")
    message(DEBUG " KEO_PROJECT_DESCRIPTION       ${KEO_PROJECT_DESCRIPTION}")
    message(DEBUG " KEO_PROJECT_LANGUAGES         ${KEO_PROJECT_LANGUAGES}")
  endif()

  # now we have:
  #
  # KEO_PROJECT_PROJECT_NAME
  # KEO_PROJECT_VERSION_MAJOR
  # KEO_PROJECT_VERSION_MINOR
  # KEO_PROJECT_BUILD_VERSION
  # KEO_PROJECT_PACKAGE_NAME
  # KEO_PROJECT_DESCRIPTION
  # KEO_PROJECT_LANGUAGES

  # ============================================================
  #
  # project settings
  #
  # ============================================================


  project(
    ${KEO_PROJECT_PROJECT_NAME}
    VERSION     ${KEO_PROJECT_VERSION_MAJOR}.${KEO_PROJECT_VERSION_MINOR}.${KEO_PROJECT_BUILD_VERSION}
    DESCRIPTION ${KEO_PROJECT_DESCRIPTION}
    LANGUAGES   ${KEO_PROJECT_LANGUAGES}
    )

  # C++11 required
  include(CheckCXXCompilerFlag)
  CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
  CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
  set (CMAKE_CXX_STANDARD 11)

  # build type
  if(UNIX)
    if (NOT CMAKE_BUILD_TYPE)
      message(STATUS "No build target set! Assume release with debug information.")
      set(CMAKE_BUILD_TYPE RELWITHDEBINFO)
    elseif (CMAKE_BUILD_TYPE STREQUAL MINSIZEREL)
      message(STATUS "Build type MINSIZEREL not supported. Assume release with debug information.")
      set(CMAKE_BUILD_TYPE RELWITHDEBINFO)
    endif()
  endif(UNIX)

  # version information
  set(${PROJECT_NAME}_VERSION_MAJOR ${KEO_PROJECT_VERSION_MAJOR})
  set(${PROJECT_NAME}_VERSION_MINOR ${KEO_PROJECT_VERSION_MINOR})
  set(${PROJECT_NAME}_VERSION_REVISION ${KEO_PROJECT_BUILD_VERSION})
  set(${PROJECT_NAME}_RELEASE_POSTFIX ${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_REVISION})

  # ---------- Setup output Directories -------------------------
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
    ${PROJECT_BINARY_DIR}/bin
    CACHE PATH
    "Single Directory for all dynamic Libraries"
    )

  # --------- Setup the Executable output Directory -------------
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${PROJECT_BINARY_DIR}/bin
    CACHE PATH
    "Single Directory for all Executables."
    )

  # --------- Setup the Executable output Directory -------------
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
    ${PROJECT_BINARY_DIR}/lib
    CACHE PATH
    "Single Directory for all static libraries."
    )


  set(KEO_VERSION_HEADER_PROJECT_NAME ${KEO_PROJECT_PROJECT_NAME})

  if (NOT KEO_SRC)
    include(KEOVersionInformation)

    # keep backwards compatibility
    if (KEO_PROJECT_PACKAGE_NAME)
      set(package_name ${KEO_PROJECT_PACKAGE_NAME})
    else()
      set(package_name ${KEO_PROJECT_PROJECT_NAME})
    endif()

    create_keo_version_header(
      TARGET ${KEO_PROJECT_PROJECT_NAME}versionfile
      VERSION_MAJOR ${KEO_PROJECT_VERSION_MAJOR}
      VERSION_MINOR    ${KEO_PROJECT_VERSION_MINOR}
      VERSION_REVISION ${KEO_PROJECT_BUILD_VERSION}
      PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR}
      PROJECT_NAME ${KEO_VERSION_HEADER_PROJECT_NAME}
      HEADER_DIR ${CMAKE_BINARY_DIR}/include
      HEADER_NAME "${KEO_PROJECT_PROJECT_NAME}Version.h"
      PACKAGE_NAME ${package_name}
      VERSION_STRING "${KEO_PROJECT_PROJECT_NAME}_VERSION"
      VERSION_HEADER "${KEO_PROJECT_PROJECT_NAME}VERSION"
      COMMENT "Create version information for ${CMAKE_CURRENT_SOURCE_DIR}"
      )
  endif()

  include_directories(
    ${PROJECT_BINARY_DIR}/include/
    )

  # ============================================================
  #
  # configuration and compile settings
  #
  # ============================================================

  if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/cmake/Config.cmake.in")
    include(GenerateExportHeader)
    include(CMakePackageConfigHelpers)

    # Configuration
    set(config_install_dir  "lib/cmake/${KEO_PROJECT_PROJECT_NAME}")
    set(generated_dir       "${CMAKE_CURRENT_BINARY_DIR}/generated")
    set(version_config      "${generated_dir}/${KEO_PROJECT_PROJECT_NAME}ConfigVersion.cmake")
    set(project_config      "${generated_dir}/${KEO_PROJECT_PROJECT_NAME}Config.cmake")
    set(targets_export_name "${KEO_PROJECT_PROJECT_NAME}Targets")
    set(namespace           "${KEO_PROJECT_PROJECT_NAME}::")

    write_basic_package_version_file(
      "${version_config}"
      VERSION ${BS_VERSION_MAJOR}.${BS_VERSION_MINOR}.${BS_VERSION_REVISION}
      COMPATIBILITY SameMajorVersion
      )

    # Configure '<PROJECT-NAME>Config.cmake'
    # Use variables:
    #   * targets_export_name
    #   * PROJECT_NAME
    configure_package_config_file(
      "${CMAKE_CURRENT_LIST_DIR}/cmake/Config.cmake.in"
      "${project_config}"
      INSTALL_DESTINATION "${config_install_dir}"
      )

    # Config
    #   * <prefix>/lib/cmake/Foo/FooConfig.cmake
    #   * <prefix>/lib/cmake/Foo/FooConfigVersion.cmake
    install(
      FILES       "${project_config}" "${version_config}"
      DESTINATION "${config_install_dir}"
      COMPONENT ${CPACK_COMPONENT_DEV_GROUP}
      )

    # Config
    install(
      EXPORT      "${targets_export_name}"
      NAMESPACE   "${namespace}"
      DESTINATION "${config_install_dir}"
      COMPONENT ${CPACK_COMPONENT_DEV_GROUP}
      )
  endif()
endmacro(keo_project)

macro(keo_install_release_notes)
  install(FILES
    ${CMAKE_CURRENT_LIST_DIR}/ReleaseNotes.txt
    PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ
    DESTINATION .
    COMPONENT dev
    )

  install(FILES
    ${CMAKE_CURRENT_LIST_DIR}/ReleaseNotes.txt
    PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ
    DESTINATION .
    COMPONENT bin
    )

  install(FILES
    ${CMAKE_CURRENT_LIST_DIR}/ReleaseNotes.txt
    PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ
    DESTINATION .
    COMPONENT ${CPACK_COMPONENT_SDK_GROUP}
    )
endmacro(keo_install_release_notes)

macro(keo_install_readme_md)
  install(FILES
    ${CMAKE_CURRENT_LIST_DIR}/README.md
    PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ
    DESTINATION .
    COMPONENT dev
    )

  install(FILES
    ${CMAKE_CURRENT_LIST_DIR}/README.md
    PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ
    DESTINATION .
    COMPONENT bin
    )

  install(FILES
    ${CMAKE_CURRENT_LIST_DIR}/README.md
    PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ
    DESTINATION .
    COMPONENT ${CPACK_COMPONENT_SDK_GROUP}
    )
endmacro(keo_install_readme_md)

macro(keo_install_license_txt)
  install(FILES
    ${CMAKE_CURRENT_LIST_DIR}/License.txt
    PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ
    DESTINATION .
    COMPONENT dev
    )

  install(FILES
    ${CMAKE_CURRENT_LIST_DIR}/License.txt
    PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ
    DESTINATION .
    COMPONENT bin
    )

  install(FILES
    ${CMAKE_CURRENT_LIST_DIR}/License.txt
    PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ
    DESTINATION .
    COMPONENT ${CPACK_COMPONENT_SDK_GROUP}
    )
endmacro(keo_install_license_txt)

macro(keo_install_package_libraries)
  set(oneValueArgs DESTINATION)

  set(multiValueArgs
    LIBRARIES
    COMPONENTS
    )

  set(options
    NO_CMAKE_FILES
    DEBUG
    )

  CMAKE_PARSE_ARGUMENTS(
    PKG
    "${options}"
    "${oneValueArgs}"
    "${multiValueArgs}"
    ${ARGN}
    )

  if (NOT PKG_DESTINATION)
    set(PKG_DESTINATION "lib")
  endif()

  foreach (tmp_lib ${PKG_LIBRARIES})

    get_target_property(lib_location ${tmp_lib} LOCATION)

    # work around missing cmake capability to install imported targets with soversion
    set(lib_name_x_y_z ${lib_location})
    STRING(REGEX REPLACE "(\\.[0-9]+$)" "" lib_name_x_y ${lib_name_x_y_z})
    STRING(REGEX REPLACE "(\\.[0-9]+$)" "" lib_name_x   ${lib_name_x_y}  )
    STRING(REGEX REPLACE "(\\.[0-9]+$)" "" lib_name     ${lib_name_x}    )

    foreach (tmp_component ${PKG_COMPONENTS})

      install(FILES ${lib_location} ${lib_name} ${lib_name_x}
        DESTINATION ${PKG_DESTINATION}
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
        COMPONENT ${tmp_component}
        )

      if (NOT PKG_NO_CMAKE_FILES)
        get_filename_component(inst_dir ${lib_location} DIRECTORY)

        if(PKG_DEBUG)
          message(DEBUG " installing ${inst_dir}/cmake")
        endif()

        install(DIRECTORY ${inst_dir}/cmake
          DESTINATION ${PKG_DESTINATION}
          USE_SOURCE_PERMISSIONS
          COMPONENT ${tmp_component}
          )
      endif()

    endforeach()

  endforeach()

endmacro()

function(keo_install_target_sources TARGET_)

  get_target_property(
    ${TARGET_}_sources_to_install
    ${TARGET_}
    SOURCES
    )

  foreach(src ${${TARGET_}_sources_to_install})
    #message(DEBUG " ------ handling source file: ${src}")

    if(NOT "${src}" MATCHES "^\\$<INSTALL_INTERFACE:.*>$")

      if("${src}" MATCHES "^\\$<BUILD_INTERFACE:.*>$")
        string(REPLACE "$<BUILD_INTERFACE:" "" src ${src})
        string(REPLACE ">" "" src ${src})
      endif()


      get_source_file_property(
        src_full_path
        ${src}
        LOCATION
        )
      string(REPLACE "${PROJECT_SOURCE_DIR}/" "" src_relative_path ${src_full_path})

      get_filename_component(rel_dir ${src_relative_path} DIRECTORY)

      install(FILES
        ${PROJECT_SOURCE_DIR}/${src_relative_path}
        DESTINATION ${SOURCE_INSTALL_PREFIX}/${rel_dir}
        COMPONENT ${CPACK_COMPONENT_SRC_GROUP}
        )
    endif()

  endforeach()

endfunction()


function(dump_target_property TARGET_ PROPERTY_)

#  message(DEBUG "  Target  : ${TARGET_}")
#  message(DEBUG " Property: ${PROPERTY_}")

  get_property(
    property_is_set
    TARGET ${TARGET_}
    PROPERTY ${PROPERTY_}
    SET
    )

  if (property_is_set)

    get_target_property(
      property_value
      ${TARGET_}
      ${PROPERTY_}
      )

    string (REPLACE ";" "\n        " property_value "${property_value}")
    #message(DEBUG " Value   :\n        ${property_value}")

  else()

    #message(DEBUG " Value   :\n        not set")

  endif()

endfunction()

function(dump_target TARGET_)
    message(DEBUG " =================================================================")
    message(DEBUG " Dumping target properties of target: ${TARGET_}")
    dump_target_property(${TARGET_} NAME)
    dump_target_property(${TARGET_} EXPORT_NAME)
    dump_target_property(${TARGET_} TYPE)
    dump_target_property(${TARGET_} SOURCES)
    dump_target_property(${TARGET_} PRIVATE_HEADER)
    dump_target_property(${TARGET_} PUBLIC_HEADER)
    dump_target_property(${TARGET_} INCLUDE_DIRECTORIES)
    dump_target_property(${TARGET_} INTERFACE_INCLUDE_DIRECTORIES)
    dump_target_property(${TARGET_} INTERFACE_SOURCES)
    dump_target_property(${TARGET_} COMPILE_DEFINITIONS)
    dump_target_property(${TARGET_} COMPILE_FEATURES)
    dump_target_property(${TARGET_} COMPILE_FLAGS)
    dump_target_property(${TARGET_} COMPILE_OPTIONS)
    dump_target_property(${TARGET_} CXX_STANDARD)
    dump_target_property(${TARGET_} LINK_LIBRARIES)
    dump_target_property(${TARGET_} LINK_FLAGS)
    message(DEBUG " =================================================================")
endfunction()

# CMake defaults:
# debug          CXX_FLAGS =     -g
# relwithdebinfo CXX_FLAGS = -O2 -g -DNDEBUG
# minsizerel     CXX_FLAGS = -Os    -DNDEBUG
# release        CXX_FLAGS = -O3    -DNDEBUG

# get rid of -O3, it does not work with all toolchains
macro(remove_cxx_flag flag)
  string(REPLACE "${flag}" "" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
endmacro()

remove_cxx_flag("-O3")


if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    SET(KEO_CMAKE_COMPILE_OPTIONS_BASE          "-pipe -fdiagnostics-show-option -Werror -Wall ")
else()
    SET(KEO_CMAKE_COMPILE_OPTIONS_BASE          "-pipe -fdiagnostics-show-option -Werror -Wall -Wno-psabi ")
endif()
if(KEO_RELAXED_WARNINGS)
  message(WARNING " Using relaxed KEO compile options: do NOT set -Wpedantic -Wextra")
else()
  SET(KEO_CMAKE_COMPILE_OPTIONS_BASE        "${KEO_CMAKE_COMPILE_OPTIONS_BASE} -Wpedantic -Wextra ")
endif()

SET(KEO_CMAKE_COMPILE_OPTIONS_DEBUG          ${KEO_CMAKE_COMPILE_OPTIONS_BASE} "-D_DEBUG -Og")
SET(KEO_CMAKE_COMPILE_OPTIONS_RELWITHDEBINFO ${KEO_CMAKE_COMPILE_OPTIONS_BASE} "-D_DEBUG")
SET(KEO_CMAKE_COMPILE_OPTIONS_RELEASE        ${KEO_CMAKE_COMPILE_OPTIONS_BASE} "-O2")
SET(KEO_CMAKE_COMPILE_OPTIONS_MINSIZE_REL    ${KEO_CMAKE_COMPILE_OPTIONS_BASE})



message(INFO " To override KEO compiler options set the following variables after including KEOProject.cmake:")
message(INFO "")
message(INFO "    KEO_CMAKE_COMPILE_OPTIONS_DEBUG")
message(INFO "    KEO_CMAKE_COMPILE_OPTIONS_RELWITHDEBINFO")
message(INFO "    KEO_CMAKE_COMPILE_OPTIONS_RELEASE")
message(INFO "    KEO_CMAKE_COMPILE_OPTIONS_MINSIZE_REL")

#-fPIC
set (CMAKE_POSITION_INDEPENDENT_CODE ON)

function(keo_compile_options TARGET_)
  string(REPLACE " " ";" opt_tmp ${KEO_CMAKE_COMPILE_OPTIONS_DEBUG})
  target_compile_options(${TARGET_} PRIVATE $<$<CONFIG:DEBUG>:${opt_tmp}>)

  string(REPLACE " " ";" opt_tmp ${KEO_CMAKE_COMPILE_OPTIONS_RELWITHDEBINFO})
  target_compile_options(${TARGET_} PRIVATE $<$<CONFIG:RELWITHDEBINFO>:${opt_tmp}>)

  string(REPLACE " " ";" opt_tmp ${KEO_CMAKE_COMPILE_OPTIONS_RELEASE})
  target_compile_options(${TARGET_} PRIVATE $<$<CONFIG:RELEASE>:${opt_tmp}>)

  string(REPLACE " " ";" opt_tmp ${KEO_CMAKE_COMPILE_OPTIONS_MINSIZE_REL})
  target_compile_options(${TARGET_} PRIVATE $<$<CONFIG:MINSIZE_REL>:${opt_tmp}>)

endfunction()

macro(keo_library)

  set(oneValueArgs
    LIBRARY_NAME
    EXPORT_NAME
    HDR_RELATIVE_INSTALL_BASE_DIR
    HDR_INSTALL_DIR
    )

  set(multiValueArgs
    LIBRARY_TYPE
    LIST_SRC
    LIST_HDR_PRIVATE
    LIST_HDR_PUBLIC
    LIST_HDR_INTERFACE
    INCLUDE_DIRECTORIES_PRIVATE
    INCLUDE_DIRECTORIES_PUBLIC
    INCLUDE_DIRECTORIES_INTERFACE
    LINK_OBJECT_LIBRARIES
    LINK_LIBRARIES
    LINK_LIBRARIES_PRIVATE
    LINK_LIBRARIES_PUBLIC
    LINK_LIBRARIES_INTERFACE
    )

  set(options
    DEBUG
    SDK
    )

  CMAKE_PARSE_ARGUMENTS(
    KEO_LIBRARY
    "${options}"
    "${oneValueArgs}"
    "${multiValueArgs}"
    ${ARGN}
    )

  if (KEO_LIBRARY_DEBUG)
    message(DEBUG " cmake_current_list_dir                    ${CMAKE_CURRENT_LIST_DIR}")
    message(DEBUG " oneValueArgs                              ${oneValueArgs}")
    message(DEBUG " KEO_LIBRARY_LIBRARY_NAME                  ${KEO_LIBRARY_LIBRARY_NAME}")
    message(DEBUG " KEO_LIBRARY_LIBRARY_TYPE                  ${KEO_LIBRARY_LIBRARY_TYPE}")
    message(DEBUG " KEO_LIBRARY_EXPORT_NAME                   ${KEO_LIBRARY_EXPORT_NAME}")
    message(DEBUG " KEO_LIBRARY_LIST_SRC                      ${KEO_LIBRARY_LIST_SRC}")
    message(DEBUG " KEO_LIBRARY_LIST_HDR_PRIVATE              ${KEO_LIBRARY_LIST_HDR_PRIVATE}")
    message(DEBUG " KEO_LIBRARY_LIST_HDR_PUBLIC               ${KEO_LIBRARY_LIST_HDR_PUBLIC}")
    message(DEBUG " KEO_LIBRARY_LIST_HDR_INTERFACE            ${KEO_LIBRARY_LIST_HDR_INTERFACE}")
    message(DEBUG " KEO_LIBRARY_INCLUDE_DIRECTORIES_PRIVATE   ${KEO_LIBRARY_INCLUDE_DIRECTORIES_PRIVATE}")
    message(DEBUG " KEO_LIBRARY_INCLUDE_DIRECTORIES_PUBLIC    ${KEO_LIBRARY_INCLUDE_DIRECTORIES_PUBLIC}")
    message(DEBUG " KEO_LIBRARY_INCLUDE_DIRECTORIES_INTERFACE ${KEO_LIBRARY_INCLUDE_DIRECTORIES_INTERFACE}")
    message(DEBUG " KEO_LIBRARY_HDR_INSTALL_DIR               ${KEO_LIBRARY_HDR_INSTALL_DIR}")
    message(DEBUG " KEO_LIBRARY_HDR_RELATIVE_INSTALL_BASE_DIR ${KEO_LIBRARY_HDR_RELATIVE_INSTALL_BASE_DIR}")
    message(DEBUG " KEO_LIBRARY_LINK_OBJECT_LIBRARIES         ${KEO_LIBRARY_LINK_OBJECT_LIBRARIES}")
    message(DEBUG " KEO_LIBRARY_LINK_LIBRARIES                ${KEO_LIBRARY_LINK_LIBRARIES}")
  endif()

  # now we have:
  #
  # KEO_LIBRARY_LIBRARY_NAME
  # KEO_LIBRARY_LIBRARY_TYPE
  # KEO_LIBRARY_EXPORT_NAME
  # KEO_LIBRARY_LIST_SRC
  # KEO_LIBRARY_LIST_HDR_PRIVATE
  # KEO_LIBRARY_LIST_HDR_PUBLIC
  # KEO_LIBRARY_LIST_HDR_INTERFACE
  # KEO_LIBRARY_INCLUDE_DIRECTORIES_PRIVATE
  # KEO_LIBRARY_INCLUDE_DIRECTORIES_PUBLIC
  # KEO_LIBRARY_INCLUDE_DIRECTORIES_INTERFACE
  # KEO_LIBRARY_HDR_INSTALL_DIR
  # KEO_LIBRARY_HDR_RELATIVE_INSTALL_BASE_DIR
  # KEO_LIBRARY_LINK_OBJECT_LIBRARIES
  # KEO_LIBRARY_LINK_LIBRARIES

  if (KEO_LIBRARY_LINK_OBJECT_LIBRARIES)
    set(OBJECTS_TMP $<TARGET_OBJECTS:${KEO_LIBRARY_LINK_OBJECT_LIBRARIES}>)
  else()
    set(OBJECTS_TMP "")
  endif()

  # declare the target
  add_library(${KEO_LIBRARY_LIBRARY_NAME}
    ${KEO_LIBRARY_LIBRARY_TYPE}
    ${OBJECTS_TMP} ""
    )

  # generate shared objects with version
  set_target_properties(${KEO_LIBRARY_LIBRARY_NAME}
    PROPERTIES
    VERSION   ${${PROJECT_NAME}_RELEASE_POSTFIX}
    SOVERSION ${${PROJECT_NAME}_VERSION_MAJOR}  )

  # set our compiler options
  keo_compile_options(${KEO_LIBRARY_LIBRARY_NAME})

  # set private source files
  target_sources(${KEO_LIBRARY_LIBRARY_NAME}
    PRIVATE    ${KEO_LIBRARY_LIST_SRC} ${KEO_LIBRARY_LIST_HDR_PRIVATE}
    )

  ############################################################
  #
  #                      target headers
  #
  ############################################################

  unset(headers_to_install)

  ###############################
  # public headers
  ###############################
  foreach(hdr_tmp ${KEO_LIBRARY_LIST_HDR_PUBLIC})
    # if we want to keep the directory structure form the source tree
    # it gets tricky ...
    if (KEO_LIBRARY_HDR_RELATIVE_INSTALL_BASE_DIR)
      # save full filename in a  list
      list(APPEND headers_to_install ${hdr_tmp})

      # strip the base directory
      string(REPLACE "${KEO_LIBRARY_HDR_RELATIVE_INSTALL_BASE_DIR}/" "" hdr_tmp_file_name ${hdr_tmp})
    else()
      # flat installation
      # strip everything, keep only the filename
      get_filename_component(hdr_tmp_file_name ${hdr_tmp} NAME)
    endif()

    # populate the target sources property with the interface headers
    # the headers are used in two ways:
    # 1) library build time
    # 2) build of the application the uses the library later
    # the generator expression is used to distinguish between library build time
    # and installation time
    target_sources(${KEO_LIBRARY_LIBRARY_NAME}
      PUBLIC
      $<BUILD_INTERFACE:${hdr_tmp}>
      $<INSTALL_INTERFACE:${KEO_LIBRARY_HDR_INSTALL_DIR}/${hdr_tmp_file_name}>
      )

    # populate doxygen input
    set(DOXYGEN_INPUT ${DOXYGEN_INPUT} ${hdr_tmp})

  endforeach()

  ###############################
  # interface headers
  ###############################
  foreach(hdr_tmp ${KEO_LIBRARY_LIST_HDR_INTERFACE})

    # if we want to keep the directory structure form the source tree
    # it gets tricky ...
    if (KEO_LIBRARY_HDR_RELATIVE_INSTALL_BASE_DIR)
      # save full filename in a  list
      list(APPEND headers_to_install ${hdr_tmp})

      # strip the base directory
      string(REPLACE "${KEO_LIBRARY_HDR_RELATIVE_INSTALL_BASE_DIR}/" "" hdr_tmp_file_name ${hdr_tmp})
    else()
      # flat installation
      # strip everything, keep only the filename
      get_filename_component(hdr_tmp_file_name ${hdr_tmp} NAME)
    endif()

    # populate the target sources property with the interface headers
    # the headers are used in two ways:
    # 1) library build time
    # 2) build of the application the uses the library later
    # the generator expression is used to distinguish between library build time
    # and installation time
    target_sources(${KEO_LIBRARY_LIBRARY_NAME}
      INTERFACE
      $<BUILD_INTERFACE:${hdr_tmp}>
      $<INSTALL_INTERFACE:${KEO_LIBRARY_HDR_INSTALL_DIR}/${hdr_tmp_file_name}>
      )

    # populate doxygen input
    set(DOXYGEN_INPUT ${DOXYGEN_INPUT} ${hdr_tmp})

  endforeach()

  ############################################################
  #
  #                handle include directories
  #
  ############################################################

  ###############################
  # private
  ###############################
  target_include_directories(${KEO_LIBRARY_LIBRARY_NAME}
    PRIVATE   ${KEO_LIBRARY_INCLUDE_DIRECTORIES_PRIVATE}
    )

  ###############################
  # public
  ###############################
  foreach(dir_tmp ${KEO_LIBRARY_INCLUDE_DIRECTORIES_PUBLIC})
    target_include_directories(${KEO_LIBRARY_LIBRARY_NAME} PUBLIC
      $<BUILD_INTERFACE:${dir_tmp}>
      $<INSTALL_INTERFACE:${KEO_LIBRARY_HDR_INSTALL_DIR}>
      )
  endforeach()

  ###############################
  # interface
  ###############################
  foreach(dir_tmp ${KEO_LIBRARY_INCLUDE_DIRECTORIES_INTERFACE})
    target_include_directories(${KEO_LIBRARY_LIBRARY_NAME} INTERFACE
      $<BUILD_INTERFACE:${dir_tmp}>
      $<INSTALL_INTERFACE:${KEO_LIBRARY_HDR_INSTALL_DIR}>
      )
  endforeach()

  ###############################
  # object libraries
  ###############################
  if (KEO_LIBRARY_LINK_OBJECT_LIBRARIES)
    foreach(objlib_tmp ${KEO_LIBRARY_LINK_OBJECT_LIBRARIES})

      get_target_property(
        objlib_incdirs
        ${objlib_tmp}
        INCLUDE_DIRECTORIES
        )

      foreach(dir_tmp ${objlib_incdirs})
        get_filename_component(dir_tmp_file_name ${dir_tmp} NAME)
        target_include_directories(${KEO_LIBRARY_LIBRARY_NAME} PUBLIC
          $<BUILD_INTERFACE:${dir_tmp}>
          $<INSTALL_INTERFACE:${KEO_LIBRARY_HDR_INSTALL_DIR}>
          )
      endforeach()

    endforeach()
  endif()

  ############################################################
  #
  #         handle link libraries and installation
  #
  ############################################################

  # not for object libraries
  if (NOT ${KEO_LIBRARY_LIBRARY_TYPE} STREQUAL "OBJECT")

    if (KEO_LIBRARY_LINK_LIBRARIES)
      # all in one argument
      target_link_libraries(${KEO_LIBRARY_LIBRARY_NAME}
        ${KEO_LIBRARY_LINK_LIBRARIES}
        )
    else()
      # distinguish private, public, interface
      target_link_libraries(${KEO_LIBRARY_LIBRARY_NAME}
        PRIVATE   ${KEO_LIBRARY_LINK_LIBRARIES_PRIVATE}
        PUBLIC    ${KEO_LIBRARY_LINK_LIBRARIES_PUBLIC}
        INTERFACE ${KEO_LIBRARY_LINK_LIBRARIES_INTERFACE}
        )
    endif()

    # install target
    install(TARGETS ${KEO_LIBRARY_LIBRARY_NAME}
      EXPORT ${KEO_LIBRARY_EXPORT_NAME}
      PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ
      LIBRARY DESTINATION lib COMPONENT ${CPACK_COMPONENT_DEV_GROUP}
      ARCHIVE DESTINATION lib COMPONENT ${CPACK_COMPONENT_DEV_GROUP}
      RUNTIME DESTINATION bin COMPONENT ${CPACK_COMPONENT_DEV_GROUP}
      PUBLIC_HEADER DESTINATION include
      INCLUDES DESTINATION include
      )

    # install dynamic libraries additionally in bin group
    install(TARGETS ${KEO_LIBRARY_LIBRARY_NAME}
      PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ
      ARCHIVE DESTINATION lib COMPONENT ${CPACK_COMPONENT_BIN_GROUP}
      LIBRARY DESTINATION lib COMPONENT ${CPACK_COMPONENT_BIN_GROUP}
      )

    if (KEO_LIBRARY_SDK)
        install(TARGETS ${KEO_LIBRARY_LIBRARY_NAME}
            PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ
            ARCHIVE DESTINATION lib COMPONENT ${CPACK_COMPONENT_SDK_GROUP}
            LIBRARY DESTINATION lib COMPONENT ${CPACK_COMPONENT_SDK_GROUP}
        )

        install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/Export/lib/cmake
            DESTINATION lib
            USE_SOURCE_PERMISSIONS
            COMPONENT ${CPACK_COMPONENT_SDK_GROUP}
        )
    endif()

  endif()


  ############################################################
  #
  #                      install headers
  #
  ############################################################

  if (NOT KEO_LIBRARY_HDR_RELATIVE_INSTALL_BASE_DIR)

    # first, check if out property is set
    get_property(
      ${KEO_LIBRARY_LIBRARY_NAME}_files_to_install_is_set
      TARGET ${KEO_LIBRARY_LIBRARY_NAME}
      PROPERTY INTERFACE_SOURCES
      SET
      )

    # check for interface headers
    if (${KEO_LIBRARY_LIBRARY_NAME}_files_to_install_is_set)

      # get header files to install from target
      get_target_property(
        ${KEO_LIBRARY_LIBRARY_NAME}_files_to_install
        ${KEO_LIBRARY_LIBRARY_NAME}
        INTERFACE_SOURCES
        )

      # and intall them flat
      install(FILES
        ${${KEO_LIBRARY_LIBRARY_NAME}_files_to_install}
        PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ
        DESTINATION ${KEO_LIBRARY_HDR_INSTALL_DIR}
        COMPONENT ${CPACK_COMPONENT_DEV_GROUP}
        )

        if (KEO_LIBRARY_SDK)
            install(FILES
                ${${KEO_LIBRARY_LIBRARY_NAME}_files_to_install}
                PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ
                DESTINATION ${KEO_LIBRARY_HDR_INSTALL_DIR}
                COMPONENT ${CPACK_COMPONENT_SDK_GROUP}
            )
        endif()
    endif()
  else()

    # tricky part: we want to maintain the directory structure from the source tree

    # iterate over our list with complete filenames of headers to install
    foreach(hdr ${headers_to_install})

      # strip the base directory at front
      string(REPLACE "${KEO_LIBRARY_HDR_RELATIVE_INSTALL_BASE_DIR}/" "" hdr_relative ${hdr})

      # strip the filename at the end to get the subdirectory
      get_filename_component(subdir ${hdr_relative} DIRECTORY)

      # install into the subdirectory
      install(FILES
        ${hdr}
        PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ
        DESTINATION "${KEO_LIBRARY_HDR_INSTALL_DIR}/${subdir}"
        COMPONENT ${CPACK_COMPONENT_DEV_GROUP}
        )

      if (KEO_LIBRARY_SDK)
        install(FILES
          ${hdr}
          PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ
          DESTINATION "${KEO_LIBRARY_HDR_INSTALL_DIR}/${subdir}"
          COMPONENT ${CPACK_COMPONENT_SDK_GROUP}
          )
      endif()
    endforeach()

  endif()

  # set convenience variable for dependent keo modules
  get_property(
    ${KEO_LIBRARY_LIBRARY_NAME}_interface_include_directories_is_set
    TARGET ${KEO_LIBRARY_LIBRARY_NAME}
    PROPERTY INTERFACE_INCLUDE_DIRECTORIES
    SET
    )

  if (${KEO_LIBRARY_LIBRARY_NAME}_interface_include_directories_is_set)
    get_target_property(
      ${KEO_LIBRARY_LIBRARY_NAME}_interface_include_directories
      ${KEO_LIBRARY_LIBRARY_NAME}
      INTERFACE_INCLUDE_DIRECTORIES
      )
  endif()

  # debug output
  if (KEO_LIBRARY_DEBUG)
    dump_target(${KEO_LIBRARY_LIBRARY_NAME})
  endif()

endmacro(keo_library)


macro(keo_executable)

  set(oneValueArgs
    EXECUTABLE_NAME
    )

  set(multiValueArgs
    LIST_SRC
    LIST_HDR
    INCLUDE_DIRECTORIES
    LINK_LIBRARIES
    )

  set(options
    NO_DOC
    NO_INSTALL
    DEBUG
    SDK
    )

  CMAKE_PARSE_ARGUMENTS(
    KEO_EXECUTABLE
    "${options}"
    "${oneValueArgs}"
    "${multiValueArgs}"
    ${ARGN}
    )

  if (KEO_EXECUTABLE_DEBUG)
    message(DEBUG " oneValueArgs                       ${oneValueArgs}")
    message(DEBUG " KEO_EXECUTABLE_EXECUTABLE_NAME     ${KEO_EXECUTABLE_EXECUTABLE_NAME}")
    message(DEBUG " KEO_EXECUTABLE_LIST_SRC            ${KEO_EXECUTABLE_LIST_SRC}")
    message(DEBUG " KEO_EXECUTABLE_LIST_HDR            ${KEO_EXECUTABLE_LIST_HDR}")
    message(DEBUG " KEO_EXECUTABLE_INCLUDE_DIRECTORIES ${KEO_EXECUTABLE_INCLUDE_DIRECTORIES}")
    message(DEBUG " KEO_EXECUTABLE_LINK_LIBRARIES      ${KEO_EXECUTABLE_LINK_LIBRARIES}")
  endif()

  # now we have:
  #
  # KEO_EXECUTABLE_EXECUTABLE_NAME
  # KEO_EXECUTABLE_LIST_SRC
  # KEO_EXECUTABLE_LIST_HDR
  # KEO_EXECUTABLE_INCLUDE_DIRECTORIES
  # KEO_EXECUTABLE_LINK_LIBRARIES

  add_executable(${KEO_EXECUTABLE_EXECUTABLE_NAME}
    ${KEO_EXECUTABLE_LIST_SRC}
    ${KEO_EXECUTABLE_LIST_HDR}
    )

  keo_compile_options(${KEO_EXECUTABLE_EXECUTABLE_NAME})
  if (KEO_EXECUTABLE_INCLUDE_DIRECTORIES)
    target_include_directories(${KEO_EXECUTABLE_EXECUTABLE_NAME} PRIVATE
      ${KEO_EXECUTABLE_INCLUDE_DIRECTORIES}
      )
  endif()

  target_link_libraries(${KEO_EXECUTABLE_EXECUTABLE_NAME}
    ${KEO_EXECUTABLE_LINK_LIBRARIES}
    )

  if (NOT KEO_EXECUTABLE_NO_INSTALL)
    install(TARGETS ${KEO_EXECUTABLE_EXECUTABLE_NAME}
      PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ
      LIBRARY DESTINATION lib COMPONENT ${CPACK_COMPONENT_BIN_GROUP}
      ARCHIVE DESTINATION lib COMPONENT ${CPACK_COMPONENT_DEV_GROUP}
      RUNTIME DESTINATION bin COMPONENT ${CPACK_COMPONENT_BIN_GROUP}
      )
  endif()

  if (NOT KEO_EXECUTABLE_NO_DOC)
    set(DOXYGEN_INPUT ${DOXYGEN_INPUT} ${KEO_EXECUTABLE_LIST_HDR})
  endif()

  if (KEO_EXECUTABLE_DEBUG)
    dump_target(${KEO_EXECUTABLE_EXECUTABLE_NAME})
  endif()

  if (KEO_EXECUTABLE_SDK)
    install(TARGETS ${KEO_EXECUTABLE_EXECUTABLE_NAME}
      PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ
      RUNTIME DESTINATION bin COMPONENT ${CPACK_COMPONENT_SDK_GROUP}
      )
  endif()

endmacro(keo_executable)

macro(keo_source_package)

  set(oneValueArgs
    BASE_DIR
    )

  set(multiValueArgs
    ADDITIONAL_EXCLUDES
    )

  set(options
    )

  CMAKE_PARSE_ARGUMENTS(
    KEO_SRC
    "${options}"
    "${oneValueArgs}"
    "${multiValueArgs}"
    ${ARGN}
    )

  # source tree, release notes and scm are private
  INSTALL(DIRECTORY
    ${KEO_SRC_BASE_DIR}
    DESTINATION src
    USE_SOURCE_PERMISSIONS
    COMPONENT ${CPACK_COMPONENT_SRC_GROUP}
    PATTERN buildsystem.json EXCLUDE
    PATTERN ReleaseNotes.txt EXCLUDE
    PATTERN ReleaseNotes_src.txt EXCLUDE
    PATTERN Readme_src.txt EXCLUDE
    PATTERN CMakeLists_src.txt EXCLUDE
    PATTERN .git EXCLUDE
    PATTERN .gitignore EXCLUDE
    PATTERN .gitmodules EXCLUDE
    PATTERN .gitattributes EXCLUDE
    PATTERN .project EXCLUDE
    ${KEO_SRC_ADDITIONAL_EXCLUDES}
    )

  set(RELEASE_NOTES ${CMAKE_CURRENT_BINARY_DIR}/ReleaseNotes_for_src_package.txt)
  file(WRITE ${RELEASE_NOTES} "source package")

  install(FILES
    ${RELEASE_NOTES}
    DESTINATION src
    PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
    COMPONENT ${CPACK_COMPONENT_SRC_GROUP}
    RENAME ReleaseNotes.txt
    )

  install(FILES
    Readme_src.txt
    DESTINATION .
    PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
    COMPONENT ${CPACK_COMPONENT_SRC_GROUP}
    RENAME Readme.txt
    )

  # Replace version information on copy automatically
  configure_file(CMakeLists_src.txt ${CMAKE_CURRENT_BINARY_DIR}/CMakeLists_src.txt @ONLY)

  install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/CMakeLists_src.txt
    DESTINATION .
    PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
    COMPONENT ${CPACK_COMPONENT_SRC_GROUP}
    RENAME CMakeLists.txt
    )
endmacro(keo_source_package)

macro(keo_source_package_additional_directories)
  set(oneValueArgs DST_DIR)
  set(multiValueArgs SRC_DIRS EXCLUDES)
  set(options)
  CMAKE_PARSE_ARGUMENTS(KEO_SRC_DIRS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  INSTALL(
    DIRECTORY   ${KEO_SRC_DIRS_SRC_DIRS}
    DESTINATION ${KEO_SRC_DIRS_DST_DIR}
    USE_SOURCE_PERMISSIONS
    COMPONENT ${CPACK_COMPONENT_SRC_GROUP}
    ${KEO_SRC_DIRS_EXCLUDES}
    )
endmacro(keo_source_package_additional_directories)

macro(keo_source_package_additional_files)
  set(oneValueArgs   DST_DIR)
  set(multiValueArgs SRC_FILES)
  set(options)
  CMAKE_PARSE_ARGUMENTS(KEO_SRC_FILES "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  INSTALL(
    FILES       ${KEO_SRC_FILES_SRC_FILES}
    DESTINATION ${KEO_SRC_FILES_DST_DIR}
    PERMISSIONS OWNER_WRITE OWNER_READ GROUP_WRITE GROUP_READ WORLD_READ
    COMPONENT   ${CPACK_COMPONENT_SRC_GROUP}
    )
endmacro(keo_source_package_additional_files)

macro(GENERATE_KEYMATERIAL)

  set(oneValueArgs
    TARGET
    PREFIX
    OUTPUT_DIR)

  set(multiValueArgs)

  CMAKE_PARSE_ARGUMENTS(
    KEYMATERIAL
    "${options}"
    "${oneValueArgs}"
    "${multiValueArgs}"
    ${ARGN})

  message(DEBUG " oneValueArgs                                 ${oneValueArgs}")
  message(DEBUG " KEYMATERIAL_TARGET                           ${KEYMATERIAL_TARGET}")
  message(DEBUG " KEYMATERIAL_PREFIX                           ${KEYMATERIAL_PREFIX}")
  message(DEBUG " KEYMATERIAL_OUTPUT_DIR                       ${KEYMATERIAL_OUTPUT_DIR}")

  set(SSL_PREFIX   "secp256r1")
  set(SSL_KEY_BIN  "${KEYMATERIAL_PREFIX}.${SSL_PREFIX}KeyDER.bin")
  set(SSL_CERT_BIN "${KEYMATERIAL_PREFIX}.${SSL_PREFIX}CertDER.bin")
  set(SSL_OUTPUT   ${KEYMATERIAL_OUTPUT_DIR}/${SSL_KEY_BIN} ${KEYMATERIAL_OUTPUT_DIR}/${SSL_CERT_BIN})

  file(MAKE_DIRECTORY ${KEYMATERIAL_OUTPUT_DIR})

  set (SSL_CMDLINE_1
    ecparam -out ${SSL_PREFIX}params.pem -name ${SSL_PREFIX} -conv_form compressed -genkey
    )

  set (SSL_CMDLINE_2
    req -x509 -newkey ec:${SSL_PREFIX}params.pem
    -keyform PEM -keyout ${SSL_PREFIX}KeyDER.pem
    -outform PEM
    -out ${SSL_PREFIX}CertDER.pem
    -days 3650
    -set_serial 1234
    -nodes
    -batch
    )

  set (SSL_CMDLINE_3
    x509 -in ${SSL_PREFIX}CertDER.pem -inform PEM -out ${SSL_CERT_BIN} -outform DER
    )

  set (SSL_CMDLINE_4
    ec   -in ${SSL_PREFIX}KeyDER.pem              -out ${SSL_KEY_BIN}  -outform DER
    )


  # generate key material
  add_custom_command(
    OUTPUT ${SSL_OUTPUT}
    COMMAND rm -f ${SSL_PREFIX}*
    COMMAND openssl ${SSL_CMDLINE_1}
    COMMAND openssl ${SSL_CMDLINE_2}
    COMMAND openssl ${SSL_CMDLINE_3}
    COMMAND openssl ${SSL_CMDLINE_4}
    COMMAND rm -f ${SSL_PREFIX}CertDER.pem ${SSL_PREFIX}KeyDER.pem ${SSL_PREFIX}params.pem
    WORKING_DIRECTORY ${KEYMATERIAL_OUTPUT_DIR}
    COMMENT "*******************Generate Key Material in ${KEYMATERIAL_OUTPUT_DIR}"
    )

  add_custom_target(
    ${KEYMATERIAL_TARGET}
    DEPENDS ${SSL_OUTPUT}
    )

endmacro(GENERATE_KEYMATERIAL)


macro(keo_docker)

  set(options "")

  set(oneValueArgs
    IMAGE_NAME
    FROM
    FILES_DIRECTORY
    ADDITIONAL_PROVISIONING_STEPS
    ADDITIONAL_PACKAGES
    )

  set(multiValueArgs
    )

  CMAKE_PARSE_ARGUMENTS(
    KEO_DOCKER
    "${options}"
    "${oneValueArgs}"
    "${multiValueArgs}"
    ${ARGN}
    )

  set(${KEO_DOCKER_IMAGE_NAME}_workdir ${PROJECT_BINARY_DIR}/docker-${KEO_DOCKER_IMAGE_NAME})

  message(DEBUG " oneValueArgs                                 ${oneValueArgs}")
  message(DEBUG " KEO_DOCKER_IMAGE_NAME                        ${KEO_DOCKER_IMAGE_NAME}")
  message(DEBUG " KEO_DOCKER_FROM                              ${KEO_DOCKER_FROM}")
  message(DEBUG " KEO_DOCKER_FILES_DIRECTORY                   ${KEO_DOCKER_FILES_DIRECTORY}")
  message(DEBUG " KEO_DOCKER_ADDITIONAL_PROVISIONING_STEPS     ${KEO_DOCKER_ADDITIONAL_PROVISIONING_STEPS}")
  message(DEBUG " KEO_DOCKER_ADDITIONAL_PACKAGES               ${KEO_DOCKER_ADDITIONAL_PACKAGES}")
  message(DEBUG " Working directory                            ${${KEO_DOCKER_IMAGE_NAME}_workdir}")

  set(SSL_PREFIX   "secp256r1")
  set(SSL_KEY_BIN  "${SSL_PREFIX}KeyDER.bin")
  set(SSL_CERT_BIN "${SSL_PREFIX}CertDER.bin")

  set(SSL_OUTPUT   ${KEO_DOCKER_IMAGE_NAME}_workdir/${SSL_KEY_BIN} ${KEO_DOCKER_IMAGE_NAME}_workdir/${SSL_CERT_BIN})

  set (SSL_CMDLINE_1
    ecparam -out ${SSL_PREFIX}params.pem -name ${SSL_PREFIX} -conv_form compressed -genkey
    )

  set (SSL_CMDLINE_2
    req -x509 -newkey ec:${SSL_PREFIX}params.pem
    -keyform PEM -keyout ${SSL_PREFIX}KeyDER.pem
    -outform PEM
    -out ${SSL_PREFIX}CertDER.pem
    -days 3650
    -set_serial 1234
    -nodes
    -batch
    )

  set (SSL_CMDLINE_3
    x509 -in ${SSL_PREFIX}CertDER.pem -inform PEM -out ${SSL_CERT_BIN} -outform DER
    )

  set (SSL_CMDLINE_4
    ec   -in ${SSL_PREFIX}KeyDER.pem              -out ${SSL_KEY_BIN}  -outform DER
    )

  # generate key material
  add_custom_command(
    OUTPUT ${SSL_OUTPUT}
    COMMAND rm -f ${SSL_PREFIX}*
    COMMAND openssl ${SSL_CMDLINE_1}
    COMMAND openssl ${SSL_CMDLINE_2}
    COMMAND openssl ${SSL_CMDLINE_3}
    COMMAND openssl ${SSL_CMDLINE_4}
    WORKING_DIRECTORY ${${KEO_DOCKER_IMAGE_NAME}_workdir}
    COMMENT "Generate Key Material"
    )

  add_custom_target(
    GenerateKeyMaterial-${KEO_DOCKER_IMAGE_NAME}
    DEPENDS ${SSL_OUTPUT}
    )

  set(DOCKERFILE "${CMAKE_CURRENT_LIST_DIR}/Dockerfile-${KEO_DOCKER_IMAGE_NAME}")

  if(EXISTS ${DOCKERFILE})

    file(READ ${DOCKERFILE} FILE_CONTENT)

  else()

    set(FILE_CONTENT
      "FROM ${KEO_DOCKER_FROM}\n"
      "\n"
      "RUN apt-get update -y\n"
      "\n"
      "RUN apt-get install -y libavahi-client3 avahi-utils avahi-daemon ${KEO_DOCKER_ADDITIONAL_PACKAGES}\n"
      "\n"
      "COPY secp256r1KeyDER.bin /tmp/\n"
      "COPY secp256r1CertDER.bin /tmp/\n"
      "\n"
      "COPY *-bin.tar.gz /tmp/package_bin.tgz\n"
      "COPY *-dev.tar.gz /tmp/package_dev.tgz\n"
      "RUN tar xzf /tmp/package_bin.tgz -C /usr\n"
      "RUN tar xzf /tmp/package_dev.tgz -C /usr\n"
      ${KEO_DOCKER_ADDITIONAL_PROVISIONING_STEPS}
      "# workaround for broken systemv init scripts of Ubuntu 14.04\n"
      "# RUN ln -sf /bin/dbus-daemon /usr/bin/dbus-daemon\n"
      "RUN mkdir /var/run/dbus\n"
      "\n"
      "EXPOSE 16368\n"
      "\n"
      "CMD chmod +x /tmp/keorunscript.sh\n"
      "CMD /tmp/keorunscript.sh\n"
      )

  endif()

  file(WRITE "${${KEO_DOCKER_IMAGE_NAME}_workdir}/Dockerfile" ${FILE_CONTENT})

  set(DOCKER_CMD_LINE  build -t ${KEO_DOCKER_IMAGE_NAME} .)

  set_source_files_properties(
    docker_output-${KEO_DOCKER_IMAGE_NAME}
    PROPERTIES SYMBOLIC(True)
    )

  # generate docker image
  add_custom_command(
    OUTPUT ${${KEO_DOCKER_IMAGE_NAME}_workdir}/docker_output-${KEO_DOCKER_IMAGE_NAME}
    COMMAND cd ${PROJECT_BINARY_DIR} && rm -f *-bin.tar.gz *-dev.tar.gz
    COMMAND cd ${PROJECT_BINARY_DIR} && make package
    COMMAND mkdir -p ${${KEO_DOCKER_IMAGE_NAME}_workdir}/docker
    COMMAND rm -f ${${KEO_DOCKER_IMAGE_NAME}_workdir}/docker/*
    COMMAND cp -f ${PROJECT_BINARY_DIR}/*-dev.tar.gz ${${KEO_DOCKER_IMAGE_NAME}_workdir}
    COMMAND cp -f ${PROJECT_BINARY_DIR}/*-bin.tar.gz ${${KEO_DOCKER_IMAGE_NAME}_workdir}
    COMMAND cp -rfa ${CMAKE_CURRENT_LIST_DIR}/${KEO_DOCKER_FILES_DIRECTORY}/* ${${KEO_DOCKER_IMAGE_NAME}_workdir}/docker/
    COMMAND docker ${DOCKER_CMD_LINE}
    DEPENDS GenerateKeyMaterial-${KEO_DOCKER_IMAGE_NAME}
    WORKING_DIRECTORY ${${KEO_DOCKER_IMAGE_NAME}_workdir}
    COMMENT "Generate Docker Image ${KEO_DOCKER_IMAGE_NAME}"
    )

  add_custom_target(
    DockerImage-${KEO_DOCKER_IMAGE_NAME}
    DEPENDS ${${KEO_DOCKER_IMAGE_NAME}_workdir}/docker_output-${KEO_DOCKER_IMAGE_NAME}
    )

endmacro(keo_docker)

macro(keo_convertUmlet)

  set(options "")

  set(oneValueArgs
    INPUT_FILES
    OUT_DIR
    FORMAT
    )

  set(multiValueArgs
    )

  CMAKE_PARSE_ARGUMENTS(
    KEO_UMLET
    "${options}"
    "${oneValueArgs}"
    "${multiValueArgs}"
    ${ARGN}
    )

  message(DEBUG " oneValueArgs          ${oneValueArgs}")
  message(DEBUG " KEO_UMLET_INPUT_FILES ${KEO_UMLET_INPUT_FILES}")
  message(DEBUG " KEO_UMLET_OUT_DIR     ${KEO_UMLET_OUT_DIR}")
  message(DEBUG " KEO_UMLET_FORMAT      ${KEO_UMLET_FORMAT}")

  set(FILE_CONTENT
    "#! /usr/bin/env python2\n"
    "\n"
    "import os\n"
    "import sys\n"
    "import subprocess\n"
    "import multiprocessing\n"
    "\n"
    "# globals!\n"
    "uxf = ''\n"
    "outdir = ''\n"
    "umlet = ''\n"
    "\n"
    "def do_calculation(fname):\n"
    "\n"
    "     outname = os.path.basename(fname).rstrip('.uxf')\n"
    "     cmd = 'java -jar ' + umlet + ' -action=convert -format=${KEO_UMLET_FORMAT} -filename=' + fname + ' -output=' + os.path.join(outdir,outname) + '.${KEO_UMLET_FORMAT}'\n"
    "     print cmd\n"
    "     process = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)\n"
    "     o = process.communicate()[0]\n"
    "     output = str(o)\n"
    "     return output\n"
    "\n"
    "\n"
    "\n"
    "def start_process():\n"
    "     #print 'Starting', multiprocessing.current_process().name\n"
    "    pass\n"
    "\n"
    "if __name__ == '__main__':\n"
    "     uxf      = sys.argv[1]\n"
    "     outdir= sys.argv[2]\n"
    "     umlet = sys.argv[3]\n"
    "\n"
    "     inputs = []\n"
    "     with open(uxf) as f:\n"
    "         for line in f:\n"
    "             inputs.append(line.strip())\n"
    "\n"
    "     print 'Input   :', inputs\n"
    "\n"
    "     pool_size = multiprocessing.cpu_count() * 16\n"
    "     pool = multiprocessing.Pool(processes=pool_size,\n"
    "                                 initializer=start_process,\n"
    "                                 )\n"
    "     pool_outputs = pool.map(do_calculation, inputs)\n"
    "     pool.close() # no more tasks\n"
    "     pool.join()     # wrap up current tasks\n"
    "\n"
    "     print 'Pool       :', pool_outputs\n"
    )
  set(CONVERT_SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/convert.py")
  file(WRITE ${CONVERT_SCRIPT}  ${FILE_CONTENT})
  file(COPY  ${CONVERT_SCRIPT}
    DESTINATION ${KEO_UMLET_OUT_DIR}
    FILE_PERMISSIONS OWNER_WRITE OWNER_READ OWNER_EXECUTE GROUP_WRITE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
    )
  file(REMOVE ${CONVERT_SCRIPT})

  set (UXFFILE "${KEO_UMLET_OUT_DIR}/uxf.txt")
  set(GENERATED_LIST_FILES )

  file(WRITE ${UXFFILE} " ")
  foreach(infileName ${KEO_UMLET_INPUT_FILES})
    file(APPEND ${UXFFILE} ${infileName} "\n")

    # get_filename_component(<VAR> <FileName> <COMP> [CACHE])
    # DIRECTORY = Directory without file name
    # NAME      = File name without directory
    # EXT       = File name longest extension (.b.c from d/a.b.c)
    # NAME_WE   = File name without directory or longest extension
    # ABSOLUTE  = Full path to file
    # REALPATH  = Full path to existing file with symlinks resolved
    # PATH      = Legacy alias for DIRECTORY (use for CMake <= 2.8.11)

    get_filename_component(pdfFile ${infileName} NAME_WE)
    list( APPEND GENERATED_LIST_FILES "${KEO_UMLET_OUT_DIR}/${pdfFile}.svg")
  endforeach()

  SET_SOURCE_FILES_PROPERTIES(
    ${GENERATED_LIST_FILES}
    PROPERTIES GENERATED TRUE
    )

  add_custom_command(
    OUTPUT ${GENERATED_LIST_FILES}
    COMMAND "${KEO_UMLET_OUT_DIR}/convert.py" "${UXFFILE}" "${KEO_UMLET_OUT_DIR}" "${UMLET_EXECUTABLE}"
    WORKING_DIRECTORY "${KEO_UMLET_OUT_DIR}"
    COMMENT "************************************** Converting uxf to ${KEO_UMLET_FORMAT} in ${KEO_UMLET_OUT_DIR} ************************************"
    DEPENDS ${KEO_UMLET_INPUT_FILES}
    )

  message(STATUS " GENERATED_LIST_FILES= ${GENERATED_LIST_FILES}")

  add_custom_target(
    ConvertUmlet
    DEPENDS ${GENERATED_LIST_FILES}
    )

endmacro(keo_convertUmlet)
