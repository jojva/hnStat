cmake_minimum_required (VERSION 2.8.12)
project (hnStat)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O3")
set(CMAKE_BUILD_TYPE Release)

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

add_executable(hnStat ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(
   hnStat
)
