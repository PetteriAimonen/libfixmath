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

	fprintf(fp, "#ifndef __fix16_trig_sin_lut_h__\n");
	fprintf(fp, "#define __fix16_trig_sin_lut_h__\n");
	fprintf(fp, "\n");

	fprintf(fp, "static fix16_t _fix16_sin_lut[%"PRIi32"] = {", (fix16_pi >> 1));

	uintptr_t i;
	for(i = 0; i < (fix16_pi >> 1); i++) {
		if((i & 7) == 0)
			fprintf(fp, "\n\t");
		fix16_t fix16_sin_lut = fix16_from_dbl(sin(fix16_to_dbl(i)));
		fprintf(fp, "%"PRIi32", ", fix16_sin_lut);
	}
	fprintf(fp, "\n\t};\n");

	fprintf(fp, "\n");
	fprintf(fp, "#endif\n");

	fclose(fp);

    return EXIT_SUCCESS;
}
