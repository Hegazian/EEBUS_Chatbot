
add_custom_command(TARGET ${keo_target_spine_datagram_deserializer}
                   POST_BUILD
                   COMMAND mkdir -p ${CMAKE_BINARY_DIR}/xsd_test
                   COMMAND chmod +x ${DATABINDER_ROOT}/test/runTestDatagramLibrary.sh
                   COMMAND chmod +x ${DATABINDER_ROOT}/test/generateXml.py
                   COMMAND chmod +x ${DATABINDER_ROOT}/test/xml2json.py
                   COMMAND ${DATABINDER_ROOT}/test/runTestDatagramLibrary.sh
                               -s ${CMAKE_BINARY_DIR}/GeneratedSpine/SpineXsd.json
                               -x ${CMAKE_CURRENT_LIST_DIR}/../xsd
                               -b ${CMAKE_BINARY_DIR}/xsd_test
                               -t ${CMAKE_BINARY_DIR}/bin/spine_datagram_deserializer
                   ${CMAKE_CURRENT_LIST_DIR})
