cmake_minimum_required (VERSION 3.1)
project (Task1.1)
set (CMAKE_CXX_STANDARD 14)

# compile & link
add_library (table sources/table.cpp sources/rowStoreTable.cpp sources/columnStoreTable.cpp)
add_executable (run tests/tests.cpp)
target_link_libraries (run table)

# test
#include(CTest)
#add_test (run-runs run)

SET(OPT0 OFF CACHE BOOL "Some user-specified option")
SET(OPT1 OFF CACHE BOOL "Some user-specified option")
SET(OPT2 OFF CACHE BOOL "Some user-specified option")
SET(OPT3 OFF CACHE BOOL "Some user-specified option")

if(OPT0)
    set(CMAKE_CXX_FLAGS "-O0")        ## Optimize
endif()
if(OPT1)
    set(CMAKE_CXX_FLAGS "-O1")        ## Optimize
endif()
if(OPT2)
    set(CMAKE_CXX_FLAGS "-O2")        ## Optimize
endif()
if(OPT3)
    set(CMAKE_CXX_FLAGS "-O3")        ## Optimize
endif()

#set(CMAKE_CXX_FLAGS "-O1")

#message("CMAKE_CXX_FLAGS_DEBUG is ${CMAKE_CXX_FLAGS_DEBUG}")
#message("CMAKE_CXX_FLAGS_RELEASE is ${CMAKE_CXX_FLAGS_RELEASE}")