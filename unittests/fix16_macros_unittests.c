/* This test checks that the F16() and F16C() macros work correctly. */

#include <libfixmath/fix16.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "unittests.h"

#define DO_TEST(i,m) \
  TEST(F16(i ## . ## m) == F16C(i,m)) \
  TEST(F16(i ## . ## m) == fix16_from_dbl(i ## . ## m))

int main()
{
  int status = 0;

  /* Corner cases */
  DO_TEST(1,234)
  DO_TEST(0,0)
  DO_TEST(1,0)
  DO_TEST(-1,0)
  DO_TEST(1,5)
  DO_TEST(-1,5)
  DO_TEST(000000,00000)
  DO_TEST(0,00001)
  DO_TEST(0,00010)
  DO_TEST(0,1)
  DO_TEST(0,10001)
  DO_TEST(0,11000)
  DO_TEST(25,133)
  DO_TEST(32767,00000)
  DO_TEST(32767,00001)
  DO_TEST(32767,99999)
  DO_TEST(0,25)
  DO_TEST(0,99555)
  DO_TEST(0,99998)
  DO_TEST(0,99999)
  DO_TEST(-1,1)
  DO_TEST(-25,133)
  DO_TEST(-32767,00001)
  DO_TEST(-32768,00000)
  
  /* Random values */
  DO_TEST(   0,02267)
  DO_TEST(   1,49887)
  DO_TEST(   0,27589)
  DO_TEST(   0,38393)
  DO_TEST(   0,08934)
  DO_TEST(   0,95820)
  DO_TEST(   0,95596)
  DO_TEST(  72,10642)
  DO_TEST(   0,48939)
  DO_TEST(   3,37797)
  DO_TEST(   1,09194)
  DO_TEST(   0,08605)
  DO_TEST(   3,04349)
  DO_TEST(   3,95401)
  DO_TEST(  15,36292)
  DO_TEST(  56,09242)
  DO_TEST(   0,54071)
  DO_TEST(  27,08953)
  DO_TEST(   0,03913)
  DO_TEST(   1,32707)
  DO_TEST(   4,50117)
  DO_TEST(   0,24990)
  DO_TEST(  44,77319)
  DO_TEST(   2,59139)
  DO_TEST(   0,16279)
  DO_TEST(  17,14712)
  DO_TEST(  11,54281)
  DO_TEST(   0,02768)
  DO_TEST(   0,39278)
  DO_TEST(   0,19369)
  DO_TEST(  -0,04534)
  DO_TEST(  -0,00349)
  DO_TEST(  -2,30380)
  DO_TEST(  -0,03061)
  DO_TEST(  -7,50065)
  DO_TEST(  -3,97050)
  DO_TEST(  -0,43898)
  DO_TEST(  -3,49876)
  DO_TEST(  -1,35942)
  DO_TEST( -10,81154)
  DO_TEST(  -0,26676)
  DO_TEST(  -9,52134)
  DO_TEST(  -0,42592)
  DO_TEST(  -0,05424)
  DO_TEST(  -0,62461)
  DO_TEST(  -0,21562)
  DO_TEST(  -0,22366)
  DO_TEST(  -0,09074)
  DO_TEST(  -1,29527)
  DO_TEST(  -4,98427)
  DO_TEST(  -0,10721)
  DO_TEST( -11,39446)
  DO_TEST(-451,53916)
  DO_TEST(  -0,04279)
  DO_TEST(  -3,36543)
  DO_TEST(  -0,01003)
  DO_TEST( -12,08326)
  DO_TEST(  -1,07143)
  DO_TEST(  -1,07737)
  DO_TEST(  -0,22957)
    
  if (status != 0)
    fprintf(stdout, "\n\nSome tests FAILED!\n");
  
  return status;
}

