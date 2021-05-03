#include "tests_str.h"
#include "tests.h"

int test_str_to()
{
    char buf[13];
    fix16_to_str(fix16_from_dbl(1234.5678), buf, 4);
    ASSERT_EQ_STR(buf, "1234.5678");

    fix16_to_str(fix16_from_dbl(-1234.5678), buf, 4);
    ASSERT_EQ_STR(buf, "-1234.5678");

    fix16_to_str(0, buf, 0);
    ASSERT_EQ_STR(buf, "0");

    fix16_to_str(fix16_from_dbl(0.9), buf, 0);
    ASSERT_EQ_STR(buf, "1");

    fix16_to_str(1, buf, 5);
    ASSERT_EQ_STR(buf, "0.00002");

    fix16_to_str(-1, buf, 5);
    ASSERT_EQ_STR(buf, "-0.00002");

    fix16_to_str(65535, buf, 5);
    ASSERT_EQ_STR(buf, "0.99998");

    fix16_to_str(65535, buf, 4);
    ASSERT_EQ_STR(buf, "1.0000");

    fix16_to_str(fix16_maximum, buf, 5);
    ASSERT_EQ_STR(buf, "32767.99998");

    fix16_to_str(fix16_minimum, buf, 5);
    ASSERT_EQ_STR(buf, "-32768.00000");

    return 0;
}

int test_str_from()
{
    ASSERT_EQ_INT(fix16_from_str("1234.5678"), fix16_from_dbl(1234.5678));
    ASSERT_EQ_INT(fix16_from_str("-1234.5678"), fix16_from_dbl(-1234.5678));
    ASSERT_EQ_INT(fix16_from_str("   +1234,56780   "),
                  fix16_from_dbl(1234.5678));

    ASSERT_EQ_INT(fix16_from_str("0"), 0);
    ASSERT_EQ_INT(fix16_from_str("1"), fix16_one);
    ASSERT_EQ_INT(fix16_from_str("1.0"), fix16_one);
    ASSERT_EQ_INT(fix16_from_str("1.0000000000"), fix16_one);

    ASSERT_EQ_INT(fix16_from_str("0.00002"), 1);
    ASSERT_EQ_INT(fix16_from_str("0.99998"), 65535);

    ASSERT_EQ_INT(fix16_from_str("32767.99998"), fix16_maximum);
    ASSERT_EQ_INT(fix16_from_str("-32768.00000"), fix16_minimum);

    return 0;
}

int test_str_extended()
{

    fix16_t value = fix16_minimum;
    char testbuf[13];
    char goodbuf[13];

    while (value < fix16_maximum)
    {
        double fvalue = fix16_to_dbl(value);

        /* Turns out we have to jump through some hoops to round
            doubles perfectly for printing:
            http://stackoverflow.com/questions/994764/rounding-doubles-5-sprintf
            */
        fvalue = round(fvalue * 100000.) / 100000.;

        snprintf(goodbuf, 13, "%0.5f", fvalue);
        fix16_to_str(value, testbuf, 5);

        if (strcmp(goodbuf, testbuf) != 0)
        {
            printf("Value (fix16_t)%d gave %s, should be %s\n", value, testbuf,
                   goodbuf);
            return 1;
        }

        fix16_t roundtrip = fix16_from_str(testbuf);
        if (roundtrip != value)
        {
            printf("Roundtrip failed: (fix16_t)%d -> %s -> (fix16_t)%d\n",
                   value, testbuf, roundtrip);
            return 1;
        }

        value += 0x10001;
    }

    return 0;
}

int test_str()
{
    TEST(test_str_to());
    TEST(test_str_from());
    TEST(test_str_extended());
    return 0;
}
