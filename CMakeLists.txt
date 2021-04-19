cmake_minimum_required(VERSION 3.5)

project(libfixmath LANGUAGES CXX C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "-Wall -pedantic -Wextra")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -pedantic -Wextra")

file(GLOB libfixmath-srcs libfixmath/*.h libfixmath/*.hpp libfixmath/*.c)
file(GLOB contrib-srcs contrib/*.c)
file(GLOB fixsingen-srcs fixsingen/*.c)
file(GLOB fixtest-srcs fixtest/*.c fixtest/*.h)

add_library(libfixmath STATIC ${libfixmath-srcs} ${contrib-srcs})
target_include_directories(libfixmath PRIVATE ${CMAKE_SOURCE_DIR})

add_executable(fixtest ${fixtest-srcs})
target_link_libraries(fixtest PRIVATE libfixmath m)
target_include_directories(fixtest PRIVATE ${CMAKE_SOURCE_DIR})


add_executable(fixsingen ${fixsingen-srcs})
target_link_libraries(fixsingen PRIVATE libfixmath m)
target_include_directories(fixsingen PRIVATE ${CMAKE_SOURCE_DIR})
