#include "fix16.h"
#include "int64.h"


#ifndef FIXMATH_NO_CACHE
fix16_t _fix16_sqrt_cache_index[4096] = { 0 };
fix16_t _fix16_sqrt_cache_value[4096] = { 0 };
#endif

fix16_t fix16_sqrt32(fix16_t inValue)
{
	fix16_t retval = 0;
	fix16_t x = inValue;

	/* Take only  Leading 1 bit */
	x |= (x >> 1);
	x |= (x >> 2);
	x |= (x >> 4);
	x |= (x >> 8);
	x |= (x >> 16);
	x = x & ~(x >> 1);

	/* Avoid useless loops */
	if (x & 0xFF000000)
	{
		x = 0x00800000;
	}
	/* Condition for numbers less than 1.0 */
	if ( !(inValue>>16) ) x = 0x00008000;

	while(x)
	{
		retval |= x;
		if ( (uint32_t)fix16_mul(retval,retval) > (uint32_t)inValue)
		{
			retval &= ~x;
		}
		x >>= 1;
	}
	return retval;
}

fix16_t fix16_sqrt(fix16_t inValue) {
	int neg = (inValue < 0);
	if(neg)
		inValue = -inValue;

	#ifndef FIXMATH_NO_CACHE
	fix16_t tempIndex = (((inValue >> 16) ^ (inValue >> 4)) & 0x00000FFF);
	if(_fix16_sqrt_cache_index[tempIndex] == inValue)
		return (neg ? -_fix16_sqrt_cache_value[tempIndex] : _fix16_sqrt_cache_value[tempIndex]);
	#endif

	int64_t tempOp  = int64_const((inValue >> 16), (inValue << 16));
	int64_t tempOut = int64_const(0, 0);
	int64_t tempOne = int64_const(0x40000000UL, 0x00000000UL);

	while(int64_cmp_gt(tempOne, tempOp))
		tempOne = int64_shift(tempOne, -2);

	while(int64_cmp_ne(tempOne, int64_const(0, 0))) {
		if(int64_cmp_ge(tempOp, int64_add(tempOut, tempOne))) {
			tempOp  = int64_sub(tempOp, int64_add(tempOut, tempOne));
			tempOut = int64_add(tempOut, int64_shift(tempOne, 1));
		}
		tempOut = int64_shift(tempOut, -1);
		tempOne = int64_shift(tempOne, -2);
	}

	#ifndef FIXMATH_NO_CACHE
	_fix16_sqrt_cache_index[tempIndex] = inValue;
	_fix16_sqrt_cache_value[tempIndex] = int64_lo(tempOut);
	#endif

	return (neg ? -int64_lo(tempOut) : int64_lo(tempOut));
}
