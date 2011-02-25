#include "fix16.h"


/* Replaced as macros, these are left here to uncomment for code dependant on the symbols.
const fix16_t fix16_pi  = 205887;
const fix16_t fix16_e   = 178145;
const fix16_t fix16_one = 0x00010000;

double  fix16_to_dbl(const fix16_t inVal)   { return ((double)inVal / 65536.0); }
fix16_t fix16_from_dbl(const double inVal)  { return (fix16_t)(inVal * 65536.0); }
float   fix16_to_float(const fix16_t inVal) { return ((float)inVal / 65536.0f); }
fix16_t fix16_from_float(const float inVal) { return (fix16_t)(inVal * 65536.0f); }
int32_t fix16_to_int(const fix16_t inVal)   { return ((inVal + 0x00008000) >> 16); }
fix16_t fix16_from_int(const int32_t inVal) { return (inVal << 16); }
*/



fix16_t fix16_sadd(fix16_t inArg0, fix16_t inArg1) {
	fix16_t tempResult = (inArg0 + inArg1);
	if((tempResult > 0) && (inArg0 < 0) && (inArg1 < 0))
		return 0x80000000;
	if((tempResult < 0) && (inArg0 > 0) && (inArg1 > 0))
		return 0x7FFFFFFF;
	return tempResult;
}



fix16_t fix16_mul(fix16_t inArg0, fix16_t inArg1) {
	int64_t tempResult = ((int64_t)inArg0 * (int64_t)inArg1);
	#ifndef FIXMATH_NO_ROUNDING
	tempResult += (fix16_one >> 1);
	#endif
	tempResult >>= 16;
	return tempResult;
}

fix16_t fix16_smul(fix16_t inArg0, fix16_t inArg1) {
	int64_t tempResult = ((int64_t)inArg0 * (int64_t)inArg1);
	#ifndef FIXMATH_NO_ROUNDING
	tempResult += (fix16_one >> 1);
	#endif
	tempResult >>= 16;
	if(tempResult < fix16_MIN)
		return fix16_MIN;
	if(tempResult > fix16_MAX)
		return fix16_MAX;
	return tempResult;
}



fix16_t fix16_div(fix16_t inArg0, fix16_t inArg1) {
	int64_t tempResult = inArg0;
	tempResult <<= 16;
	#ifndef FIXMATH_NO_ROUNDING
	tempResult += (inArg1 >> 1);
	#endif
	tempResult /= inArg1;
	return tempResult;
}

fix16_t fix16_sdiv(fix16_t inArg0, fix16_t inArg1) {
	if(inArg1 == 0) {
		if(inArg0 < 0)
			return fix16_MIN;
		return fix16_MAX;
	}
	int64_t tempResult = inArg0;
	tempResult <<= 16;
	#ifndef FIXMATH_NO_ROUNDING
	tempResult += (inArg1 >> 1);
	#endif
	tempResult /= inArg1;
	if(tempResult < fix16_MIN)
		return fix16_MIN;
	if(tempResult > fix16_MAX)
		return fix16_MAX;
	return tempResult;
}



fix16_t fix16_lerp8(fix16_t inArg0, fix16_t inArg1, uint8_t inFract) {
	int64_t tempOut;
	tempOut   = ((int64_t)inArg0 * (256 - inFract));
	tempOut  += ((int64_t)inArg1 * inFract);
	tempOut >>= 8;
	return (fix16_t)tempOut;
}

fix16_t fix16_lerp16(fix16_t inArg0, fix16_t inArg1, uint16_t inFract) {
	int64_t tempOut;
	tempOut   = ((int64_t)inArg0 * (fix16_one - inFract));
	tempOut  += ((int64_t)inArg1 * inFract);
	tempOut >>= 16;
	return (fix16_t)tempOut;
}

fix16_t fix16_lerp32(fix16_t inArg0, fix16_t inArg1, uint32_t inFract) {
	int64_t tempOut;
	tempOut   = ((int64_t)inArg0 * (0 - inFract));
	tempOut  += ((int64_t)inArg1 * inFract);
	tempOut >>= 32;
	return (fix16_t)tempOut;
}
