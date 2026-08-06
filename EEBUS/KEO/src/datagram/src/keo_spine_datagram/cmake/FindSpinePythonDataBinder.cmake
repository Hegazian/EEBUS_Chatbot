# - Try to find DataBinding binary
# Usage of this module as follows:
#
#  DATABINDER_FOUND        - True if DataBinding found.
#
# Variables used by this module which you may want to set.
#
#                                   The preferred installation prefix for searching for
#   DATABINDER_ROOT                     DataBinding.  Set this if the module has problems finding
#                                       the proper DataBinding installation.
#
#   DATABINDER_EXEC                 Set this to the Databinder program path, if the
#                                       module has problems finding the proper Databinder installation

#=============================================================================
# Copyright 2018 KEO GmbH

# Allow EEBUS_DATABINDER_ROOT as alias for DATABINDER_ROOT
if ((NOT DEFINED DATABINDER_ROOT) AND (DEFINED EEBUS_DATABINDER_ROOT))
  set(DATABINDER_ROOT ${EEBUS_DATABINDER_ROOT})
endif()

if (($ENV{DATABINDER_ROOT} STREQUAL "") AND (NOT $ENV{EEBUS_DATABINDER_ROOT} STREQUAL ""))
    set(ENV{DATABINDER_ROOT} $ENV{EEBUS_DATABINDER_ROOT})
endif()



# If DATABINDER_ROOT was defined in the environment, use it.
if (NOT DATABINDER_ROOT AND NOT $ENV{DATABINDER_ROOT} STREQUAL "")
    set(DATABINDER_ROOT $ENV{DATABINDER_ROOT})
endif()

# Look for the Databinder program.
find_program(databinder_EXEC
         NAMES python/databinder/codegenerator.py
         HINTS ${DATABINDER_ROOT}
         HINTS ${DATABINDER_ROOT}/bin
         )


# handle the QUIETLY and REQUIRED arguments and set DATABINDER_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(DATABINDER
                                  REQUIRED_VARS databinder_EXEC
                                  )
# Copy the results to the output variables.
if(DATABINDER_FOUND)
   set(DATABINDER_EXEC ${databinder_EXEC})
endif()
