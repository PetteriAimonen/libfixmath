file(GLOB tests-srcs tests/*.c tests/*.h)

set(ro64 PREFIX=ro64)
set(no64 PREFIX=no64 FIXMATH_NO_ROUNDING)
set(rn64 PREFIX=rn64 FIXMATH_NO_OVERFLOW)
set(nn64 PREFIX=nn64 FIXMATH_NO_ROUNDING FIXMATH_NO_OVERFLOW)
set(ro32 PREFIX=ro32 FIXMATH_NO_64BIT)
set(no32 PREFIX=no32 FIXMATH_NO_ROUNDING FIXMATH_NO_64BIT)
set(rn32 PREFIX=rn32 FIXMATH_NO_OVERFLOW FIXMATH_NO_64BIT)
set(nn32 PREFIX=nn32 FIXMATH_NO_OVERFLOW FIXMATH_NO_ROUNDING FIXMATH_NO_64BIT)
set(ro08 PREFIX=ro08 FIXMATH_OPTIMIZE_8BIT)
set(no08 PREFIX=no08 FIXMATH_NO_ROUNDING FIXMATH_OPTIMIZE_8BIT)
set(rn08 PREFIX=rn08 FIXMATH_NO_OVERFLOW FIXMATH_OPTIMIZE_8BIT)
set(nn08 PREFIX=nn08 FIXMATH_NO_OVERFLOW FIXMATH_NO_ROUNDING FIXMATH_OPTIMIZE_8BIT)

configure_file(tests/run_tests ${CMAKE_BINARY_DIR}/run_tests COPYONLY)

enable_testing()

add_custom_target(make_tests)

function(create_variant name defs)
    add_library(libfixmath_${name} STATIC ${libfixmath-srcs})
    target_compile_definitions(libfixmath_${name} PRIVATE ${defs})
    add_executable(tests_${name} ${tests-srcs})
    target_link_libraries(tests_${name} PRIVATE libfixmath_${name} m)
    target_include_directories(tests_${name} PRIVATE ${CMAKE_SOURCE_DIR})
    target_compile_definitions(tests_${name} PRIVATE ${defs})
    add_dependencies(make_tests tests_${name})
    add_test(NAME tests_${name} COMMAND tests_${name})
endfunction()


create_variant("ro64" "${ro64}")
create_variant("no64" "${no64}")
create_variant("rn64" "${rn64}")
create_variant("nn64" "${nn64}")
create_variant("ro32" "${ro32}")
create_variant("no32" "${no32}")
create_variant("rn32" "${rn32}")
create_variant("nn32" "${nn32}")
create_variant("ro08" "${ro08}")
create_variant("no08" "${no08}")
create_variant("rn08" "${rn08}")
create_variant("nn08" "${nn08}")


