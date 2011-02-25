#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>
#include <libfixmath/fixmath.h>

int main(int argc, char** argv) {
	FILE* fp = fopen("fix16_trig_sin_lut.h", "wb");
	if(fp == NULL) {
		fprintf(stderr, "Error: Unable to open file for writing.\n");
		return EXIT_FAILURE;
	}

	// TODO - Store as uint16_t with a count to determine the end and return 1.

	fprintf(fp, "#ifndef __fix16_trig_sin_lut_h__\n");
	fprintf(fp, "#define __fix16_trig_sin_lut_h__\n");
	fprintf(fp, "\n");

	fix16_t fix16_sin_lut_count = (fix16_pi >> 1);
	fix16_t fix16_sin_lut[fix16_sin_lut_count];

	uintptr_t i;
	for(i = 0; i < fix16_sin_lut_count; i++)
		fix16_sin_lut[i] = fix16_from_dbl(sin(fix16_to_dbl(i)));
	for(i--; fix16_sin_lut[i] == fix16_one; i--, fix16_sin_lut_count--);

	fprintf(fp, "static const uint32_t _fix16_sin_lut_count = %"PRIi32";\n", fix16_sin_lut_count);
	fprintf(fp, "static uint16_t _fix16_sin_lut[%"PRIi32"] = {", fix16_sin_lut_count);

	for(i = 0; i < fix16_sin_lut_count; i++) {
		if((i & 7) == 0)
			fprintf(fp, "\n\t");
		fprintf(fp, "%"PRIi32", ", fix16_sin_lut[i]);
	}
	fprintf(fp, "\n\t};\n");

	fprintf(fp, "\n");
	fprintf(fp, "#endif\n");

	fclose(fp);

    return EXIT_SUCCESS;
}
