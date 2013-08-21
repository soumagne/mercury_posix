#------------------------------------------------------------------------------
# Set up test options
#------------------------------------------------------------------------------
#set(MERCURY_TESTING_BUFFER_SIZE "16" CACHE STRING
#  "Total buffer size (in MB) used for testing.")

#set(MERCURY_TESTING_MAX_LOOP "1" CACHE STRING
#  "Loop n times for average bandwidth/time measures.")

#set(MERCURY_TESTING_NUM_THREADS "8" CACHE STRING
#  "Number of server threads used for testing.")

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${MERCURY_POSIX_INCLUDES_BUILD_TIME}
)

#------------------------------------------------------------------------------
# POSIX test
add_executable(client_posix client_posix.c)
target_link_libraries(client_posix)
#if(MERCURY_ENABLE_COVERAGE)
#  set_coverage_flags(client_posix)
#endif()

#add_executable(server_posix server_posix.c)
#target_link_libraries(server_posix )
#if(MERCURY_ENABLE_COVERAGE)
#  set_coverage_flags(server_posix)
#endif()
