set(TEST_TARGET_NAME websockets)
message(STATUS "Configuring tests for: ${TEST_TARGET_NAME}")

include_directories(
  ${PROJECT_SOURCE_DIR}/include
  )

set(LIST_TEST_SRCS
  gtestmain.cpp
  tests.cpp
  )

set(LIST_TEST_HDRS
  )

set(THREAD_LIB pthread)

set(SOCKET_LIB dl)

if(USE_SSL)
  set(SECURITY_LIB ${OPENSSL_LIBRARIES})
  set(SECURITY_OBJECT_LIB shipsecurity)
endif()

set (TEST_ADDITIONAL_LIBS   
        ${SECURITY_LIB}
        ${SOCKET_LIB}
        ${THREAD_LIB}
)
set (TEST_ADDITIONAL_OBJECT_LIBS 
    websockets
    ${SECURITY_OBJECT_LIB}
)

message (STATUS "TEST_ADDITIONAL_LIBS: ${TEST_ADDITIONAL_LIBS}")
message (STATUS "TEST_TARGET_NAME: ${TEST_TARGET_NAME}")
googletest(${TEST_TARGET_NAME})
