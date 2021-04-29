#include "tests_lerp.h"
#include "tests.h"

int test_lerp()
{
    ASSERT_EQ_INT(fix16_lerp8(0, 2, 0), 0);
    ASSERT_EQ_INT(fix16_lerp8(0, 2, 127), 0);
    ASSERT_EQ_INT(fix16_lerp8(0, 2, 128), 1);
    ASSERT_EQ_INT(fix16_lerp8(0, 2, 255), 1);
    ASSERT_EQ_INT(fix16_lerp8(fix16_minimum, fix16_maximum, 0), fix16_minimum);
    ASSERT_EQ_INT(fix16_lerp8(fix16_minimum, fix16_maximum, 255),
                  (fix16_maximum - (1 << 24)));
    ASSERT_EQ_INT(fix16_lerp8(-fix16_maximum, fix16_maximum, 128), 0);

    ASSERT_EQ_INT(fix16_lerp16(0, 2, 0), 0);
    ASSERT_EQ_INT(fix16_lerp16(0, 2, 0x7fff), 0);
    ASSERT_EQ_INT(fix16_lerp16(0, 2, 0x8000), 1);
    ASSERT_EQ_INT(fix16_lerp16(0, 2, 0xffff), 1);
    ASSERT_EQ_INT(fix16_lerp16(fix16_minimum, fix16_maximum, 0), fix16_minimum);
    ASSERT_EQ_INT(fix16_lerp16(fix16_minimum, fix16_maximum, 0xffff),
                  (fix16_maximum - (1 << 16)));
    ASSERT_EQ_INT(fix16_lerp16(-fix16_maximum, fix16_maximum, 0x8000), 0);

    ASSERT_EQ_INT(fix16_lerp32(0, 2, 0), 0);
    ASSERT_EQ_INT(fix16_lerp32(0, 2, 0x7fffffff), 0);
    ASSERT_EQ_INT(fix16_lerp32(0, 2, 0x80000000), 1);
    ASSERT_EQ_INT(fix16_lerp32(0, 2, 0xffffffff), 1);
    ASSERT_EQ_INT(fix16_lerp32(fix16_minimum, fix16_maximum, 0), fix16_minimum);
    ASSERT_EQ_INT(fix16_lerp32(fix16_minimum, fix16_maximum, 0xffffffff),
                  (fix16_maximum - 1));
    ASSERT_EQ_INT(fix16_lerp32(-fix16_maximum, fix16_maximum, 0x80000000), 0);
    return 0;
}
