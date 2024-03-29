cmake_minimum_required(VERSION 3.13)

project(libfixmath LANGUAGES CXX C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -Wextra -Werror=return-type")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra -Werror=return-type")

include(libfixmath/libfixmath.cmake)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    # We're in the root, define additional targets for developers.
    include(tests/tests.cmake)

    file(GLOB fixsingen-srcs fixsingen/*.c)
    file(GLOB fixtest-srcs fixtest/*.c fixtest/*.h)

    add_executable(fixtest ${fixtest-srcs})
    target_link_libraries(fixtest PRIVATE libfixmath m)
    target_include_directories(fixtest PRIVATE ${CMAKE_SOURCE_DIR})

    add_executable(fixsingen ${fixsingen-srcs})
    target_link_libraries(fixsingen PRIVATE libfixmath m)
    target_include_directories(fixsingen PRIVATE ${CMAKE_SOURCE_DIR})
endif()
