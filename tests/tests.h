#ifndef TESTS_H
#define TESTS_H

#include <libfixmath/fix16.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

extern unsigned stack_depth;

#define delta(a, b) (((a) >= (b)) ? (a) - (b) : (b) - (a))

#define COMMENT(x) printf("\n----" x "----\n");
#define STR(x)     #x
#define STR2(x)    STR(x)
#define TEST(x)                                                       \
    do                                                                \
    {                                                                 \
        ++stack_depth;                                                \
        if ((x))                                                      \
        {                                                             \
            fflush(stdout);                                           \
            fflush(stderr);                                           \
            fprintf(stdout,                                           \
                    "\033[31;1mFAILED:\033[22;39m%*s" #x              \
                    " \033[0mat: " __FILE__ ":" STR2(__LINE__) " \n", \
                    stack_depth, "");                                 \
            --stack_depth;                                            \
            return 1;                                                 \
        }                                                             \
        else                                                          \
        {                                                             \
            fflush(stdout);                                           \
            fflush(stderr);                                           \
            printf("\033[32;1m    OK:\033[22;39m%*s" #x "\n\033[0m",  \
                   stack_depth, "");                                  \
        }                                                             \
        --stack_depth;                                                \
    } while (0)

#define ASSERT_NEAR_DOUBLE(a, b, eps)                                       \
    do                                                                      \
    {                                                                       \
        if ((delta((a), (b)) >= (eps)))                                     \
        {                                                                   \
            fflush(stdout);                                                 \
            fflush(stderr);                                                 \
            fprintf(stdout,                                                 \
                    "\033[31;1mFAILED:\033[22;39m%*sASSERT_NEAR a: %f, b: " \
                    "%f, eps: %f\033[0m at: %s(), " __FILE__                \
                    ":" STR2(__LINE__) "\n",                                \
                    stack_depth, "", (a), (b), (eps), __func__);            \
            return 1;                                                       \
        }                                                                   \
    } while (0)

#define ASSERT_EQ_INT(a, b)                                                  \
    do                                                                       \
    {                                                                        \
        if ((a) != (b))                                                      \
        {                                                                    \
            fflush(stdout);                                                  \
            fflush(stderr);                                                  \
            fprintf(stdout,                                                  \
                    "\033[31;1mFAILED:\033[22;39m%*sASSERT_EQ a: %i, b: "    \
                    "%i\033[0m at: %s(), " __FILE__ ":" STR2(__LINE__) "\n", \
                    stack_depth, "", (a), (b), __func__);                    \
            return 1;                                                        \
        }                                                                    \
    } while (0)

extern const fix16_t testcases[102];

#define TESTCASES_COUNT (sizeof(testcases) / sizeof(testcases[0]))

#define delta(a, b) (((a) >= (b)) ? (a) - (b) : (b) - (a))

#endif // TESTS_H
