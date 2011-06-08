#include <limits.h>
#include "fix16.h"

#if defined(FIXMATH_SIN_LUT)
#include "fix16_trig_sin_lut.h"
#elif !defined(FIXMATH_NO_CACHE)
static fix16_t _fix16_sin_cache_index[4096]  = { 0 };
static fix16_t _fix16_sin_cache_value[4096]  = { 0 };
#endif

#ifndef FIXMATH_NO_CACHE
static fix16_t _fix16_atan_cache_index[2][4096] = { { 0 }, { 0 } };
static fix16_t _fix16_atan_cache_value[4096] = { 0 };
#endif


fix16_t fix16_sin_parabola(fix16_t inAngle)
{
	fix16_t abs_inAngle, abs_retval, retval;
	fix16_t mask;

	/* Absolute function */
	mask = (inAngle >> (sizeof(fix16_t)*CHAR_BIT-1));
	abs_inAngle = (inAngle + mask) ^ mask;
	
	/* On 0->PI, sin looks like x² that is :
	   - centered on PI/2,
	   - equals 1 on PI/2,
	   - equals 0 on 0 and PI
	  that means :  4/PI * x  - 4/PI² * x²
	  Use abs(x) to handle (-PI) -> 0 zone.
	 */
	retval = fix16_mul(FOUR_DIV_PI, inAngle) + fix16_mul( fix16_mul(_FOUR_DIV_PI2, inAngle), abs_inAngle );
	/* At this point, retval equals sin(inAngle) on important points ( -PI, -PI/2, 0, PI/2, PI),
	   but is not very precise between these points
	 */
	#ifndef FIXMATH_FAST_SIN
	/* Absolute value of retval */
	mask = (retval >> (sizeof(fix16_t)*CHAR_BIT-1));
	abs_retval = (retval + mask) ^ mask;
	/* So improve its precision by adding some x^4 component to retval */
	retval += fix16_mul(X4_CORRECTION_COMPONENT, fix16_mul(retval, abs_retval) - retval );
	#endif
	return retval;
}

fix16_t fix16_sin(fix16_t inAngle) {
	fix16_t tempAngle = inAngle % (fix16_pi << 1);

	#ifdef FIXMATH_SIN_LUT
	if(tempAngle < 0)
		tempAngle += (fix16_pi << 1);

	fix16_t tempOut;
	if(tempAngle >= fix16_pi) {
		tempAngle -= fix16_pi;
		if(tempAngle >= (fix16_pi >> 1))
			tempAngle = fix16_pi - tempAngle;
		tempOut = -(tempAngle >= _fix16_sin_lut_count ? fix16_one : _fix16_sin_lut[tempAngle]);
	} else {
		if(tempAngle >= (fix16_pi >> 1))
			tempAngle = fix16_pi - tempAngle;
		tempOut = (tempAngle >= _fix16_sin_lut_count ? fix16_one : _fix16_sin_lut[tempAngle]);
	}
	#else
	if(tempAngle > fix16_pi)
		tempAngle -= (fix16_pi << 1);
	else if(tempAngle < -fix16_pi)
		tempAngle += (fix16_pi << 1);

	#ifndef FIXMATH_NO_CACHE
	fix16_t tempIndex = ((inAngle >> 5) & 0x00000FFF);
	if(_fix16_sin_cache_index[tempIndex] == inAngle)
		return _fix16_sin_cache_value[tempIndex];
	#endif

	fix16_t tempAngleSq = fix16_mul(tempAngle, tempAngle);

	#ifndef FIXMATH_FAST_SIN // Most accurate version, accurate to ~2.1%
	fix16_t tempOut = tempAngle;
	tempAngle = fix16_mul(tempAngle, tempAngleSq);
	tempOut -= (tempAngle / 6);
	tempAngle = fix16_mul(tempAngle, tempAngleSq);
	tempOut += (tempAngle / 120);
	tempAngle = fix16_mul(tempAngle, tempAngleSq);
	tempOut -= (tempAngle / 5040);
	tempAngle = fix16_mul(tempAngle, tempAngleSq);
	tempOut += (tempAngle / 362880);
	tempAngle = fix16_mul(tempAngle, tempAngleSq);
	tempOut -= (tempAngle / 39916800);
	#else // Fast implementation, runs at 159% the speed of above 'accurate' version with an slightly lower accuracy of ~2.3%
	fix16_t tempOut;
	tempOut = fix16_mul(-13, tempAngleSq) + 546;
	tempOut = fix16_mul(tempOut, tempAngleSq) - 10923;
	tempOut = fix16_mul(tempOut, tempAngleSq) + 65536;
	tempOut = fix16_mul(tempOut, tempAngle);
	#endif

	#ifndef FIXMATH_NO_CACHE
	_fix16_sin_cache_index[tempIndex] = inAngle;
	_fix16_sin_cache_value[tempIndex] = tempOut;
	#endif
	#endif

	return tempOut;
}

fix16_t fix16_cos(fix16_t inAngle) {
	return fix16_sin(inAngle + (fix16_pi >> 1));
}

fix16_t fix16_tan(fix16_t inAngle) {
	return fix16_sdiv(fix16_sin(inAngle), fix16_cos(inAngle));
}

fix16_t fix16_asin(fix16_t inValue) {
	if((inValue > fix16_one) || (inValue < -fix16_one))
		return 0;
	fix16_t tempOut;
	tempOut = (fix16_one - fix16_mul(inValue, inValue));
	tempOut = fix16_div(inValue, fix16_sqrt(tempOut));
	tempOut = fix16_atan(tempOut);
	return tempOut;
}

fix16_t fix16_acos(fix16_t inValue) {
	return ((fix16_pi >> 1) - fix16_asin(inValue));
}

fix16_t fix16_atan2(fix16_t inY , fix16_t inX) {
	#ifndef FIXMATH_NO_CACHE
	uintptr_t hash = (inX ^ inY);
	hash ^= hash >> 20;
	hash &= 0x0FFF;
	if((_fix16_atan_cache_index[0][hash] == inX) && (_fix16_atan_cache_index[1][hash] == inY))
		return _fix16_atan_cache_value[hash];
	#endif

	fix16_t absy = (inY < 0 ? -inY : inY);

	#ifndef FIXMATH_NO_64BIT
	int64_t i = inX + (inX >= 0 ? -absy : absy);
	int64_t j = (inX >= 0 ? inX : -inX) + absy;
	if(j == 0)
		return (inY < 0 ? (-fix16_pi >> 1) : (fix16_pi >> 1));

	int64_t is, js;
	int64_t angle;
	angle  = (4216574283LL * -i) / j;
	is = (i * i);
	js = (j * j);
	#ifndef FIXMATH_NO_ROUNDING
	is += (fix16_one >> 1);
	js += (fix16_one >> 1);
	#endif
	is >>= 16;
	js >>= 16;
	if((is | js) >> 32) {
		if((is | js) >> 40) {
			is >>= 16;
			js >>= 16;
		} else {
			is >>= 8;
			js >>= 8;
		}
	}
	is = (is * i);
	js = (js * j);
	#ifndef FIXMATH_NO_ROUNDING
	is += (fix16_one >> 1);
	js += (fix16_one >> 1);
	#endif
	is >>= 16;
	js >>= 16;
	is = is * 51472LL;
	angle += (is / js) << 14;
	angle += (inX >= 0 ? 3373259426LL : 10119778278LL);
	#ifndef FIXMATH_NO_ROUNDING
	angle += (fix16_one >> 1);
	#endif
	angle >>= 16;
	#else
    fix16_t angle;
    if(inX >= 0) {
        fix16_t r = fix16_sdiv(fix16_sadd(inX, -absy),
                fix16_sadd(inX, absy));
        angle = fix16_sadd(fix16_sadd(
                    fix16_mul(12864, fix16_mul(r, fix16_mul(r, r))),
                    fix16_mul(-64336, r)),
                51471); // pi/4
    } else {
        fix16_t r = fix16_sdiv(fix16_sadd(inX, absy),
                fix16_sadd(absy, -inX));
        angle = fix16_sadd(fix16_sadd(
                    fix16_mul(12864, fix16_mul(r, fix16_mul(r, r))),
                    fix16_mul(-64336, r)),
                154415); // 3pi/4
    }
	#endif
	angle = (inY < 0 ? -angle : angle);

	#ifndef FIXMATH_NO_CACHE
	_fix16_atan_cache_index[0][hash] = inX;
	_fix16_atan_cache_index[1][hash] = inY;
	_fix16_atan_cache_value[hash] = angle;
	#endif

	return angle;
}

fix16_t fix16_atan(fix16_t inValue) {
	return fix16_atan2(inValue, fix16_one);
}
