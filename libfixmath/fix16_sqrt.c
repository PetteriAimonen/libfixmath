#include "fix16.h"



#ifndef FIXMATH_NO_CACHE
fix16_t _fix16_sqrt_cache_index[4096] = { 0 };
fix16_t _fix16_sqrt_cache_value[4096] = { 0 };
#endif



fix16_t fix16_sqrt(fix16_t inValue) {
	#ifndef FIXMATH_NO_CACHE
	fix16_t tempIndex = (((inValue >> 16) ^ (inValue >> 4)) & 0x00000FFF);
	if(_fix16_sqrt_cache_index[tempIndex] == inValue)
		return _fix16_sqrt_cache_value[tempIndex];
	#endif

	int64_t tempOp = inValue; tempOp <<= 16;
	int64_t tempOut = 0;
	int64_t tempOne = 0x4000000000000000ULL;

	while(tempOne > tempOp)
		tempOne >>= 2;

	while(tempOne != 0) {
		if (tempOp >= tempOut + tempOne) {
			tempOp -= tempOut + tempOne;
			tempOut += tempOne << 1;
		}
		tempOut >>= 1;
		tempOne >>= 2;
	}

	#ifndef FIXMATH_NO_CACHE
	_fix16_sqrt_cache_index[tempIndex] = inValue;
	_fix16_sqrt_cache_value[tempIndex] = tempOut;
	#endif

	return tempOut;
}
