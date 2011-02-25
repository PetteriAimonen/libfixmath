#include "fix16.h"



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
		return fix16_MAX;
	if(inValue < -726817)
		return 0;

	#ifndef FIXMATH_NO_CACHE
	fix16_t tempIndex = (inValue ^ (inValue >> 16));
	tempIndex = (inValue ^ (inValue >> 4)) & 0x0FFF;
	if(_fix16_exp_cache_index[tempIndex] == inValue)
		return _fix16_exp_cache_value[tempIndex];
	#endif

	int64_t tempOut = fix16_one;
	tempOut += inValue;
	int64_t tempValue = inValue;
	uint32_t i, n;
	for(i = 3, n = 2; i < 13; n *= i, i++) {
		tempValue *= inValue;
		#ifndef FIXMATH_NO_ROUNDING
		tempValue += (fix16_one >> 1);
		#endif
		tempValue >>= 16;
		tempOut += (tempValue / n);
	}

	#ifndef FIXMATH_NO_CACHE
	_fix16_exp_cache_index[tempIndex] = inValue;
	_fix16_exp_cache_value[tempIndex] = tempOut;
	#endif

	return tempOut;
}
