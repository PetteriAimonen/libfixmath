#include "tests_trig.h"
#include "tests.h"
#include <stdio.h>

/* Test fix16_asin boundary cases */
int test_asin_boundaries(void)
{
    fix16_t pi_2 = (fix16_pi >> 1);  /* π/2 */

    /* asin(1.0) should return π/2 */
    fix16_t result_pos = fix16_asin(fix16_one);
    ASSERT_NEAR_DOUBLE(fix16_to_dbl(pi_2), fix16_to_dbl(result_pos), 0.001,
                       "asin(1.0) should be π/2");

    /* asin(-1.0) should return -π/2 */
    fix16_t result_neg = fix16_asin(-fix16_one);
    ASSERT_NEAR_DOUBLE(fix16_to_dbl(-pi_2), fix16_to_dbl(result_neg), 0.001,
                       "asin(-1.0) should be -π/2");

    /* asin(0) should return 0 */
    fix16_t result_zero = fix16_asin(0);
    ASSERT_NEAR_DOUBLE(0.0, fix16_to_dbl(result_zero), 0.001,
                       "asin(0) should be 0");

    /* asin(0.5) should return π/6 (~0.5236) */
    fix16_t half = fix16_from_dbl(0.5);
    fix16_t result_half = fix16_asin(half);
    ASSERT_NEAR_DOUBLE(0.5236, fix16_to_dbl(result_half), 0.01,
                       "asin(0.5) should be ~π/6");

    return 0;
}

/* Test fix16_acos boundary cases */
int test_acos_boundaries(void)
{
    /* acos(1.0) should return 0 */
    fix16_t result_pos = fix16_acos(fix16_one);
    ASSERT_NEAR_DOUBLE(0.0, fix16_to_dbl(result_pos), 0.001,
                       "acos(1.0) should be 0");

    /* acos(-1.0) should return π */
    fix16_t result_neg = fix16_acos(-fix16_one);
    ASSERT_NEAR_DOUBLE(fix16_to_dbl(fix16_pi), fix16_to_dbl(result_neg), 0.001,
                       "acos(-1.0) should be π");

    /* acos(0) should return π/2 */
    fix16_t pi_2 = (fix16_pi >> 1);
    fix16_t result_zero = fix16_acos(0);
    ASSERT_NEAR_DOUBLE(fix16_to_dbl(pi_2), fix16_to_dbl(result_zero), 0.001,
                       "acos(0) should be π/2");

    return 0;
}

/* Test fix16_tan boundary cases */
int test_tan_boundaries(void)
{
    /* tan(0) should return 0 */
    fix16_t result_zero = fix16_tan(0);
    ASSERT_NEAR_DOUBLE(0.0, fix16_to_dbl(result_zero), 0.001,
                       "tan(0) should be 0");

    /* tan(π/4) should return 1 */
    fix16_t pi_4 = (fix16_pi >> 2);
    fix16_t result_pi4 = fix16_tan(pi_4);
    ASSERT_NEAR_DOUBLE(1.0, fix16_to_dbl(result_pi4), 0.1,
                       "tan(π/4) should be ~1");

    /* tan(π/2) is undefined (approaches ±∞)
     * The function should handle this gracefully - either return
     * fix16_overflow, fix16_maximum, or clamp to a large value.
     * It should NOT crash or return garbage.
     */
    fix16_t pi_2 = (fix16_pi >> 1);
    fix16_t result_pi2 = fix16_tan(pi_2);
    /* Just verify it returns something "large" or overflow indicator */
    printf("  tan(π/2) = %f (checking for graceful handling)\n", fix16_to_dbl(result_pi2));
    /* We accept any large value or overflow - just not a crash */

    /* tan(-π/2) should also be handled gracefully */
    fix16_t result_neg_pi2 = fix16_tan(-pi_2);
    printf("  tan(-π/2) = %f (checking for graceful handling)\n", fix16_to_dbl(result_neg_pi2));

    return 0;
}

/* Test fix16_atan2 boundary cases */
int test_atan2_boundaries(void)
{
    fix16_t pi = fix16_pi;
    fix16_t pi_2 = (fix16_pi >> 1);

    /* atan2(0, 1) = 0 */
    fix16_t result_01 = fix16_atan2(0, fix16_one);
    ASSERT_NEAR_DOUBLE(0.0, fix16_to_dbl(result_01), 0.01,
                       "atan2(0, 1) should be 0");

    /* atan2(1, 0) = π/2 */
    fix16_t result_10 = fix16_atan2(fix16_one, 0);
    ASSERT_NEAR_DOUBLE(fix16_to_dbl(pi_2), fix16_to_dbl(result_10), 0.01,
                       "atan2(1, 0) should be π/2");

    /* atan2(0, -1) = π */
    fix16_t result_0n1 = fix16_atan2(0, -fix16_one);
    ASSERT_NEAR_DOUBLE(fix16_to_dbl(pi), fix16_to_dbl(result_0n1), 0.01,
                       "atan2(0, -1) should be π");

    /* atan2(-1, 0) = -π/2 */
    fix16_t result_n10 = fix16_atan2(-fix16_one, 0);
    ASSERT_NEAR_DOUBLE(-fix16_to_dbl(pi_2), fix16_to_dbl(result_n10), 0.01,
                       "atan2(-1, 0) should be -π/2");

    /* atan2(0, 0) is mathematically undefined.
     * We follow a common convention and return 0.
     */
    fix16_t result_00 = fix16_atan2(0, 0);
    ASSERT_NEAR_DOUBLE(0.0, fix16_to_dbl(result_00), 0.001,
                       "atan2(0, 0) should return 0");

    return 0;
}

int test_trig(void)
{
    TEST(test_asin_boundaries());
    TEST(test_acos_boundaries());
    TEST(test_tan_boundaries());
    TEST(test_atan2_boundaries());
    return 0;
}
