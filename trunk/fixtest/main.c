#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <inttypes.h>

#include <libfixmath/fixmath.h>

#include "hiclock.h"


int main(int argc, char** argv) {
    printf("libfixmath test tool\n");

    hiclock_init();

	uintptr_t iter = (1 << 16);
	uintptr_t pass = (1 <<  8);

	uintptr_t i;
	srand(time(NULL));

	fix16_t fix_args[iter];
	for(i = 0; i < iter; i++)
		fix_args[i] = (rand() ^ (rand() << 16));
	fix16_t fix_result[iter];
	hiclock_t fix_start = hiclock();
	for(i = 0; i < pass; i++) {
		uintptr_t j;
		for(j = 0; j < iter; j++)
			fix_result[j] = fix16_atan(fix_args[j]);
	}
	hiclock_t fix_end = hiclock();

	float   flt_args[iter];
	for(i = 0; i < iter; i++)
		flt_args[i] = fix16_to_float(fix_args[i]);
	float   flt_result[iter];
	hiclock_t flt_start = hiclock();
	for(i = 0; i < pass; i++) {
		uintptr_t j;
		for(j = 0; j < iter; j++)
			flt_result[j] = atanf(flt_args[j]);
	}
	hiclock_t flt_end = hiclock();

	fix16_t fix_error = 0;
	for(i = 0; i < iter; i++)
		fix_error += abs(fix16_from_float(flt_result[i]) - fix_result[i]);

	hiclock_t flt_duration = (flt_end - flt_start);
	hiclock_t fix_duration = (fix_end - fix_start);

	printf("Floating Point: %08"PRIuHICLOCK" @ %"PRIu32"Hz\n", flt_duration, HICLOCKS_PER_SEC);
	printf("Fixed Point:    %08"PRIuHICLOCK" @ %"PRIu32"Hz\n", fix_duration, HICLOCKS_PER_SEC);
	printf("Difference:     %08"PRIiHICLOCK" (% 3.2f%%)\n", (flt_duration - fix_duration), ((fix_duration * 100.0) / flt_duration));
	printf("Error:          % 3.2f%%\n", ((double)fix_error / iter));

    return EXIT_SUCCESS;
}
