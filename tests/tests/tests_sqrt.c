#include "tests_sqrt.h"
#include "tests.h"

int test_sqrt_specific()
{
    ASSERT_EQ_INT(fix16_sqrt(fix16_from_int(16)), fix16_from_int(4));
    ASSERT_EQ_INT(fix16_sqrt(fix16_from_int(100)), fix16_from_int(10));
    ASSERT_EQ_INT(fix16_sqrt(fix16_from_int(1)), fix16_from_int(1));
#ifndef FIXMATH_NO_ROUNDING
    ASSERT_EQ_INT(fix16_sqrt(214748302), 3751499);
    ASSERT_EQ_INT(fix16_sqrt(214748303), 3751499);
    ASSERT_EQ_INT(fix16_sqrt(214748359), 3751499);
    ASSERT_EQ_INT(fix16_sqrt(214748360), 3751500);
#endif
    return 0;
}

int test_sqrt_short()
{
    for (unsigned i = 0; i < TESTCASES_COUNT; ++i)
    {
        fix16_t a       = testcases[i];
        double  fa      = fix16_to_dbl(a);
        fix16_t result  = fix16_sqrt(a);
        double  fresult = sqrt(fa);
        ASSERT_NEAR_DOUBLE(fresult, fix16_to_dbl(result), fix16_to_dbl(1),
                           "in: %f", fa);
    }
    return 0;
}

int test_sqrt()
{
    TEST(test_sqrt_specific());
    TEST(test_sqrt_short());
    return 0;
}
