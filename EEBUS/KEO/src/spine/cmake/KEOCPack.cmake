# ============================================================
#
# cpack settings
#
# ============================================================

#
# @brief KEO CPack settings
#
# @param PROJECT_NAME
# @param DESCRIPTION_SUMMARY
# @param VERSION_MAJOR
# @param VERSION_MINOR
# @param VERSION_PATCH
# @param VERSION_STRING
# @param TARGETARCHITECTURE
# @param PACKAGE_FILE_NAME

# @NOTE Known issue:



macro(keo_cpack)
  message(DEBUG "---- processing keocpack")

  set(options RELEASE_PACKAGE)
  set(oneValueArgs
    PROJECT_NAME
    DESCRIPTION_SUMMARY
    VERSION_MAJOR
    VERSION_MINOR
    VERSION_PATCH
    VERSION_STRING
    TARGETARCHITECTURE
    PACKAGE_FILE_NAME)

  set(multiValueArgs "")

   CMAKE_PARSE_ARGUMENTS(
       KEO_CPACK
       "${options}"
       "${oneValueArgs}"
       "${multiValueArgs}"
       ${ARGN}
    )

    message(DEBUG " oneValueArgs                  ${oneValueArgs}")
    message(DEBUG " KEO_CPACK_PROJECT_NAME        ${KEO_CPACK_PROJECT_NAME}")
    message(DEBUG " KEO_CPACK_DESCRIPTION_SUMMARY ${KEO_CPACK_DESCRIPTION_SUMMARY}")
    message(DEBUG " KEO_CPACK_VERSION_MAJOR       ${KEO_CPACK_VERSION_MAJOR}")
    message(DEBUG " KEO_CPACK_VERSION_MINOR       ${KEO_CPACK_VERSION_MINOR}")
    message(DEBUG " KEO_CPACK_VERSION_PATCH       ${KEO_CPACK_VERSION_PATCH}")
    message(DEBUG " KEO_CPACK_VERSION_STRING      ${KEO_CPACK_VERSION_STRING}")
    message(DEBUG " KEO_CPACK_TARGETARCHITECTURE  ${KEO_CPACK_TARGETARCHITECTURE}")
    message(DEBUG " KEO_CPACK_PACKAGE_FILE_NAME   ${KEO_CPACK_PACKAGE_FILE_NAME}")

  # now we have:
  #
  # KEO_CPACK_PROJECT_NAME
  # KEO_CPACK_DESCRIPTION_SUMMARY
  # KEO_CPACK_VERSION_MAJOR
  # KEO_CPACK_VERSION_MINOR
  # KEO_CPACK_VERSION_PATCH
  # KEO_CPACK_VERSION_STRING
  # KEO_CPACK_TARGETARCHITECTURE
  # KEO_CPACK_PACKAGE_FILE_NAME


  # CPack boilerplate for this project
  set(CPACK_PACKAGE_CONTACT "www.keo-connectivity.de")
  set(CPACK_PACKAGE_NAME                ${KEO_CPACK_PROJECT_NAME})
  set(CPACK_PACKAGE_VENDOR "KEO GmbH")
  set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${KEO_CPACK_DESCRIPTION_SUMMARY})
  set(CPACK_PACKAGE_VERSION_MAJOR       ${KEO_CPACK_VERSION_MAJOR})
  set(CPACK_PACKAGE_VERSION_MINOR       ${KEO_CPACK_VERSION_MINOR})
  set(CPACK_PACKAGE_VERSION_PATCH       ${KEO_CPACK_VERSION_PATCH})
  set(CPACK_PACKAGE_VERSION             ${KEO_CPACK_VERSION_STRING})
  set(CPACK_PACKAGE_FILE_NAME           ${KEO_CPACK_PACKAGE_FILE_NAME})

  set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE ${KEO_CPACK_TARGETARCHITECTURE})
  set(CPACK_DEBIAN_PACKAGE_NAME         ${CPACK_PACKAGE_NAME})
  set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY 0)

  # Prefer markdown license file if present
  set(LIC_MD ${CMAKE_SOURCE_DIR}/License.md)
  if(EXISTS ${LIC_MD})
    set(CPACK_RESOURCE_FILE_LICENSE ${LIC_MD})
  else()
    set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_SOURCE_DIR}/License.txt)
  endif()
  message(INFO " Using CPack license file ${CPACK_RESOURCE_FILE_LICENSE}")


  if(UNIX)

    # Only for single-configuration-generators we can use ${CMAKE_BUILD_TYPE} to give the package a more specific name:
    set(CPACK_GENERATOR "TGZ")
    set(CPACK_DEB_COMPONENT_INSTALL ON)
    set(CPACK_TGZ_COMPONENT_INSTALL ON)

  else(UNIX)

    set(CPACK_GENERATOR "ZIP;NSIS")
    set(CPACK_ZIP_COMPONENT_INSTALL ON)
    set(CPACK_NSIS_COMPONENT_INSTALL ON)

  endif(UNIX)

  if (NOT KEO_CPACK_NO_DEFAULT_COMPONENTS)
    set(CPACK_COMPONENT_BIN_GROUP "bin")
    set(CPACK_COMPONENT_CFG_GROUP "cfg")
    set(CPACK_COMPONENT_DEV_GROUP "dev")
    set(CPACK_COMPONENT_DOC_GROUP "documentation")
    set(CPACK_COMPONENT_EXAMPLE_GROUP "example")
    set(CPACK_COMPONENT_SDK_GROUP "sdk")
    set(CPACK_COMPONENT_SRC_GROUP "src")
    set(CPACK_COMPONENT_TOOLS_GROUP "tools")
    set(CPACK_COMPONENT_TESTS "tests")
    set(CPACK_COMPONENTS_ALL "bin;cfg;dev;documentation;example;sdk;src;tools;tests")
  endif()

  if (KEO_CUSTOM_CPACK)
    include(${KEO_CUSTOM_CPACK})
  endif()

  set(CPACK_ARCHIVE_COMPONENT_INSTALL 1)
  set(CPACK_COMPONENTS_ALL_IN_ONE_PACKAGE OFF)
  set(CPACK_COMPONENTS_IGNORE_GROUPS 1)

  set(CPACK_STRIP_FILES ON)

  # Include CPack to introduce the appropriate targets
  include(CPack)

  # CPack end
endmacro(keo_cpack)
