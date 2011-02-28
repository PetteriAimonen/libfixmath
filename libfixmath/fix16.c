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
	#ifndef FIXMATH_NO_64BIT
	int64_t tempResult = ((int64_t)inArg0 * (int64_t)inArg1);
	#ifndef FIXMATH_NO_ROUNDING
	tempResult += (fix16_one >> 1);
	#endif
	tempResult >>= 16;
	return tempResult;
	#else
	 int16_t hi[2] = { (inArg0 >> 16),    (inArg1 >> 16)    };
	uint16_t lo[2] = { (inArg0 & 0xFFFF), (inArg1 & 0xFFFF) };

	 int32_t r_hi = hi[0] * hi[1];
	 int32_t r_md = (hi[0] * lo[1]) + (hi[1] * lo[0]);
	uint32_t r_lo = lo[0] * lo[1];
	#ifndef FIXMATH_NO_ROUNDING
	r_lo += 0xFFFF;
	#endif

	r_md += (r_hi & 0xFFFF) << 16;
	r_md += (r_lo >> 16);

	return r_md;
	#endif
}

fix16_t fix16_smul(fix16_t inArg0, fix16_t inArg1) {
	#ifndef FIXMATH_NO_64BIT
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
	#else
	 int16_t hi[2] = { (inArg0 >> 16),    (inArg1 >> 16)    };
	 int32_t r_hi = hi[0] * hi[1];
	 if(r_hi >> 16)
		return (r_hi < 0 ? fix16_MIN : fix16_MAX);

	uint16_t lo[2] = { (inArg0 & 0xFFFF), (inArg1 & 0xFFFF) };
	 int32_t r_md = (hi[0] * lo[1]) + (hi[1] * lo[0]);
	uint32_t r_lo = lo[0] * lo[1];
	#ifndef FIXMATH_NO_ROUNDING
	r_lo += 0xFFFF;
	#endif

	r_md += (r_hi & 0xFFFF) << 16;
	r_md += (r_lo >> 16);

	return r_md;
	#endif
}



fix16_t fix16_div(fix16_t inArg0, fix16_t inArg1) {
	#ifndef FIXMATH_NO_64BIT
	int64_t tempResult = inArg0;
	tempResult <<= 16;
	#ifndef FIXMATH_NO_ROUNDING
	tempResult += (inArg1 >> 1);
	#endif
	tempResult /= inArg1;
	return tempResult;
	#else
	 int32_t rcp = (0xFFFFFFFF / inArg1);
	 int32_t rcp_hi = rcp >> 16;

	uint32_t rcp_lo = rcp & 0xFFFF;
	 int32_t arg_hi = (inArg0 >> 16);
	uint32_t arg_lo = (inArg0 & 0xFFFF);

	 int32_t res_hi = rcp_hi * arg_hi;
	 int32_t res_md = (rcp_hi * arg_lo) + (rcp_lo * arg_hi);
	uint32_t res_lo = rcp_lo * arg_lo;

	int32_t res = (res_hi << 16) + res_md + (res_lo >> 16);
	#ifndef FIXMATH_NO_ROUNDING
	res += ((res_lo >> 15) & 1);
	#endif
	return res;

	/*int32_t res = (inArg0 / inArg1) << 16;
	int32_t mod = inArg0 % inArg1;
	uintptr_t i;
	for(i = 0; i < 16; i++) {
		mod <<= 1;
		res += (mod / inArg1) << (15 - i);
		mod %= inArg1;
	}
	#ifndef FIXMATH_NO_ROUNDING
	if((mod << 1) / inArg1)
		res++;
	#endif
	return res;*/
	#endif
}

fix16_t fix16_sdiv(fix16_t inArg0, fix16_t inArg1) {
	if(inArg1 == 0) {
		if(inArg0 < 0)
			return fix16_MIN;
		return fix16_MAX;
	}
	#ifndef FIXMATH_NO_64BIT
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
	#else
	 int32_t rcp = (0xFFFFFFFF / inArg1);
	 int32_t rcp_hi = rcp >> 16;
	if(rcp_hi >= 32768)
		return fix16_MAX;
	if(rcp_hi < -32768)
		return fix16_MIN;

	uint32_t rcp_lo = rcp & 0xFFFF;
	 int32_t arg_hi = (inArg0 >> 16);
	uint32_t arg_lo = (inArg0 & 0xFFFF);

	 int32_t res_hi = rcp_hi * arg_hi;
	 int32_t res_md = (rcp_hi * arg_lo) + (rcp_lo * arg_hi);
	uint32_t res_lo = rcp_lo * arg_lo;

	int32_t res = (res_hi << 16) + res_md + (res_lo >> 16);
	#ifndef FIXMATH_NO_ROUNDING
	res += ((res_lo >> 15) & 1);
	#endif
	return res;

	/*int32_t res = (inArg0 / inArg1);
	if((res < -32768) || (res >= 32768))
		return (res < 0 ? fix16_MIN : fix16_MAX);
	res <<= 16;
	int32_t mod = inArg0 % inArg1;
	uintptr_t i;
	for(i = 0; i < 16; i++) {
		mod <<= 1;
		res += (mod / inArg1) << (15 - i);
		mod %= inArg1;
	}
	#ifndef FIXMATH_NO_ROUNDING
	if((mod << 1) / inArg1)
		res++;
	#endif
	return res;*/
	#endif
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
