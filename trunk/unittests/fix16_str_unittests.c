#include <fix16.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "unittests.h"

int main()
{
    int status = 0;

    {
        COMMENT("Testing fix16_to_str corner cases");
        char buf[13];
        
        fix16_to_str(fix16_from_dbl(1234.5678), buf, 4);
        printf("1234.5678 = %s\n", buf);
        TEST(strcmp(buf, "1234.5678") == 0);
        
        fix16_to_str(fix16_from_dbl(-1234.5678), buf, 4);
        printf("-1234.5678 = %s\n", buf);
        TEST(strcmp(buf, "-1234.5678") == 0);
     
        fix16_to_str(0, buf, 0);
        TEST(strcmp(buf, "0") == 0);
     
        fix16_to_str(fix16_from_dbl(0.9), buf, 0);
        TEST(strcmp(buf, "1") == 0);
     
        fix16_to_str(1, buf, 5);
        printf("(fix16_t)1 = %s\n", buf);
        TEST(strcmp(buf, "0.00002") == 0);
        
        fix16_to_str(-1, buf, 5);
        printf("(fix16_t)-1 = %s\n", buf);
        TEST(strcmp(buf, "-0.00002") == 0);
        
        fix16_to_str(65535, buf, 5);
        printf("(fix16_t)65535 = %s\n", buf);
        TEST(strcmp(buf, "0.99998") == 0);

        fix16_to_str(65535, buf, 4);
        printf("(fix16_t)65535 = %s\n", buf);
        TEST(strcmp(buf, "1.0000") == 0);
        
        fix16_to_str(fix16_maximum, buf, 5);
        printf("fix16_maximum = %s\n", buf);
        TEST(strcmp(buf, "32767.99998") == 0);
        
        fix16_to_str(fix16_minimum, buf, 5);
        printf("fix16_minimum = %s\n", buf);
        TEST(strcmp(buf, "-32768.00000") == 0);
    }

    {
        COMMENT("Testing fix16_from_str corner cases");
    
        TEST(fix16_from_str("1234.5678") == fix16_from_dbl(1234.5678));
        TEST(fix16_from_str("-1234.5678") == fix16_from_dbl(-1234.5678));
        TEST(fix16_from_str("   +1234,56780   ") == fix16_from_dbl(1234.5678));
    
        TEST(fix16_from_str("0") == 0);
        TEST(fix16_from_str("1") == fix16_one);
        TEST(fix16_from_str("1.0") == fix16_one);
        TEST(fix16_from_str("1.0000000000") == fix16_one);
        
        TEST(fix16_from_str("0.00002") == 1);
        TEST(fix16_from_str("0.99998") == 65535);
        
        TEST(fix16_from_str("32767.99998") == fix16_maximum);
        TEST(fix16_from_str("-32768.00000") == fix16_minimum);
    }
    
    {
        COMMENT("Extended testing for whole range");
        fix16_t value = fix16_minimum;
        char testbuf[13];
        char goodbuf[13];
        
        bool ok = true;
        while (value < fix16_maximum)
        {
            double fvalue = fix16_to_dbl(value);
        
            /* Turns out we have to jump through some hoops to round
            doubles perfectly for printing: 
            http://stackoverflow.com/questions/994764/rounding-doubles-5-sprintf
            */
            fvalue = round(fvalue * 100000.)/100000.;
        
            snprintf(goodbuf, 13, "%0.5f", fvalue);
            fix16_to_str(value, testbuf, 5);
            
            if (strcmp(goodbuf, testbuf) != 0)
            {
                printf("Value (fix16_t)%d gave %s, should be %s\n", value, testbuf, goodbuf);
                ok = false;
            }
            
            fix16_t roundtrip = fix16_from_str(testbuf);
            if (roundtrip != value)
            {
                printf("Roundtrip failed: (fix16_t)%d -> %s -> (fix16_t)%d\n", value, testbuf, roundtrip);
                ok = false;
            }
        
            value += 0x10001;
        }
        
        TEST(ok);
    }

    if (status != 0)
        fprintf(stdout, "\n\nSome tests FAILED!\n");

    return status;
}
