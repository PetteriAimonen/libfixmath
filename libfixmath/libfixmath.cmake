file(GLOB libfixmath-srcs libfixmath/*.c)

add_library(libfixmath STATIC ${libfixmath-srcs})

target_include_directories(libfixmath INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR})