# Compatibility

if (NOT SPINE_XSD_DIRECTORY)
  if (XSD_DIRECTORY)
    set(SPINE_XSD_DIRECTORY ${XSD_DIRECTORY})
  endif()
endif()

# ============================================================
#
# data binder
#
# ============================================================

set(SPINE_GENERATED_LIST_FILES ${GENERATED_DIR}/CMakeLists.txt)

# excecute python databinder
add_custom_command(
    OUTPUT ${SPINE_GENERATED_LIST_FILES}

    COMMAND ${DATABINDER_EXEC} --xsddir ${SPINE_XSD_DIRECTORY}
                               --destination ${GENERATED_DIR}
                               --binding cpp11
                               --format
                               --meta

    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    COMMENT "${DATABINDER_EXEC} ${DATABINDING_COMMAND_LINE}"
    )

add_custom_target(
  RunSpineDataBinder
  ALL #todo: remove this!!!
  DEPENDS ${SPINE_GENERATED_LIST_FILES}
  )
