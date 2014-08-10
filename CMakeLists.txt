cmake_minimum_required (VERSION 2.6)
project (fpdelta)

# Enable c++11 and pedantic warning
if (UNIX)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else ()
  message(FATAL_ERROR "Unsupported platform")
endif ()

# Using BOOST
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

set (LIB ${LIB} ${Boost_LIBRARIES})

# Main fpdelta library
include ("${PROJECT_SOURCE_DIR}/src/fpdelta/CMakeLists.txt")

# Sample test
include ("${PROJECT_SOURCE_DIR}/tests/test_1/CMakeLists.txt")

