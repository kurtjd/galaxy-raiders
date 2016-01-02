cmake_minimum_required(VERSION 3.2)

# Use custom Find* modules
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR} "${CMAKE_SOURCE_DIR}/modules")

# Current version
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION_RELEASE "alpha")
set(PROJECT_VERSION_METADATA "")

# Use a common include and source directory for projects. Each project creates their own
# subdirectory in ../include and ../source as needed.
set(PROJECT_INCLUDES ${CMAKE_SOURCE_DIR}/../inc)
set(PROJECT_SOURCES ${CMAKE_SOURCE_DIR}/../src)

# Global variable for warning flags
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
  set(WARNING_FLAGS "-Wall -Wextra -pedantic")
endif()

# Include cmake files that create targets
include(projects/space-invaders)
