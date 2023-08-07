# libfixmath

This is a mirror of the libfixmath's original SVN repository on Google Code.

**Not actively maintained, pull requests welcome.**

Libfixmath implements Q16.16 format fixed point operations in C.

License: <a href="http://www.opensource.org/licenses/mit-license.php">MIT</a>

# Options

Configuration options are compile definitions that are checked by the preprocessor with `#ifdef` and `#ifndef`.  All of these are undefined by default.

#### `FIXMATH_FAST_SIN`

- `#ifndef`: Most accurate version, accurate to ~2.1%.
- `#ifdef`: Fast implementation, runs at 159% the speed of above 'accurate' version with a slightly lower accuracy of ~2.3%.

#### `FIXMATH_NO_64BIT`

- `#ifndef`: For compilers/platforms that have `uint64_t`.
- `#ifdef`: For compilers/platforms that do not have `uint64_t`.

#### `FIXMATH_NO_CACHE`

- `#ifndef`: Use static memory caches for exponents (32KB) and trigonometry (80KB). 
- `#ifdef`: Do not use caches.

#### `FIXMATH_NO_HARD_DIVISION`

Note: will be automatically defined if `FIXMATH_OPTIMIZE_8BIT` is defined.

- `#ifndef`: For platforms that have hardware integer division.
- `#ifdef`: For platforms that do not have hardware integer division.

#### `FIXMATH_NO_OVERFLOW`

- `#ifndef`: Check for overflow and return the overflow constants. 
- `#ifdef`: Do not check for overflow.

#### `FIXMATH_NO_ROUNDING`

- `#ifndef`: Use rounding. 
- `#ifdef`: Do not use rounding.

#### `FIXMATH_OPTIMIZE_8BIT`

- `#ifndef`: Do not optimize for processors with 8-bit multiplication like Atmel AVR. 
- `#ifdef`: Optimize for processors like Atmel AVR.  Also defines `FIXMATH_NO_HARD_DIVISION` automatically in `fix16.h`.

# Include the `libfixmath` library in your CMake Project

The simplest way to use `libfixmath` as a dependency is with CMake's [FetchContent API](https://cmake.org/cmake/help/latest/module/FetchContent.html).

```cmake
include(FetchContent)
FetchContent_Declare(
    libfixmath
    GIT_REPOSITORY https://github.com/PetteriAimonen/libfixmath.git
    GIT_TAG <the long git hash of the version you want>
)
FetchContent_MakeAvailable(libfixmath)

target_compile_definitions(libfixmath PRIVATE
    # FIXMATH_FAST_SIN
    # FIXMATH_NO_64BIT
    # FIXMATH_NO_CACHE
    # FIXMATH_NO_HARD_DIVISION
    # FIXMATH_NO_OVERFLOW
    # FIXMATH_NO_ROUNDING
    # FIXMATH_OPTIMIZE_8BIT
)

target_link_libraries(my_cmake_project PRIVATE libfixmath)
```