file(GLOB libfixmath-srcs libfixmath/*.h libfixmath/*.hpp libfixmath/*.c)

add_library(libfixmath STATIC ${libfixmath-srcs})
target_include_directories(libfixmath PRIVATE ${CMAKE_SOURCE_DIR})

