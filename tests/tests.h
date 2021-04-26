#ifndef TESTS_H
#define TESTS_H

#include <libfixmath/fix16.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define delta(a, b) (((a) >= (b)) ? (a) - (b) : (b) - (a))

#define COMMENT(x) printf("\n----" x "----\n");
#define STR(x)     #x
#define STR2(x)    STR(x)
#define TEST(x)                                                  \
    if ((x))                                                     \
    {                                                            \
        fflush(stdout);                                          \
        fflush(stderr);                                          \
        fprintf(stdout, "\033[31;1mFAILED:\033[22;39m " __FILE__ \
                        ":" STR2(__LINE__) " " #x "\n");         \
        return 1;                                                \
    }                                                            \
    else                                                         \
    {                                                            \
        fflush(stdout);                                          \
        fflush(stderr);                                          \
        printf("\033[32;1mOK:\033[22;39m " #x "\n");             \
    }

#define ASSERT_NEAR_DOUBLE(a, b, eps)                           \
    if ((delta((a), (b)) >= (eps)))                             \
    {                                                           \
        fflush(stdout);                                         \
        fflush(stderr);                                         \
        fprintf(stdout,                                         \
                "\033[31;1mFAILED:\033[22;39m " __FILE__        \
                ":" STR2(__LINE__) " a: %f, b: %f, eps: %f \n", \
                (a), (b), (eps));                               \
        return 1;                                               \
    }

extern const fix16_t testcases[102];

#define TESTCASES_COUNT (sizeof(testcases) / sizeof(testcases[0]))

#define delta(a, b) (((a) >= (b)) ? (a) - (b) : (b) - (a))

#endif // TESTS_H
