/* Regression test candidates, subject to redistribution into their respective suites. */

#include "tests_staging.h"
#include "tests.h"
#include <libfixmath/fract32.h>

/* exp(2) after exp(-2) must not return the cached exp(-2) */
static int test_exp_cache_sign(void)
{
    ASSERT_NEAR_DOUBLE(exp(-2.0), fix16_to_dbl(fix16_exp(fix16_from_int(-2))),
                       0.001, "exp(-2) should be ~0.135");
    ASSERT_NEAR_DOUBLE(exp(2.0), fix16_to_dbl(fix16_exp(fix16_from_int(2))),
                       0.01, "exp(2) after exp(-2) should be ~7.389");
    return 0;
}

/* exp(-11) is a tiny positive value */
static int test_exp_negative_tail(void)
{
    ASSERT_NEAR_DOUBLE(exp(-11.0), fix16_to_dbl(fix16_exp(fix16_from_int(-11))),
                       fix16_to_dbl(2), "exp(-11) should be ~1.7e-5");
    return 0;
}

/* Half of 100 is 50 */
static int test_fract32_create_half(void)
{
#ifndef FIXMATH_NO_64BIT
    ASSERT_EQ_INT(fract32_usmul(100, fract32_create(1, 2)), 50);
#endif
    return 0;
}

/* log2(2^-15) = -15 */
static int test_log2_small(void)
{
    ASSERT_NEAR_DOUBLE(-15.0, fix16_to_dbl(fix16_log2(2)), 0.01,
                       "log2(2^-15) should be -15");
    return 0;
}

/* 256.0000153 * 255.9999847 is about 65536, far above the maximum */
static int test_mul_overflow(void)
{
#ifndef FIXMATH_NO_OVERFLOW
    ASSERT_EQ_INT(fix16_mul(0x01000001, 0x00FFFFFF), fix16_overflow);
#endif
    return 0;
}

/* 25 / 1092267 is just below 1.5 raw units */
static int test_div_remainder(void)
{
    ASSERT_EQ_INT(fix16_div(25, 0x10AAAB), 1);
    return 0;
}

/* atan of the largest integer is about pi/2 */
static int test_atan_large(void)
{
    ASSERT_NEAR_DOUBLE(atan(32767.0), fix16_to_dbl(fix16_atan(fix16_from_int(32767))),
                       0.01, "atan(32767) should be ~1.571");
    return 0;
}

/* cos is periodic at the top of the range */
static int test_cos_large(void)
{
    ASSERT_NEAR_DOUBLE(fix16_to_dbl(fix16_cos(fix16_maximum - (fix16_pi << 1))),
                       fix16_to_dbl(fix16_cos(fix16_maximum)), fix16_to_dbl(2),
                       "cos(max) should equal cos(max - 2pi)");
    return 0;
}

/* -32768.5 is below the minimum */
static int test_str_below_minimum(void)
{
#ifndef FIXMATH_NO_OVERFLOW
    ASSERT_EQ_INT(fix16_from_str("-32768.5"), fix16_overflow);
#endif
    return 0;
}

int test_staging(void)
{
    TEST(test_exp_cache_sign());
    TEST(test_exp_negative_tail());
    TEST(test_fract32_create_half());
    TEST(test_log2_small());
    TEST(test_mul_overflow());
    TEST(test_div_remainder());
    TEST(test_atan_large());
    TEST(test_cos_large());
    TEST(test_str_below_minimum());
    return 0;
}
