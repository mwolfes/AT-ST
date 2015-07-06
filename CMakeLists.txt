cmake_minimum_required (VERSION 2.6)
project(ape)

if (CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR AND NOT MSVC_IDE )
	message( FATAL_ERROR "\nIn-source build attempt detected!\n")
endif()

include (cmake/settings.cmake)
include (cmake/FindROOT.cmake)
include (cmake/FindPluto.cmake)

message("\n==>  Build Type:       " ${CMAKE_BUILD_TYPE})
message("==>  Install libs to:  " ${LIBRARY_OUTPUT_PATH})
message("==>  Install bin to:   " ${EXECUTABLE_OUTPUT_PATH})
message("==>  Compiler flags:   " ${DEFAULT_COMPILE_FLAGS})


# Create output directories
INSTALL(CODE "FILE(MAKE_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})")
INSTALL(CODE "FILE(MAKE_DIRECTORY ${LIBRARY_OUTPUT_PATH})")

add_subdirectory (ape)
add_subdirectory (tools)
