#include "fix16.h"



fix16_t _fix16_sin_cache_index[4096] = { 0 };
fix16_t _fix16_sin_cache_value[4096] = { 0 };
fix16_t _fix16_atan_cache_index[4096] = { 0 };
fix16_t _fix16_atan_cache_value[4096] = { 0 };



fix16_t fix16_sin(fix16_t inAngle) {
	fix16_t tempAngle = inAngle % (fix16_pi << 1);
	if(tempAngle > fix16_pi)
		tempAngle -= (fix16_pi << 1);
	else if(tempAngle < -fix16_pi)
		tempAngle += (fix16_pi << 1);

	fix16_t tempIndex = ((inAngle >> 5) & 0x00000FFF);
	if(_fix16_sin_cache_index[tempIndex] == inAngle)
		return _fix16_sin_cache_value[tempIndex];

	fix16_t tempAngleSq = fix16_mul(tempAngle, tempAngle);

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

	_fix16_sin_cache_index[tempIndex] = inAngle;
	_fix16_sin_cache_value[tempIndex] = tempOut;

	return tempOut;
}

fix16_t fix16_cos(fix16_t inAngle) {
	return fix16_sin(inAngle + (fix16_pi >> 1));
}

fix16_t fix16_tan(fix16_t inAngle) {
	return fix16_div(fix16_sin(inAngle), fix16_cos(inAngle));
}

fix16_t fix16_asin(fix16_t inValue) {
	if((inValue > 1) || (inValue < -1))
		return 0;
	fix16_t tempOut;
	tempOut = (1 - fix16_mul(inValue, inValue));
	tempOut = (inValue / fix16_sqrt(tempOut));
	tempOut = fix16_atan(tempOut);
	return tempOut;
}

fix16_t fix16_acos(fix16_t inValue) {
	return ((fix16_pi >> 1) - fix16_asin(inValue));
}

fix16_t _fix16_atan(fix16_t inValue) {
	fix16_t tempOut;
	if(inValue > 29736) {
		tempOut = (1 + fix16_mul(inValue, inValue));
		tempOut = (1 + fix16_sqrt(tempOut));
		tempOut = (inValue / tempOut);
		tempOut = _fix16_atan(tempOut);
		return (tempOut << 1);
	}

	fix16_t tempValue = inValue;
	fix16_t tempValSq = fix16_mul(inValue, inValue);
	tempOut = inValue;
	tempValue = fix16_mul(tempValue, tempValSq);
	tempOut += (tempValue / 3);
	tempValue = fix16_mul(tempValue, tempValSq);
	tempOut += (tempValue / 5);
	tempValue = fix16_mul(tempValue, tempValSq);
	tempOut += (tempValue / 7);
	tempValue = fix16_mul(tempValue, tempValSq);
	tempOut += (tempValue / 9);
	tempValue = fix16_mul(tempValue, tempValSq);
	tempOut += (tempValue / 11);

	return tempOut;
}

fix16_t fix16_atan(fix16_t inValue) {
	fix16_t tempIndex = (((inValue >> 16) ^ (inValue >> 4)) & 0x00000FFF);
	if(_fix16_atan_cache_index[tempIndex] == inValue)
		return _fix16_atan_cache_value[tempIndex];
	fix16_t tempOut = _fix16_atan(inValue);
	_fix16_atan_cache_index[tempIndex] = inValue;
	_fix16_atan_cache_value[tempIndex] = tempOut;
	return tempOut;
}

fix16_t fix16_atan2(fix16_t inY, fix16_t inX) {
	if(inX == 0) {
		if(inY == 0)
			return 0;
		if(inY > 0)
			return (fix16_pi >> 1);
		return -(fix16_pi >> 1);
	}
	if(inY > 0)
		return fix16_atan(fix16_div(inY, inX));
	if(inY >= 0)
		return (fix16_pi + fix16_atan(fix16_div(inY, inX)));
	return (-fix16_pi + fix16_atan(fix16_div(inY, inX)));
}
