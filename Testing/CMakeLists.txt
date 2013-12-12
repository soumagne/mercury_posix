#------------------------------------------------------------------------------
# Set up test options
#------------------------------------------------------------------------------
add_definitions(${MERCURY_POSIX_DEF})

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${MERCURY_POSIX_INCLUDES_BUILD_TIME}
)

#------------------------------------------------------------------------------
# POSIX test
add_executable(client_posix client_posix.c)
target_link_libraries(client_posix mercury_posix)

# MPI I/O test
option(MERCURY_POSIX_TEST_MPIIO "Build MPI I/O test." OFF)
if(MERCURY_POSIX_TEST_MPIIO)
  find_package(MPI REQUIRED)
  if(MPI_FOUND)
    include_directories(${MPI_INCLUDE_PATH})
    add_executable(client_mpiio client_mpiio.c)
    target_link_libraries(client_mpiio mercury_posix ${MPI_LIBRARIES})
  else()
    message(FATAL_ERROR "Could not find MPI.")
  endif()
endif()
