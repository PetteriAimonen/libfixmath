#include "tests_basic.h"
#include "tests.h"

int test_abs_short(void)
{
    for (unsigned i = 0; i < TESTCASES_COUNT; ++i)
    {
        fix16_t a      = testcases[i];
        double fa      = fix16_to_dbl(a);
        fix16_t result = fix16_abs(a);
        double fresult = fabs(fa);
        ASSERT_NEAR_DOUBLE(fresult, fix16_to_dbl(result), fix16_to_dbl(1));
    }
    return 0;
}

int test_abs_long(void)
{
    for (unsigned i = 0; i < 10000; ++i)
    {
        fix16_t a      = -rand();
        double fa      = fix16_to_dbl(a);
        fix16_t result = fix16_abs(a);
        double fresult = fabs(fa);
        ASSERT_NEAR_DOUBLE(fresult, fix16_to_dbl(result), fix16_to_dbl(1));
    }
    return 0;
}

int test_abs(void)
{
    TEST(test_abs_short());
    TEST(test_abs_long());
    return 0;
}

int test_add_short(void)
{
    for (unsigned i = 0; i < TESTCASES_COUNT; ++i)
    {
        for (unsigned j = 0; j < TESTCASES_COUNT; ++j)
        {
            fix16_t a      = testcases[i];
            fix16_t b      = testcases[j];
            double fa      = fix16_to_dbl(a);
            double fb      = fix16_to_dbl(b);
            fix16_t result = fix16_add(a, b);
            double fresult = fa + fb;
            ASSERT_NEAR_DOUBLE(fresult, fix16_to_dbl(result), fix16_to_dbl(1));
        }
    }
    return 0;
}

int test_add(void)
{
    TEST(test_add_short());
    return 0;
}
