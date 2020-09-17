project(UpsilonGC)

cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

include(FeatureSummary)

# Set version
set(UPSILONGC_VERSION_MAJOR 0)
set(UPSILONGC_VERSION_MINOR 1)
set(UPSILONGC_VERSION_PATCH 0)
set(UPSILONGC_VERSION_STRING "${UPSILONGC_VERSION_MAJOR}.${UPSILONGC_VERSION_MINOR}.${UPSILONGC_VERSION_PATCH}")
add_definitions("-DUPSILONGC_VERSION_STRING=\"${UPSILONGC_VERSION_STRING}\"")

# CoreCLR source path
if(NOT EXISTS "${CORECLR_FOR_CUSTOMGC}/CMakeLists.txt")
    message(FATAL_ERROR "CORECLR_FOR_CUSTOMGC ${CORECLR_FOR_CUSTOMGC} doesn't exist!")
endif()

add_definitions("-DCORECLR_FOR_CUSTOMGC=\"${CORECLR_FOR_CUSTOMGC}\"")

# Default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Handle build type
if(CMAKE_BUILD_TYPE MATCHES [Dd]ebug)
    message(STATUS "Debug build")
    add_definitions(-DUPSILONGC_DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
else()
    message(STATUS "Release build")
    add_definitions(-DNDEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
endif()

include("${CORECLR_FOR_CUSTOMGC}/configurecompiler.cmake")

# Add subdirectories
add_subdirectory(src)

# Display feature summary
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
