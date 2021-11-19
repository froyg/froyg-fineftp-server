cmake_minimum_required(VERSION 3.5.1)

# Normalize backslashes from Windows paths
file(TO_CMAKE_PATH "${CMAKE_MODULE_PATH}" CMAKE_MODULE_PATH)
file(TO_CMAKE_PATH "${CMAKE_PREFIX_PATH}" CMAKE_PREFIX_PATH)
message(STATUS "Module Path: ${CMAKE_MODULE_PATH}")
message(STATUS "Prefix Path: ${CMAKE_PREFIX_PATH}")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

project(fineftp)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(as_subproject fineftp)
include(msvc_sourcetree.cmake)

string(COMPARE EQUAL "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_SOURCE_DIR}" _cmp)
set(_cmp True)
if (_cmp)
  macro(find_package)
    if(NOT "${ARGV0}" IN_LIST as_subproject)
      _find_package(${ARGV})
    endif()
  endmacro()
endif()

set(Asio_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/thirdparty/asio/asio/include")
add_library(asio::asio INTERFACE IMPORTED)
    set_target_properties(asio::asio PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES ${Asio_INCLUDE_DIR}
      INTERFACE_COMPILE_DEFINITIONS ASIO_STANDALONE)
    mark_as_advanced(Asio_INCLUDE_DIR)

add_subdirectory(fineftp-server)
add_subdirectory(example)
