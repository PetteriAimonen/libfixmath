#include "fract32.h"



fract32_t fract32_create(uint32_t inNumerator, uint32_t inDenominator) {
	if(inDenominator <= inNumerator)
		return 0xFFFFFFFF;
	#ifndef FIXMATH_NO_64BIT
	return (fract32_t)(((uint64_t)inNumerator << 32) / inDenominator);
	#else
	fract32_t result = 0;
	unsigned i;
	for (i = 0; i < 32; i++) {
		result <<= 1;
		/* Compare before doubling so the remainder cannot overflow. */
		if (inNumerator >= inDenominator - inNumerator) {
			inNumerator -= inDenominator - inNumerator;
			result |= 1;
		} else {
			inNumerator <<= 1;
		}
	}
	return result;
	#endif
}

fract32_t fract32_invert(fract32_t inFract) {
	return (0xFFFFFFFF - inFract);
}

#ifndef FIXMATH_NO_64BIT
uint32_t fract32_usmul(uint32_t inVal, fract32_t inFract) {
	return (uint32_t)(((uint64_t)inVal * (uint64_t)inFract) >> 32);
}

int32_t fract32_smul(int32_t inVal, fract32_t inFract) {
	if(inVal < 0)
        return -(int32_t)fract32_usmul(-inVal, inFract);
	return fract32_usmul(inVal, inFract);
}
#endif
