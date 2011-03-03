#include "fix16.h"
#include "int64.h"



#ifndef FIXMATH_NO_CACHE
static fix16_t _fix16_exp_cache_index[4096]  = { 0 };
static fix16_t _fix16_exp_cache_value[4096]  = { 0 };
#endif



fix16_t fix16_exp(fix16_t inValue) {
	if(inValue == 0)
		return fix16_one;
	if(inValue == fix16_one)
		return fix16_e;
	if(inValue > 681391)
		return fix16_max;
	if(inValue < -726817)
		return 0;

	#ifndef FIXMATH_NO_CACHE
	fix16_t tempIndex = (inValue ^ (inValue >> 16));
	tempIndex = (inValue ^ (inValue >> 4)) & 0x0FFF;
	if(_fix16_exp_cache_index[tempIndex] == inValue)
		return _fix16_exp_cache_value[tempIndex];
	#endif

	int64_t tempOut = int64_add(int64_from_int32(fix16_one), int64_from_int32(inValue));
	int64_t tempValue = int64_from_int32(inValue);
	uint32_t i, n;
	for(i = 3, n = 2; i < 13; n *= i, i++) {
		tempValue = int64_mul_i64_i32(tempValue, inValue);
		#ifndef FIXMATH_NO_ROUNDING
		tempValue = int64_add(tempValue, int64_from_int32(fix16_one >> 1));
		#endif
		tempValue = int64_shift(tempValue, -16);
		tempOut = int64_add(tempOut, int64_div_i64_i32(tempValue, n));
	}

	#ifndef FIXMATH_NO_CACHE
	_fix16_exp_cache_index[tempIndex] = inValue;
	_fix16_exp_cache_value[tempIndex] = int64_lo(tempOut);
	#endif

	return int64_lo(tempOut);
}
