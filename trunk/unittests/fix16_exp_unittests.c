#include <fix16.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "unittests.h"

#define delta(a,b) (((a)>=(b)) ? (a)-(b) : (b)-(a))

int main()
{
    int status = 0;
    {
        COMMENT("Testing fix16_exp() corner cases");
        TEST(fix16_exp(0) == fix16_one);
        TEST(fix16_exp(fix16_minimum) == 0);
        TEST(fix16_exp(fix16_maximum) == fix16_maximum);
    }
    
    {
        COMMENT("Testing fix16_exp() accuracy over -11..4");
        
        fix16_t max_delta = -1;
        fix16_t worst = 0;
        fix16_t sum = 0;
        int count = 0;
        fix16_t a;
        
        for (a = fix16_from_dbl(-11.0); a < fix16_from_dbl(4.0); a += 31)
        {
            fix16_t result = fix16_exp(a);
            fix16_t resultf = fix16_from_dbl(exp(fix16_to_dbl(a)));
            
            fix16_t d = delta(result, resultf);
            if (d > max_delta)
            {
                max_delta = d;
                worst = a;
            }
            
            sum += d;
            count++;
        }
        
        printf("Worst delta %d with input %d\n", max_delta, worst);
        printf("Average delta %0.2f\n", (float)sum / count);
        
        TEST(max_delta < 200);
    }
    
    {
        COMMENT("Testing fix16_exp() accuracy over full range");
        
        float max_delta = -1;
        fix16_t worst = 0;
        float sum = 0;
        int count = 0;
        fix16_t a;
        
        // Test the whole range of results 0..32768 with a bit less samples
        for (a = -772243; a < 681391; a += 113)
        {
            fix16_t result = fix16_exp(a);
            fix16_t resultf = fix16_from_dbl(exp(fix16_to_dbl(a)));
            
            fix16_t d1 = delta(result, resultf);
            
            if (d1 > 0) d1--; // Forgive +-1 for the fix16_t inaccuracy
            
            float d = (float)d1 / resultf * 100;
            
            if (resultf < 1000) continue; // Percentages can explode when result is almost 0.
            
            if (d > max_delta)
            {
                max_delta = d;
                worst = a;
            }
            
            sum += d;
            count++;
        }
        
        printf("Worst delta %0.4f%% with input %d\n", max_delta, worst);
        printf("Average delta %0.4f%%\n", sum / count);
        
        TEST(max_delta < 1);
    }
    
    {
        COMMENT("Testing fix16_log() accuracy over full range");
        
        fix16_t max_delta = -1;
        fix16_t worst = 0;
        fix16_t sum = 0;
        int count = 0;
        fix16_t a;
        
        for (a = 100; a > 0 && a < fix16_maximum - 7561; a += 7561)
        {
            fix16_t result = fix16_log(a);
            fix16_t resultf = fix16_from_dbl(log(fix16_to_dbl(a)));
            
            fix16_t d = delta(result, resultf);
            if (d > max_delta)
            {
                max_delta = d;
                worst = a;
            }
            
            sum += d;
            count++;
        }
        
        printf("Worst delta %d with input %d\n", max_delta, worst);
        printf("Average delta %0.2f\n", (float)sum / count);
        
        TEST(max_delta < 20);
    }
    
    if (status != 0)
    fprintf(stdout, "\n\nSome tests FAILED!\n");

    return status;
}
