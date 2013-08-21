#------------------------------------------------------------------------------
# External dependencies
#------------------------------------------------------------------------------
# Mercury
find_package(mercury REQUIRED)
if(mercury_FOUND)
  include_directories(${MERCURY_INCLUDE_DIR})
  if(NOT ${MERCURY_USE_BOOST_PP})
    message(FATAL_ERROR "Mercury POSIX requires Mercury to be built with USE_BOOST_PP option ON.")
  endif()
else()
  message(FATAL_ERROR "Could not find Boost, please check Boost_INCLUDE_DIR.")
endif()

#------------------------------------------------------------------------------
# Configure module header files
#------------------------------------------------------------------------------
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/mercury_posix_config.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/mercury_posix_config.h
)

# Used by config.cmake.build.in and Testing
set(MERCURY_POSIX_INCLUDES_BUILD_TIME
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${MERCURY_INCLUDE_DIR}
  PARENT_SCOPE
)

# Used by config.cmake.install.in
set(MERCURY_POSIX_INCLUDES_INSTALL_TIME
  ${MERCURY_POSIX_INSTALL_INCLUDE_DIR}
  ${MERCURY_INCLUDE_DIR}
  PARENT_SCOPE
)

#------------------------------------------------------------------------------
# Set sources
#------------------------------------------------------------------------------
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${MERCURY_POSIX_INCLUDES_BUILD_TIME}
  )

set(MERCURY_POSIX_SRCS
  ${CMAKE_CURRENT_SOURCE_DIR}/mercury_posix.c
)

#----------------------------------------------------------------------------
# Libraries
#----------------------------------------------------------------------------
# POSIX
add_library(mercury_posix ${MERCURY_POSIX_SRCS})
target_link_libraries(mercury_posix mercury)
set_lib_options(mercury_posix "mercury_posix" ${MERCURY_POSIX_LIBTYPE})
#if(MERCURY_ENABLE_COVERAGE)
#  set_coverage_flags(mercury_posix)
#endif()

add_executable(server_posix server_posix.c)
target_link_libraries(server_posix mercury)


set(MERCURY_EXPORTED_LIBS mercury_posix ${MERCURY_EXPORTED_LIBS})

#-----------------------------------------------------------------------------
# Specify project header files to be installed
#-----------------------------------------------------------------------------
set(MERCURY_POSIX_HEADERS
  ${CMAKE_CURRENT_SOURCE_DIR}/mercury_posix.h
)

#-----------------------------------------------------------------------------
# Add file(s) to CMake Install
#-----------------------------------------------------------------------------
install(
  FILES
    ${MERCURY_HEADERS}
  DESTINATION
    ${MERCURY_INSTALL_INCLUDE_DIR}
  COMPONENT
    headers
)

#---------------------------------------------------------------------------
# Add Target(s) to CMake Install
#---------------------------------------------------------------------------
install(
  TARGETS
    mercury_posix
  EXPORT
    ${MERCURY_POSIX_EXPORTED_TARGETS}
  LIBRARY DESTINATION ${MERCURY_POSIX_INSTALL_LIB_DIR}
  ARCHIVE DESTINATION ${MERCURY_POSIX_INSTALL_LIB_DIR}
  RUNTIME DESTINATION ${MERCURY_POSIX_INSTALL_BIN_DIR}
)

#-----------------------------------------------------------------------------
# Add Target(s) to CMake Install for import into other projects
#-----------------------------------------------------------------------------
install(
  EXPORT
    ${MERCURY_POSIX_EXPORTED_TARGETS}
  DESTINATION
    ${MERCURY_POSIX_INSTALL_DATA_DIR}/cmake/mercury_posix
  FILE
    ${MERCURY_POSIX_EXPORTED_TARGETS}.cmake
)

#-----------------------------------------------------------------------------
# Export all exported targets to the build tree for use by parent project
#-----------------------------------------------------------------------------
EXPORT (
  TARGETS
    ${MERCURY_POSIX_EXPORTED_LIBS}
  FILE
    ${MERCURY_POSIX_EXPORTED_TARGETS}.cmake
)
