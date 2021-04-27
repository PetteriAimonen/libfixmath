#include "tests_basic.h"
#include "tests.h"

int test_abs_short(void)
{
    for (unsigned i = 0; i < TESTCASES_COUNT; ++i)
    {
        fix16_t a       = testcases[i];
        double  fa      = fix16_to_dbl(a);
        fix16_t result  = fix16_abs(a);
        double  fresult = fabs(fa);
        double  min     = fix16_to_dbl(fix16_minimum);
        if (fa <= min)
        {
#ifndef FIXMATH_NO_OVERFLOW
            ASSERT_EQ_INT(result, fix16_overflow);
#endif
        }
        else
        {
            ASSERT_NEAR_DOUBLE(fresult, fix16_to_dbl(result), fix16_to_dbl(1));
        }
    }
    return 0;
}

int test_abs_long(void)
{
    for (unsigned i = 0; i < 10000; ++i)
    {
        fix16_t a       = -rand();
        double  fa      = fix16_to_dbl(a);
        fix16_t result  = fix16_abs(a);
        double  fresult = fabs(fa);
        double  min     = fix16_to_dbl(fix16_minimum);
        if (fa <= min)
        {
#ifndef FIXMATH_NO_OVERFLOW
            ASSERT_EQ_INT(result, fix16_overflow);
#endif
        }
        else
        {
            ASSERT_NEAR_DOUBLE(fresult, fix16_to_dbl(result), fix16_to_dbl(1));
        }
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
            fix16_t result = fix16_add(a, b);

            double fa      = fix16_to_dbl(a);
            double fb      = fix16_to_dbl(b);
            double fresult = fa + fb;

            double max = fix16_to_dbl(fix16_maximum);
            double min = fix16_to_dbl(fix16_minimum);
            if ((fa + fb > max) || (fa + fb < min))
            {
#ifndef FIXMATH_NO_OVERFLOW
                ASSERT_EQ_INT(result, fix16_overflow);
#endif
            }
            else
            {
                ASSERT_NEAR_DOUBLE(fresult, fix16_to_dbl(result),
                                   fix16_to_dbl(1));
            }
        }
    }
    return 0;
}

int test_add(void)
{
    TEST(test_add_short());
    return 0;
}

int test_mul_specific(void)
{
    ASSERT_EQ_INT(fix16_mul(fix16_from_int(5), fix16_from_int(5)),
                  fix16_from_int(25));
    ASSERT_EQ_INT(fix16_mul(fix16_from_int(-5), fix16_from_int(5)),
                  fix16_from_int(-25));
    ASSERT_EQ_INT(fix16_mul(fix16_from_int(-5), fix16_from_int(-5)),
                  fix16_from_int(25));
    ASSERT_EQ_INT(fix16_mul(fix16_from_int(5), fix16_from_int(-5)),
                  fix16_from_int(-25));

    ASSERT_EQ_INT(fix16_mul(0, 10), 0);
    ASSERT_EQ_INT(fix16_mul(2, 0x8000), 1);
    ASSERT_EQ_INT(fix16_mul(-2, 0x8000), -1);
    ASSERT_EQ_INT(fix16_mul(3, 0x8000), 2);
    ASSERT_EQ_INT(fix16_mul(-3, 0x8000), -2);
    ASSERT_EQ_INT(fix16_mul(2, 0x7FFF), 1);
    ASSERT_EQ_INT(fix16_mul(-2, 0x7FFF), -1);
    ASSERT_EQ_INT(fix16_mul(2, 0x8001), 1);
    ASSERT_EQ_INT(fix16_mul(-2, 0x8001), -1);
    return 0;
}

int test_mul_short()
{
    for (unsigned i = 0; i < TESTCASES_COUNT; ++i)
    {
        for (unsigned j = 0; j < TESTCASES_COUNT; ++j)
        {
            fix16_t a      = testcases[i];
            fix16_t b      = testcases[j];
            fix16_t result = fix16_mul(a, b);

            double fa      = fix16_to_dbl(a);
            double fb      = fix16_to_dbl(b);
            double fresult = fa * fb;

            double max = fix16_to_dbl(fix16_maximum);
            double min = fix16_to_dbl(fix16_minimum);

            if (fa * fb > max || fa * fb < min)
            {
#ifndef FIXMATH_NO_OVERFLOW
                ASSERT_EQ_INT(result, fix16_overflow);
#endif
            }
            else
            {
                ASSERT_NEAR_DOUBLE(fresult, fix16_to_dbl(result),
                                   fix16_to_dbl(1));
            }
        }
    }
    return 0;
}

int test_mul(void)
{
    TEST(test_mul_specific());
    TEST(test_mul_short());
    return 0;
}
