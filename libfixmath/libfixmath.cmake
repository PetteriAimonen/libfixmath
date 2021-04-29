file(GLOB libfixmath-srcs libfixmath/*.h libfixmath/*.hpp libfixmath/*.c)

add_library(libfixmath STATIC ${libfixmath-srcs})
