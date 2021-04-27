cmake_minimum_required(VERSION 3.5)

project(libfixmath LANGUAGES CXX C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "-Wall -pedantic -Wextra -Werror=return-type")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -pedantic -Wextra -Werror=return-type")

include(libfixmath/libfixmath.cmake)

file(GLOB fixsingen-srcs fixsingen/*.c)
file(GLOB fixtest-srcs fixtest/*.c fixtest/*.h)
file(GLOB unittests-srcs unittests/*.c unittests/*.h)
file(GLOB tests-srcs tests/*.c tests/*.h)

add_executable(fixtest ${fixtest-srcs})
target_link_libraries(fixtest PRIVATE libfixmath m)
target_include_directories(fixtest PRIVATE ${CMAKE_SOURCE_DIR})

add_executable(fixsingen ${fixsingen-srcs})
target_link_libraries(fixsingen PRIVATE libfixmath m)
target_include_directories(fixsingen PRIVATE ${CMAKE_SOURCE_DIR})

add_executable(unittests ${unittests-srcs})
target_link_libraries(unittests PRIVATE libfixmath m)
target_include_directories(unittests PRIVATE ${CMAKE_SOURCE_DIR})

add_executable(tests ${tests-srcs})
target_link_libraries(tests PRIVATE libfixmath m)
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR})
