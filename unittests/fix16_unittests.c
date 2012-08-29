#include <fix16.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "unittests.h"

const fix16_t testcases[] = {
  // Small numbers
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
  -1, -2, -3, -4, -5, -6, -7, -8, -9, -10,
  
  // Integer numbers
  0x10000, -0x10000, 0x20000, -0x20000, 0x30000, -0x30000,
  0x40000, -0x40000, 0x50000, -0x50000, 0x60000, -0x60000,
  
  // Fractions (1/2, 1/4, 1/8)
  0x8000, -0x8000, 0x4000, -0x4000, 0x2000, -0x2000,
  
  // Problematic carry
  0xFFFF, -0xFFFF, 0x1FFFF, -0x1FFFF, 0x3FFFF, -0x3FFFF,
  
  // Smallest and largest values
  0x7FFFFFFF, 0x80000000,
  
  // Large random numbers
  831858892, 574794913, 2147272293, -469161054, -961611615,
  1841960234, 1992698389, 520485404, 560523116, -2094993050,
  -876897543, -67813629, 2146227091, 509861939, -1073573657,
  
  // Small random numbers
  -14985, 30520, -83587, 41129, 42137, 58537, -2259, 84142,
  -28283, 90914, 19865, 33191, 81844, -66273, -63215, -44459,
  -11326, 84295, 47515, -39324,
  
  // Tiny random numbers
  -171, -359, 491, 844, 158, -413, -422, -737, -575, -330,
  -376, 435, -311, 116, 715, -1024, -487, 59, 724, 993
};

#define TESTCASES_COUNT (sizeof(testcases)/sizeof(testcases[0]))

#define delta(a,b) (((a)>=(b)) ? (a)-(b) : (b)-(a))

#ifdef FIXMATH_NO_ROUNDING
const fix16_t max_delta = 1;
#else
const fix16_t max_delta = 0;
#endif

int main()
{
  int status = 0;
  
  {
    COMMENT("Testing basic multiplication");
    TEST(fix16_mul(fix16_from_int(5), fix16_from_int(5)) == fix16_from_int(25));
    TEST(fix16_mul(fix16_from_int(-5), fix16_from_int(5)) == fix16_from_int(-25));
    TEST(fix16_mul(fix16_from_int(-5), fix16_from_int(-5)) == fix16_from_int(25));
    TEST(fix16_mul(fix16_from_int(5), fix16_from_int(-5)) == fix16_from_int(-25));
  }
  
#ifndef FIXMATH_NO_ROUNDING
  {
    COMMENT("Testing multiplication rounding corner cases");
    TEST(fix16_mul(0, 10) == 0);
    TEST(fix16_mul(2, 0x8000) == 1);
    TEST(fix16_mul(-2, 0x8000) == -1);
    TEST(fix16_mul(3, 0x8000) == 2);
    TEST(fix16_mul(-3, 0x8000) == -2);
    TEST(fix16_mul(2, 0x7FFF) == 1);
    TEST(fix16_mul(-2, 0x7FFF) == -1);
    TEST(fix16_mul(2, 0x8001) == 1);
    TEST(fix16_mul(-2, 0x8001) == -1);
  }
#endif
  
  {
    unsigned int i, j;
    int failures = 0;
    COMMENT("Running testcases for multiplication");
    
    for (i = 0; i < TESTCASES_COUNT; i++)
    {
      for (j = 0; j < TESTCASES_COUNT; j++)
      {
        fix16_t a = testcases[i];
        fix16_t b = testcases[j];
        fix16_t result = fix16_mul(a, b);
        
        double fa = fix16_to_dbl(a);
        double fb = fix16_to_dbl(b);
        fix16_t fresult = fix16_from_dbl(fa * fb);
        
        double max = fix16_to_dbl(fix16_maximum);
        double min = fix16_to_dbl(fix16_minimum);
        
        if (delta(fresult, result) > max_delta)
        {
          if (fa * fb > max || fa * fb < min)
          {
            #ifndef FIXMATH_NO_OVERFLOW
            if (result != fix16_overflow)
            {
              printf("\n%d * %d overflow not detected!\n", a, b);
              failures++;
            }
            #endif
            // Legitimate overflow
            continue;
          }
          
          printf("\n%d * %d = %d\n", a, b, result);
          printf("%f * %f = %d\n", fa, fb, fresult);
          failures++;
        }
      }
    }
    
    TEST(failures == 0);
  }
  
  {
    COMMENT("Testing basic division");
    TEST(fix16_div(fix16_from_int(15), fix16_from_int(5)) == fix16_from_int(3));
    TEST(fix16_div(fix16_from_int(-15), fix16_from_int(5)) == fix16_from_int(-3));
    TEST(fix16_div(fix16_from_int(-15), fix16_from_int(-5)) == fix16_from_int(3));
    TEST(fix16_div(fix16_from_int(15), fix16_from_int(-5)) == fix16_from_int(-3));
  }
  
#ifndef FIXMATH_NO_ROUNDING
  {
    COMMENT("Testing division rounding corner cases");
    TEST(fix16_div(0, 10) == 0);
    TEST(fix16_div(1, fix16_from_int(2)) == 1);
    TEST(fix16_div(-1, fix16_from_int(2)) == -1);
    TEST(fix16_div(1, fix16_from_int(-2)) == -1);
    TEST(fix16_div(-1, fix16_from_int(-2)) == 1);
    TEST(fix16_div(3, fix16_from_int(2)) == 2);
    TEST(fix16_div(-3, fix16_from_int(2)) == -2);
    TEST(fix16_div(3, fix16_from_int(-2)) == -2);
    TEST(fix16_div(-3, fix16_from_int(-2)) == 2);
    TEST(fix16_div(2, 0x7FFF) == 4);
    TEST(fix16_div(-2, 0x7FFF) == -4);
    TEST(fix16_div(2, 0x8001) == 4);
    TEST(fix16_div(-2, 0x8001) == -4);
  }
#endif
  
  {
    unsigned int i, j;
    int failures = 0;
    COMMENT("Running testcases for division");
    
    for (i = 0; i < TESTCASES_COUNT; i++)
    {
      for (j = 0; j < TESTCASES_COUNT; j++)
      {
        fix16_t a = testcases[i];
        fix16_t b = testcases[j];
        
        // We don't require a solution for /0 :)
        if (b == 0) continue;
        
        fix16_t result = fix16_div(a, b);
        
        double fa = fix16_to_dbl(a);
        double fb = fix16_to_dbl(b);
        fix16_t fresult = fix16_from_dbl(fa / fb);
        
        double max = fix16_to_dbl(fix16_maximum);
        double min = fix16_to_dbl(fix16_minimum);        
        if (delta(fresult, result) > max_delta)
        {
          if (fa / fb > max || fa / fb < min)
          {
            #ifndef FIXMATH_NO_OVERFLOW
            if (result != fix16_overflow)
            {
              printf("\n%d / %d overflow not detected!\n", a, b);
              failures++;
            }
            #endif
            // Legitimate overflow
            continue;
          }
          
          printf("\n%d / %d = %d\n", a, b, result);
          printf("%f / %f = %d\n", fa, fb, fresult);
          failures++;
        }
      }
    }
    
    TEST(failures == 0);
  }
  
  {
    unsigned int i, j;
    int failures = 0;
    COMMENT("Running testcases for addition");
    
    for (i = 0; i < TESTCASES_COUNT; i++)
    {
      for (j = 0; j < TESTCASES_COUNT; j++)
      {
        fix16_t a = testcases[i];
        fix16_t b = testcases[j];
        
        fix16_t result = fix16_add(a, b);
        
        double fa = fix16_to_dbl(a);
        double fb = fix16_to_dbl(b);
        fix16_t fresult = fix16_from_dbl(fa + fb);
        
        double max = fix16_to_dbl(fix16_maximum);
        double min = fix16_to_dbl(fix16_minimum);
        
        if (delta(fresult, result) > max_delta)
        {
          if (fa + fb > max || fa + fb < min)
          {
            #ifndef FIXMATH_NO_OVERFLOW
            if (result != fix16_overflow)
            {
              printf("\n%d + %d overflow not detected!\n", a, b);
              failures++;
            }
            #endif
            // Legitimate overflow
            continue;
          }
          
          printf("\n%d + %d = %d\n", a, b, result);
          printf("%f + %f = %d\n", fa, fb, fresult);
          failures++;
        }
      }
    }
    
    TEST(failures == 0);
  }
  
  {
    unsigned int i, j;
    int failures = 0;
    COMMENT("Running testcases for subtraction");
    
    for (i = 0; i < TESTCASES_COUNT; i++)
    {
      for (j = 0; j < TESTCASES_COUNT; j++)
      {
        fix16_t a = testcases[i];
        fix16_t b = testcases[j];
        
        fix16_t result = fix16_sub(a, b);
        
        double fa = fix16_to_dbl(a);
        double fb = fix16_to_dbl(b);
        fix16_t fresult = fix16_from_dbl(fa - fb);
        
        double max = fix16_to_dbl(fix16_maximum);
        double min = fix16_to_dbl(fix16_minimum);
        
        if (delta(fresult, result) > max_delta)
        {
          if (fa - fb > max || fa - fb < min)
          {
            #ifndef FIXMATH_NO_OVERFLOW
            if (result != fix16_overflow)
            {
              printf("\n%d - %d overflow not detected!\n", a, b);
              failures++;
            }
            #endif
            // Legitimate overflow
            continue;
          }
          
          printf("\n%d - %d = %d\n", a, b, result);
          printf("%f - %f = %d\n", fa, fb, fresult);
          failures++;
        }
      }
    }
    
    TEST(failures == 0);
  }
  
  {
    COMMENT("Testing basic square roots");
    TEST(fix16_sqrt(fix16_from_int(16)) == fix16_from_int(4));
    TEST(fix16_sqrt(fix16_from_int(100)) == fix16_from_int(10));
    TEST(fix16_sqrt(fix16_from_int(1)) == fix16_from_int(1));
  }
  
#ifndef FIXMATH_NO_ROUNDING
  {
    COMMENT("Testing square root rounding corner cases");
    TEST(fix16_sqrt(214748302) == 3751499);
    TEST(fix16_sqrt(214748303) == 3751499);
    TEST(fix16_sqrt(214748359) == 3751499);
    TEST(fix16_sqrt(214748360) == 3751500);
  }
#endif
  
  {
    unsigned int i;
    int failures = 0;
    COMMENT("Running test cases for square root");
    
    for (i = 0; i < TESTCASES_COUNT; i++)
    {
      fix16_t a = testcases[i];
      
      if (a < 0) continue;
      
      fix16_t result = fix16_sqrt(a);
      
      double fa = fix16_to_dbl(a);
      fix16_t fresult = fix16_from_dbl(sqrt(fa));
      
      if (delta(fresult, result) > max_delta)
      {
        printf("\nfix16_sqrt(%d) = %d\n", a, result);
        printf("sqrt(%f) = %d\n", fa, fresult);
        failures++;
      }
    }
    
    TEST(failures == 0);
  }
  
  if (status != 0)
    fprintf(stdout, "\n\nSome tests FAILED!\n");
  
  return status;
}
