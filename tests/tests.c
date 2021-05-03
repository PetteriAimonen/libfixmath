#include "tests.h"
#include "tests_basic.h"
#include "tests_lerp.h"
#include "tests_macros.h"
#include "tests_sqrt.h"
#include "tests_str.h"
#include <stdio.h>

const fix16_t testcases[] = {
    // Small numbers
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10,

    // Integer numbers
    0x10000, -0x10000, 0x20000, -0x20000, 0x30000, -0x30000, 0x40000, -0x40000,
    0x50000, -0x50000, 0x60000, -0x60000,

    // Fractions (1/2, 1/4, 1/8)
    0x8000, -0x8000, 0x4000, -0x4000, 0x2000, -0x2000,

    // Problematic carry
    0xFFFF, -0xFFFF, 0x1FFFF, -0x1FFFF, 0x3FFFF, -0x3FFFF,

    // Smallest and largest values
    0x7FFFFFFF, 0x80000000,

    // Large random numbers
    831858892, 574794913, 2147272293, -469161054, -961611615, 1841960234,
    1992698389, 520485404, 560523116, -2094993050, -876897543, -67813629,
    2146227091, 509861939, -1073573657,

    // Small random numbers
    -14985, 30520, -83587, 41129, 42137, 58537, -2259, 84142, -28283, 90914,
    19865, 33191, 81844, -66273, -63215, -44459, -11326, 84295, 47515, -39324,

    // Tiny random numbers
    -171, -359, 491, 844, 158, -413, -422, -737, -575, -330, -376, 435, -311,
    116, 715, -1024, -487, 59, 724, 993};

unsigned stack_depth = 0;

int main()
{
    printf("\033[1;34m\nVARIANT: \033[39m" STR2(PREFIX) "\033[0m\n");
#if 0
    fix16_t a      = 65536;
    fix16_t b      = -2147483648;
    fix16_t result = fix16_div(a, b);

    double fa      = fix16_to_dbl(a);
    double fb      = fix16_to_dbl(b);
    double fresult = fa / fb;

    double max = fix16_to_dbl(fix16_maximum);
    double min = fix16_to_dbl(fix16_minimum);

    printf("result  %i, %.20f\n", result, fix16_to_dbl(result));
    printf("fresult %i, %.20f\n", fix16_from_dbl(fresult), fresult);

    if ((fa / fb) > max || (fa / fb) < min)
    {
#ifndef FIXMATH_NO_OVERFLOW
        ASSERT_EQ_INT(result, fix16_overflow);
#endif
    }
    else
    {
        ASSERT_NEAR_DOUBLE(fresult, fix16_to_dbl(result),
                           fix16_to_dbl(fix16_eps), "%i / %i \n", a, b);
    }

#else
    TEST(test_abs());
    TEST(test_add());
    TEST(test_mul());
    TEST(test_div());
    TEST(test_sub());
    TEST(test_sqrt());
    TEST(test_lerp());
    TEST(test_macros());
    //TEST(test_str());
#endif
    return 0;
}
