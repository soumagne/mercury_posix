cmake_minimum_required(VERSION 2.8.5 FATAL_ERROR)
project(MERCURY_POSIX C)

#------------------------------------------------------------------------------
# Version information 
#------------------------------------------------------------------------------
set(MERCURY_POSIX_VERSION_MAJOR "0")
set(MERCURY_POSIX_VERSION_MINOR "8")
set(MERCURY_POSIX_VERSION_PATCH "1")
set(MERCURY_POSIX_PACKAGE "mercury_posix")
set(MERCURY_POSIX_PACKAGE_NAME "MERCURY_POSIX")
set(MERCURY_POSIX_PACKAGE_VERSION "${MERCURY_POSIX_VERSION_MAJOR}.${MERCURY_POSIX_VERSION_MINOR}.${MERCURY_POSIX_VERSION_PATCH}")
set(MERCURY_POSIX_PACKAGE_VERSION_MAJOR "${MERCURY_POSIX_VERSION_MAJOR}.${MERCURY_POSIX_VERSION_MINOR}")
set(MERCURY_POSIX_PACKAGE_VERSION_MINOR "${MERCURY_POSIX_VERSION_PATCH}")
set(MERCURY_POSIX_PACKAGE_STRING "${MERCURY_POSIX_PACKAGE_NAME} ${MERCURY_POSIX_PACKAGE_VERSION}")
set(MERCURY_POSIX_PACKAGE_TARNAME "${MERCURY_POSIX_PACKAGE}")

#------------------------------------------------------------------------------
# Setup install and output Directories
#------------------------------------------------------------------------------
if(NOT MERCURY_POSIX_INSTALL_BIN_DIR)
  set(MERCURY_POSIX_INSTALL_BIN_DIR ${CMAKE_INSTALL_PREFIX}/bin)
endif()
if(NOT MERCURY_POSIX_INSTALL_LIB_DIR)
  set(MERCURY_POSIX_INSTALL_LIB_DIR ${CMAKE_INSTALL_PREFIX}/lib)
endif()
if(NOT MERCURY_POSIX_INSTALL_INCLUDE_DIR)
  set(MERCURY_POSIX_INSTALL_INCLUDE_DIR ${CMAKE_INSTALL_PREFIX}/include)
endif()
if(NOT MERCURY_POSIX_INSTALL_DATA_DIR)
  set(MERCURY_POSIX_INSTALL_DATA_DIR ${CMAKE_INSTALL_PREFIX}/share)
endif()

#------------------------------------------------------------------------------
# Setup CMake Environment
#------------------------------------------------------------------------------
# Setup cmake policies.
foreach(policy CMP0012 CMP0013 CMP0014)
  if(POLICY ${policy})
    cmake_policy(SET ${policy} NEW)
  endif()
endforeach()

foreach(policy CMP0017)
  if(POLICY ${policy})
    cmake_policy(SET ${policy} OLD)
  endif()
endforeach()

#------------------------------------------------------------------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${PROJECT_BINARY_DIR}/bin CACHE PATH "Single Directory for all Executables."
)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
    ${PROJECT_BINARY_DIR}/bin CACHE PATH "Single Directory for all Libraries"
)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
    ${PROJECT_BINARY_DIR}/bin CACHE PATH "Single Directory for all static libraries."
)
set(MERCURY_POSIX_CMAKE_DIR "${MERCURY_SOURCE_DIR}/CMake")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${MERCURY_POSIX_CMAKE_DIR})

#------------------------------------------------------------------------------
# Disallow in-source build
#------------------------------------------------------------------------------
if("${MERCURY_POSIX_SOURCE_DIR}" STREQUAL "${MERCURY_POSIX_BINARY_DIR}")
  message(FATAL_ERROR
    "Mercury POSIX requires an out of source Build. "
    "Please create a separate binary directory and run CMake there.")
endif()

#------------------------------------------------------------------------------
# Set a default build type if none was specified
#------------------------------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'Release' as none was specified.")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
    "MinSizeRel" "RelWithDebInfo")
endif()

#-----------------------------------------------------------------------------
# Targets built within this project are exported at Install time for use
# by other projects.
#-----------------------------------------------------------------------------
if(NOT MERCURY_POSIX_EXPORTED_TARGETS)
  set(MERCURY_POSIX_EXPORTED_TARGETS "mercury_posix-targets")
endif()

#------------------------------------------------------------------------------
# Choose static or shared libraries.
#------------------------------------------------------------------------------
option(BUILD_SHARED_LIBS "Build with shared libraries." OFF)

#-------------------------------------------------------------------------------
function(set_lib_options libtarget libname libtype)
  if(${libtype} MATCHES "SHARED")
    if(WIN32 AND NOT MINGW)
      set(LIB_RELEASE_NAME "${libname}")
      set(LIB_DEBUG_NAME "${libname}_D")
      set(LIB_VERSION ${MERCURY_POSIX_PACKAGE_VERSION_MAJOR})
    else()
      set(LIB_RELEASE_NAME "${libname}")
      set(LIB_DEBUG_NAME "${libname}_debug")
      set(LIB_VERSION ${MERCURY_POSIX_PACKAGE_VERSION})
    endif()
  else()
    if(WIN32 AND NOT MINGW)
      set(LIB_RELEASE_NAME "lib${libname}")
      set(LIB_DEBUG_NAME "lib${libname}_D")
    else()
      # if the generator supports configuration types or if the CMAKE_BUILD_TYPE has a value
      if(CMAKE_CONFIGURATION_TYPES OR CMAKE_BUILD_TYPE)
        set(LIB_RELEASE_NAME "${libname}")
        set(LIB_DEBUG_NAME "${libname}_debug")
      else()
        set(LIB_RELEASE_NAME "lib${libname}")
        set(LIB_DEBUG_NAME "lib${libname}_debug")
      endif()
    endif()
  endif()

  set_target_properties(${libtarget}
      PROPERTIES
      DEBUG_OUTPUT_NAME          ${LIB_DEBUG_NAME}
      RELEASE_OUTPUT_NAME        ${LIB_RELEASE_NAME}
      MINSIZEREL_OUTPUT_NAME     ${LIB_RELEASE_NAME}
      RELWITHDEBINFO_OUTPUT_NAME ${LIB_RELEASE_NAME}
      VERSION                    ${LIB_VERSION}
      SOVERSION                  ${LIB_VERSION}
  )

  #----- Use MSVC Naming conventions for Shared Libraries
  if(MINGW AND ${libtype} MATCHES "SHARED")
    set_target_properties(${libtarget}
        PROPERTIES
        IMPORT_SUFFIX ".lib"
        IMPORT_PREFIX ""
        PREFIX ""
    )
  endif()
endfunction()

#-----------------------------------------------------------------------------
# Source
#-----------------------------------------------------------------------------
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

#-----------------------------------------------------------------------------
# Testing
#-----------------------------------------------------------------------------
option(BUILD_TESTING "Build testing." OFF)
if(BUILD_TESTING)
  add_subdirectory(Testing)
endif()

#-----------------------------------------------------------------------------
# Configure the config.cmake file for the build directory
#-----------------------------------------------------------------------------
configure_file(
  ${MERCURY_POSIX_SOURCE_DIR}/CMake/mercury_posix-config.cmake.build.in
  ${MERCURY_POSIX_BINARY_DIR}/mercury_posix-config.cmake @ONLY
)

#-----------------------------------------------------------------------------
# Configure the config.cmake file for the install directory
#-----------------------------------------------------------------------------
configure_file(
  ${MERCURY_POSIX_SOURCE_DIR}/CMake/mercury_posix-config.cmake.install.in
  ${MERCURY_POSIX_BINARY_DIR}/CMakeFiles/mercury_posix-config.cmake @ONLY
)

install(
  FILES
    ${MERCURY_POSIX_BINARY_DIR}/CMakeFiles/mercury_posix-config.cmake
  DESTINATION
    ${MERCURY_POSIX_INSTALL_DATA_DIR}/cmake/mercury_posix
)

#-----------------------------------------------------------------------------
# Configure the hdf5-config-version .cmake file for the install directory
#-----------------------------------------------------------------------------
configure_file(
  ${MERCURY_POSIX_SOURCE_DIR}/CMake/mercury_posix-config-version.cmake.in
  ${MERCURY_POSIX_BINARY_DIR}/CMakeFiles/mercury_posix-config-version.cmake @ONLY
)

install(
  FILES
    ${MERCURY_POSIX_BINARY_DIR}/CMakeFiles/mercury_posix-config-version.cmake
  DESTINATION
    ${MERCURY_POSIX_INSTALL_DATA_DIR}/cmake/mercury_posix
)

#-----------------------------------------------------------------------------
# CPack
#-----------------------------------------------------------------------------
set(CPACK_PACKAGE_DESCRIPTION_FILE ${MERCURY_POSIX_SOURCE_DIR}/README)
set(CPACK_RESOURCE_FILE_LICENSE ${MERCURY_POSIX_SOURCE_DIR}/COPYING)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "POSIX I/O Forwarder")
set(CPACK_PACKAGE_NAME "Mercury POSIX")
set(CPACK_PACKAGE_VENDOR "Argonne National Laboratories / The HDF Group")
set(CPACK_PACKAGE_VERSION_MAJOR ${MERCURY_POSIX_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${MERCURY_POSIX_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${MERCURY_POSIX_VERSION_PATCH})
set(CPACK_GENERATOR "TBZ2")
set(CPACK_SOURCE_PACKAGE_FILE_NAME ${MERCURY_POSIX_PACKAGE_TARNAME}-${MERCURY_POSIX_PACKAGE_VERSION})
set(CPACK_SOURCE_IGNORE_FILES ".git*;/GitSetup/;/.git/;.swp$;.#;/#;.*~")
set(CPACK_SOURCE_STRIP_FILES "")
include(CPack)
