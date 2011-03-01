#include "fix16.h"



fix16_t fix16_sadd(fix16_t inArg0, fix16_t inArg1) {
	fix16_t tempResult = (inArg0 + inArg1);
	if((tempResult > 0) && (inArg0 < 0) && (inArg1 < 0))
		return fix16_min;
	if((tempResult < 0) && (inArg0 > 0) && (inArg1 > 0))
		return fix16_max;
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
	if(tempResult < fix16_min)
		return fix16_min;
	if(tempResult > fix16_max)
		return fix16_max;
	return tempResult;
	#else
	 int16_t hi[2] = { (inArg0 >> 16),    (inArg1 >> 16)    };
	 int32_t r_hi = hi[0] * hi[1];
	 if(r_hi >> 16)
		return (r_hi < 0 ? fix16_min : fix16_max);

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
	int neg = ((inArg0 < 0) != (inArg1 < 0));
	inArg0 = (inArg0 < 0 ? -inArg0 : inArg0);
	inArg1 = (inArg1 < 0 ? -inArg1 : inArg1);

	while(((inArg0 | inArg1) & 1) == 0) {
		inArg0 >>= 1;
		inArg1 >>= 1;
	}

	uint32_t r_hi = (inArg0 / inArg1);

	uint32_t n_lo = (inArg0 % inArg1);
	uint32_t n_hi = (n_lo >> 16);
	n_lo <<= 16;

	uint32_t i, arg;
	for(i = 1, arg = inArg1; ((n_lo | arg) & 1) == 0; i <<= 1) {
		n_lo = ((n_lo >> 1) | (n_hi << 31));
		n_hi =  (n_hi >> 1);
		arg >>= 1;
	}

	uint32_t res = 0;
	if(n_hi) {
		uint32_t arg_lo, arg_hi;
		for(arg_lo = inArg1; (arg_lo >> 31) == 0; arg_lo <<= 1, i <<= 1);
		for(arg_hi = (arg_lo >> 31), arg_lo <<= 1, i <<= 1; arg_hi < n_hi; arg_hi = (arg_hi << 1) | (arg_lo >> 31), arg_lo <<= 1, i <<= 1);

		do {
			arg_lo = (arg_lo >> 1) | (arg_hi << 31);
			arg_hi = (arg_hi >> 1);
			i >>= 1;
			if(arg_hi < n_hi) {
				n_hi -= arg_hi;
				if(arg_lo > n_lo)
					n_hi--;
				n_lo -= arg_lo;
				res += i;
			} else if((arg_hi == n_hi) && (arg_lo <= n_lo)) {
				n_hi -= arg_hi;
				n_lo -= arg_lo;
				res += i;
			}
		} while(n_hi);
	}

	res += (n_lo / inArg1);
	#ifndef FIXMATH_NO_ROUNDING
	if((n_lo % inArg1) >= (inArg1 >> 1))
		res++;
	#endif
	res += (r_hi << 16);

	return (neg ? -res : res);
	#endif
}

fix16_t fix16_sdiv(fix16_t inArg0, fix16_t inArg1) {
	if(inArg1 == 0) {
		if(inArg0 < 0)
			return fix16_min;
		return fix16_max;
	}
	#ifndef FIXMATH_NO_64BIT
	int64_t tempResult = inArg0;
	tempResult <<= 16;
	#ifndef FIXMATH_NO_ROUNDING
	tempResult += (inArg1 >> 1);
	#endif
	tempResult /= inArg1;
	if(tempResult < fix16_min)
		return fix16_min;
	if(tempResult > fix16_max)
		return fix16_max;
	return tempResult;
	#else
	int neg = ((inArg0 < 0) != (inArg1 < 0));
	inArg0 = (inArg0 < 0 ? -inArg0 : inArg0);
	inArg1 = (inArg1 < 0 ? -inArg1 : inArg1);

	while(((inArg0 | inArg1) & 1) == 0) {
		inArg0 >>= 1;
		inArg1 >>= 1;
	}

	uint32_t r_hi = (inArg0 / inArg1);
	if(r_hi > (neg ? 32768 : 32767))
		return (neg ? fix16_min : fix16_max);

	uint32_t n_lo = (inArg0 % inArg1);
	uint32_t n_hi = (n_lo >> 16);
	n_lo <<= 16;

	uint32_t i, arg;
	for(i = 1, arg = inArg1; ((n_lo | arg) & 1) == 0; i <<= 1) {
		n_lo = ((n_lo >> 1) | (n_hi << 31));
		n_hi =  (n_hi >> 1);
		arg >>= 1;
	}

	uint32_t res = 0;
	if(n_hi) {
		uint32_t arg_lo, arg_hi;
		for(arg_lo = inArg1; (arg_lo >> 31) == 0; arg_lo <<= 1, i <<= 1);
		for(arg_hi = (arg_lo >> 31), arg_lo <<= 1, i <<= 1; arg_hi < n_hi; arg_hi = (arg_hi << 1) | (arg_lo >> 31), arg_lo <<= 1, i <<= 1);

		do {
			arg_lo = (arg_lo >> 1) | (arg_hi << 31);
			arg_hi = (arg_hi >> 1);
			i >>= 1;
			if(arg_hi < n_hi) {
				n_hi -= arg_hi;
				if(arg_lo > n_lo)
					n_hi--;
				n_lo -= arg_lo;
				res += i;
			} else if((arg_hi == n_hi) && (arg_lo <= n_lo)) {
				n_hi -= arg_hi;
				n_lo -= arg_lo;
				res += i;
			}
		} while(n_hi);
	}

	res += (n_lo / inArg1);
	#ifndef FIXMATH_NO_ROUNDING
	if((n_lo % inArg1) >= (inArg1 >> 1))
		res++;
	#endif
	res += (r_hi << 16);

	return (neg ? -res : res);
	#endif
}



#ifndef FIXMATH_NO_64BIT
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
#endif
