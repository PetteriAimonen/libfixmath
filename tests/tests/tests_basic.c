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
            ASSERT_NEAR_DOUBLE(fresult, fix16_to_dbl(result),
                               fix16_to_dbl(fix16_eps), "in: %f", fa);
        }
    }
    return 0;
}

int test_abs(void)
{
    TEST(test_abs_short());
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
                                   fix16_to_dbl(fix16_eps), "%f + %f", fa, fb);
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
#ifndef FIXMATH_NO_ROUNDING
    ASSERT_EQ_INT(fix16_mul(3, 0x8000), 2);
    ASSERT_EQ_INT(fix16_mul(2, 0x7FFF), 1);
    ASSERT_EQ_INT(fix16_mul(-2, 0x8001), -1);
    ASSERT_EQ_INT(fix16_mul(-3, 0x8000), -2);
    ASSERT_EQ_INT(fix16_mul(-2, 0x7FFF), -1);
    ASSERT_EQ_INT(fix16_mul(2, 0x8001), 1);
#endif
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
                                   fix16_to_dbl(fix16_eps), "%f * %f", fa, fb);
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

int test_div_specific()
{
    ASSERT_EQ_INT(fix16_div(fix16_from_int(15), fix16_from_int(5)),
                  fix16_from_int(3));
    ASSERT_EQ_INT(fix16_div(fix16_from_int(-15), fix16_from_int(5)),
                  fix16_from_int(-3));
    ASSERT_EQ_INT(fix16_div(fix16_from_int(-15), fix16_from_int(-5)),
                  fix16_from_int(3));
    ASSERT_EQ_INT(fix16_div(fix16_from_int(15), fix16_from_int(-5)),
                  fix16_from_int(-3));

#ifndef FIXMATH_NO_ROUNDING
    ASSERT_EQ_INT(fix16_div(0, 10), 0);
    ASSERT_EQ_INT(fix16_div(1, fix16_from_int(2)), 1);
    ASSERT_EQ_INT(fix16_div(-1, fix16_from_int(2)), -1);
    ASSERT_EQ_INT(fix16_div(1, fix16_from_int(-2)), -1);
    ASSERT_EQ_INT(fix16_div(-1, fix16_from_int(-2)), 1);
    ASSERT_EQ_INT(fix16_div(3, fix16_from_int(2)), 2);
    ASSERT_EQ_INT(fix16_div(-3, fix16_from_int(2)), -2);
    ASSERT_EQ_INT(fix16_div(3, fix16_from_int(-2)), -2);
    ASSERT_EQ_INT(fix16_div(-3, fix16_from_int(-2)), 2);
    ASSERT_EQ_INT(fix16_div(2, 0x7FFF), 4);
    ASSERT_EQ_INT(fix16_div(-2, 0x7FFF), -4);
    ASSERT_EQ_INT(fix16_div(2, 0x8001), 4);
    ASSERT_EQ_INT(fix16_div(-2, 0x8001), -4);
#endif

    return 0;
}

int test_div_short()
{
    for (unsigned i = 0; i < TESTCASES_COUNT; ++i)
    {
        for (unsigned j = 0; j < TESTCASES_COUNT; ++j)
        {
            fix16_t a = testcases[i];
            fix16_t b = testcases[j];
            // We don't require a solution for /0 :)
            if (b == 0)
                continue;
            fix16_t result = fix16_div(a, b);

            double fa      = fix16_to_dbl(a);
            double fb      = fix16_to_dbl(b);
            double fresult = fa / fb;

            double max = fix16_to_dbl(fix16_maximum);
            double min = fix16_to_dbl(fix16_minimum);

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
        }
    }
    return 0;
}

int test_div(void)
{
    TEST(test_div_specific());
    TEST(test_div_short());
    return 0;
}

int test_sub_short()
{
    for (unsigned i = 0; i < TESTCASES_COUNT; ++i)
    {
        for (unsigned j = 0; j < TESTCASES_COUNT; ++j)
        {
            fix16_t a      = testcases[i];
            fix16_t b      = testcases[j];
            fix16_t result = fix16_sub(a, b);

            double fa      = fix16_to_dbl(a);
            double fb      = fix16_to_dbl(b);
            double fresult = fa - fb;

            double max = fix16_to_dbl(fix16_maximum);
            double min = fix16_to_dbl(fix16_minimum);
            if ((fa - fb > max) || (fa - fb < min))
            {
#ifndef FIXMATH_NO_OVERFLOW
                ASSERT_EQ_INT(result, fix16_overflow);
#endif
            }
            else
            {
                ASSERT_NEAR_DOUBLE(fresult, fix16_to_dbl(result),
                                   fix16_to_dbl(fix16_eps), "%f - %f", fa, fb);
            }
        }
    }
    return 0;
}

int test_sub()
{
    TEST(test_sub_short());
    return 0;
}
