cmake_minimum_required (VERSION 2.8.12)
project (techtest)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

set (SOURCE_FILES
   main.cpp
)

add_executable(techtest ${SOURCE_FILES})

target_link_libraries(
   techtest
   # pthread
)
