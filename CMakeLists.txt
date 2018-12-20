cmake_minimum_required (VERSION 2.8.12)
project (techtest)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_BUILD_TYPE Debug)

set (SOURCE_FILES
   main.cpp
   Distinct.cpp
   Top.cpp
)

set (HEADER_FILES
   ISubcommand.h
   Distinct.h
   Top.h
)

add_executable(techtest ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(
   techtest
   # pthread
)
