#include <stdio.h>
#include "interface.h"

void print_value(const char *label, int32_t value)
{
    printf("%-20s %6ld\n", label, value);
}

void print(const char *label, cyclecount_t *count)
{
    printf("%-20s %6ld %6ld %6ld\n",label,count->min, count->sum / count->count, count->max);
}
