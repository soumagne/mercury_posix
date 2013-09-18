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
target_link_libraries(client_posix)
