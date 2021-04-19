#include "hiclock.h"
#include <inttypes.h>
#include <libfixmath/fixmath.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define EXP
//#define ATAN
//#define SIN
//#define SQRT

#ifdef EXP
#define fix_func     fix16_exp
#define fix_func_str "fix16_exp"
#define flt_func     expf
#define flt_func_str "expf"
#endif

#ifdef ATAN
#define fix_func     fix16_atan
#define fix_func_str "fix16_atan"
#define flt_func     atanf
#define flt_func_str "atanf"
#endif

#ifdef SIN
#define fix_func     fix16_sin
#define fix_func_str "fix16_sin"
#define flt_func     sinf
#define flt_func_str "sinf"
#endif

#ifdef SQRT
#define fix_func     fix16_sqrt
#define fix_func_str "fix16_sqrt"
#define flt_func     sqrtf
#define flt_func_str "sqrtf"
#endif

int main(int argc, char **argv)
{
    printf("libfixmath test tool\n");

    hiclock_init();

    uintptr_t args = (1 << 8);
    uintptr_t iter = (1 << 8);
    uintptr_t pass = (1 << 8);

    uintptr_t i;
    srand(time(NULL));

    hiclock_t fix_duration = 0;
    hiclock_t flt_duration = 0;
    fix16_t   fix_error    = 0;

    uintptr_t k;
    for (k = 0; k < pass; k++)
    {
        fix16_t fix_args[args];
        for (i = 0; i < args; i++) fix_args[i] = (rand() ^ (rand() << 16));
        fix16_t   fix_result[args];
        hiclock_t fix_start = hiclock();
        for (i = 0; i < iter; i++)
        {
            uintptr_t j;
            for (j = 0; j < args; j++) fix_result[j] = fix_func(fix_args[j]);
        }
        hiclock_t fix_end = hiclock();

        float flt_args[args];
        for (i = 0; i < args; i++) flt_args[i] = fix16_to_float(fix_args[i]);
        float     flt_result[args];
        hiclock_t flt_start = hiclock();
        for (i = 0; i < iter; i++)
        {
            uintptr_t j;
            for (j = 0; j < args; j++) flt_result[j] = flt_func(flt_args[j]);
        }
        hiclock_t flt_end = hiclock();

        for (i = 0; i < args; i++)
            fix_error += abs(fix16_from_float(flt_result[i]) - fix_result[i]);
        flt_duration += (flt_end - flt_start);
        fix_duration += (fix_end - fix_start);
    }

    printf("%16s: %08" PRIuHICLOCK " @ %" PRIu32 "Hz\n", flt_func_str,
           flt_duration, HICLOCKS_PER_SEC);
    printf("%16s: %08" PRIuHICLOCK " @ %" PRIu32 "Hz\n", fix_func_str,
           fix_duration, HICLOCKS_PER_SEC);
    printf("      Difference: %08" PRIiHICLOCK " (% 3.2f%%)\n",
           (flt_duration - fix_duration),
           ((fix_duration * 100.0) / flt_duration));
    printf("           Error: %f%%\n",
           ((fix16_to_dbl(fix_error) * 100.0) / (args * pass)));

    return EXIT_SUCCESS;
}
