cmake_minimum_required(VERSION 3.5.1)

# Project call
include("${CMAKE_CURRENT_LIST_DIR}/fineftp-server/version.cmake")
project(fineftp VERSION ${FINEFTP_SERVER_VERSION_MAJOR}.${FINEFTP_SERVER_VERSION_MINOR}.${FINEFTP_SERVER_VERSION_PATCH})

# Normalize backslashes from Windows paths
file(TO_CMAKE_PATH "${CMAKE_MODULE_PATH}" CMAKE_MODULE_PATH)
file(TO_CMAKE_PATH "${CMAKE_PREFIX_PATH}" CMAKE_PREFIX_PATH)
message(STATUS "Module Path: ${CMAKE_MODULE_PATH}")
message(STATUS "Prefix Path: ${CMAKE_PREFIX_PATH}")

# CMake Options
option(FINEFTP_SERVER_BUILD_SAMPLES
       "Build project samples"
       ON)

# Module path for finding asio
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Set Debug postfix
set(CMAKE_DEBUG_POSTFIX            d)
set(CMAKE_MINSIZEREL_POSTFIX       minsize)
set(CMAKE_RELWITHDEBINFO_POSTFIX   reldbg)
set(CMAKE_EXPORT_COMPILE_COMMANDS  ON)

# Build as subproject
set(as_subproject fineftp)
set(_cmp True)
if (_cmp)
  macro(find_package)
    if(NOT "${ARGV0}" IN_LIST as_subproject)
      _find_package(${ARGV})
    endif()
  endmacro()
endif()

# Hardcode asio path
set(Asio_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/thirdparty/asio/asio/include")
add_library(asio::asio INTERFACE IMPORTED)
    set_target_properties(asio::asio PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES ${Asio_INCLUDE_DIR}
      INTERFACE_COMPILE_DEFINITIONS ASIO_STANDALONE)
    mark_as_advanced(Asio_INCLUDE_DIR)

# Add main fineftp::server library
add_subdirectory(fineftp-server)

if (FINEFTP_SERVER_BUILD_SAMPLES)
    add_subdirectory(samples/fineftp_example)
endif()

# Make this package available for packing with CPack
include("${CMAKE_CURRENT_LIST_DIR}/cpack_config.cmake")
