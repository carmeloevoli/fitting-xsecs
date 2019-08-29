project(ffxsecs CXX)

cmake_minimum_required(VERSION 2.6)

set(CMAKE_VERBOSE_MAKEFILE off)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-std=c++11 -O3 -DROOT_Math_VecTypes")
set(FFXSECS_INCLUDES)
set(FFXSECS_LIBRARIES)

include_directories("${CMAKE_SOURCE_DIR}")

set(FFXSECS_SRCS 
	src/channel.cpp
	src/data.cpp
	src/minimizer.cpp
	src/model.cpp
    )

# Minuit2 (external)
find_package(Minuit2 REQUIRED)

# MAKE EXECUTABLE
include_directories(include ${FFXSECS_INCLUDES})

add_executable(ffxsecs ${FFXSECS_SRCS} src/main.cpp)
target_link_libraries (ffxsecs PUBLIC Minuit2::Minuit2)

# Show summary.
message (STATUS "CMAKE_SYSTEM .......... = ${CMAKE_SYSTEM}")
message (STATUS "BUILD_SHARED_LIBS ..... = ${BUILD_SHARED_LIBS}")
message (STATUS "CMAKE_CXX_COMPILER .... = ${CMAKE_CXX_COMPILER}")
message (STATUS "CMAKE_CXX_FLAGS ....... = ${CMAKE_CXX_FLAGS}")
message (STATUS "CMAKE_SOURCE_DIR ...... = ${CMAKE_SOURCE_DIR}")
