file(GLOB tests-srcs tests/*.c tests/*.h)

enable_testing()

# -fno-sanitize-recover
if(APPLE AND CMAKE_OSX_ARCHITECTURES MATCHES "ppc|ppc64")
# Darwin PPC does not support ubsan presently.
    set(sanitizer_opts "")
else()
    set(sanitizer_opts -fsanitize=undefined)
endif()

add_custom_target(make_tests)

function(create_variant name)
    add_library(libfixmath_${name} STATIC ${libfixmath-srcs})
    target_include_directories(libfixmath_${name} INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR})
    target_compile_definitions(libfixmath_${name} PRIVATE PREFIX=${name} ${ARGN})
    target_compile_options(libfixmath_${name} PRIVATE ${sanitizer_opts})
    target_link_options(libfixmath_${name} PRIVATE ${sanitizer_opts})
    add_executable(tests_${name} ${tests-srcs})
    target_link_libraries(tests_${name} PRIVATE libfixmath_${name} m)
    target_include_directories(tests_${name} PRIVATE ${CMAKE_SOURCE_DIR})
    target_compile_definitions(tests_${name} PRIVATE PREFIX=${name} ${ARGN})
    target_compile_options(tests_${name} PRIVATE ${sanitizer_opts})
    target_link_options(tests_${name} PRIVATE ${sanitizer_opts})
    add_dependencies(make_tests tests_${name})
    add_test(NAME tests_${name} COMMAND tests_${name})
endfunction()

create_variant(ro64)
create_variant(no64 FIXMATH_NO_ROUNDING)
create_variant(rn64 FIXMATH_NO_OVERFLOW)
create_variant(nn64 FIXMATH_NO_ROUNDING FIXMATH_NO_OVERFLOW)
create_variant(ro32 FIXMATH_NO_64BIT)
create_variant(no32 FIXMATH_NO_ROUNDING FIXMATH_NO_64BIT)
create_variant(rn32 FIXMATH_NO_OVERFLOW FIXMATH_NO_64BIT)
create_variant(nn32 FIXMATH_NO_OVERFLOW FIXMATH_NO_ROUNDING FIXMATH_NO_64BIT)
create_variant(ro08 FIXMATH_OPTIMIZE_8BIT)
create_variant(no08 FIXMATH_NO_ROUNDING FIXMATH_OPTIMIZE_8BIT)
create_variant(rn08 FIXMATH_NO_OVERFLOW FIXMATH_OPTIMIZE_8BIT)
create_variant(nn08 FIXMATH_NO_OVERFLOW FIXMATH_NO_ROUNDING FIXMATH_OPTIMIZE_8BIT)

create_variant(ro64div FIXMATH_NO_HARD_DIV)
create_variant(no64div FIXMATH_NO_HARD_DIV FIXMATH_NO_ROUNDING)
create_variant(rn64div FIXMATH_NO_HARD_DIV FIXMATH_NO_OVERFLOW)
create_variant(nn64div FIXMATH_NO_HARD_DIV FIXMATH_NO_ROUNDING FIXMATH_NO_OVERFLOW)
create_variant(ro32div FIXMATH_NO_HARD_DIV FIXMATH_NO_64BIT)
create_variant(no32div FIXMATH_NO_HARD_DIV FIXMATH_NO_ROUNDING FIXMATH_NO_64BIT)
create_variant(rn32div FIXMATH_NO_HARD_DIV FIXMATH_NO_OVERFLOW FIXMATH_NO_64BIT)
create_variant(nn32div FIXMATH_NO_HARD_DIV FIXMATH_NO_OVERFLOW FIXMATH_NO_ROUNDING FIXMATH_NO_64BIT)
create_variant(ro08div FIXMATH_NO_HARD_DIV FIXMATH_OPTIMIZE_8BIT)
create_variant(no08div FIXMATH_NO_HARD_DIV FIXMATH_NO_ROUNDING FIXMATH_OPTIMIZE_8BIT)
create_variant(rn08div FIXMATH_NO_HARD_DIV FIXMATH_NO_OVERFLOW FIXMATH_OPTIMIZE_8BIT)
create_variant(nn08div FIXMATH_NO_HARD_DIV FIXMATH_NO_OVERFLOW FIXMATH_NO_ROUNDING FIXMATH_OPTIMIZE_8BIT)
