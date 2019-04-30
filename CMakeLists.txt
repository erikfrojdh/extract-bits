cmake_minimum_required(VERSION 3.12)
project(utils VERSION 0.0.1 LANGUAGES CXX)


#Check if Link Time Optimization is supported
include(CheckIPOSupported)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "No build type selected, default to Release")
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type (default Release)" FORCE)
endif()

option (BUILD_TESTS "Build unit tests" ON)
option (BUILD_BENCHMARKS "Build benchmarks" ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG")
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address,undefined")
# set (CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address,undefined")

add_library(project_options INTERFACE)
add_library(project_warnings INTERFACE)



target_compile_features(project_options INTERFACE
  cxx_std_11
)

target_compile_options(project_options INTERFACE 
    -O3
    -mtune=native
    -march=native
)

target_compile_options(project_warnings
INTERFACE -Wall
          #-Werror # treat all warnings as errors
          -Wextra # reasonable and standard
          -Wshadow # warn the user if a variable declaration shadows one
                   # from a parent context
          -Wnon-virtual-dtor # warn the user if a class with virtual
                             # functions has a non-virtual destructor. This
                             # helps catch hard to track down memory errors
          -Wold-style-cast # warn for c-style casts
          -Wcast-align # warn for potential performance problem casts
          -Wunused # warn on anything being unused
          -Woverloaded-virtual # warn if you overload (not override) a
                               # virtual function
          -Wpedantic # warn if non-standard C++ is used
          -Wconversion # warn on type conversions that may lose data
          -Wsign-conversion # warn on sign conversions
          -Wnull-dereference # warn if a null dereference is detected
          -Wdouble-promotion # warn if float is implicit promoted to double
          -Wformat=2 # warn on security issues around functions that format
                     # output (ie printf)
)

add_library(utils STATIC 
  src/ReadData.cpp
  src/ExtractBits.cpp
)

target_include_directories(utils PUBLIC include)
target_link_libraries(utils PUBLIC 
  project_options
  project_warnings
)

check_ipo_supported(RESULT result)
if(result)
    set_property(TARGET utils PROPERTY INTERPROCEDURAL_OPTIMIZATION True)
endif()

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(benchmark)

if(BUILD_TESTS)
  add_subdirectory(lib/Catch2)
  add_subdirectory(test)
endif(BUILD_TESTS)

add_executable(a app/main.cpp)
target_link_libraries(a PRIVATE project_options project_warnings Threads::Threads utils benchmark)

if(BUILD_BENCHMARKS) 
  add_subdirectory(benchmarks)
endif(BUILD_BENCHMARKS)