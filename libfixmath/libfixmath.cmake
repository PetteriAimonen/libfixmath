file(GLOB libfixmath-srcs libfixmath/*.c)

add_library(fixmath SHARED ${libfixmath-srcs})

target_include_directories(fixmath INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR})