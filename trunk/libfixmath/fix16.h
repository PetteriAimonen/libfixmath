#ifndef __libfixmath_fix16_h__
#define __libfixmath_fix16_h__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

typedef int32_t fix16_t;

#define fix16_MAX (fix16_t)0x7FFFFFFF /*!< the maximum value of fix16_t */
#define fix16_MIN (fix16_t)0x80000000 /*!< the minimum value of fix16_t */

#define fix16_pi  205887     /*!< fix16_t value of pi */
#define fix16_e   178145     /*!< fix16_t value of e */
#define fix16_one 0x00010000 /*!< fix16_t value of 1 */

/*! Coverts a fix16_t to a double and returns the result. */
#define fix16_to_dbl(inVal) ((double)((inVal) / 65536.0))
/*! Converts a double to a fix16_t and returns the result. */
#define fix16_from_dbl(inVal) ((fix16_t)((inVal) * 65536.0))
/*! Converts a fix16_t to a float and returns the result. */
#define fix16_to_float(inVal) ((float)((inVal) / 65536.0f))
/*! Converts a float to a fix16_t and returns the result. */
#define fix16_from_float(inVal) ((fix16_t)((inVal) * 65536.0f))
/*! Converts a fix16_t to a signed integer and returns the result. */
#define fix16_to_int(inVal) ((int32_t)(((inVal) + (fix16_one >> 1)) >> 16))
/*! Converts a signed integer to a fix16_t and returns the result. */
#define fix16_from_int(inVal) ((fix16_t)((inVal) << 16))

/* Replaced with macros, uncomment if symbols are needed by old code.
extern double  fix16_to_dbl(const fix16_t inVal);
extern fix16_t fix16_from_dbl(const double inVal);
extern float   fix16_to_float(const fix16_t inVal);
extern fix16_t fix16_from_float(const float inVal);
extern int32_t fix16_to_int(const fix16_t inVal);
extern fix16_t fix16_from_int(const int32_t inVal);
*/



/*! Performs a saturated addition (overflow-protected) of the two given fix16_t's and returns the result.
*/
extern fix16_t fix16_sadd(fix16_t inArg0, fix16_t inArg1);



/*! Multiplies the two given fix16_t's and returns the result.
*/
extern fix16_t fix16_mul(fix16_t inArg0, fix16_t inArg1);

/*! Performs a saturated multiplication (overflow-protected) of the two given fix16_t's and returns the result.
*/
extern fix16_t fix16_smul(fix16_t inArg0, fix16_t inArg1);



/*! Divides the first given fix16_t by the second and returns the result.
*/
extern fix16_t fix16_div(fix16_t inArg0, fix16_t inArg1);

/*! Performs a saturated division (overflow-protected) of the first fix16_t by the second and returns the result.
*/
extern fix16_t fix16_sdiv(fix16_t inArg0, fix16_t inArg1);



/*! Returns the linear interpolation: (inArg0 * (1 - inFract)) + (inArg1 * inFract)
*/
extern fix16_t fix16_lerp8(fix16_t inArg0, fix16_t inArg1, uint8_t inFract);
extern fix16_t fix16_lerp16(fix16_t inArg0, fix16_t inArg1, uint16_t inFract);
extern fix16_t fix16_lerp32(fix16_t inArg0, fix16_t inArg1, uint32_t inFract);



/*! Returns the sine of the given fix16_t.
*/
extern fix16_t fix16_sin(fix16_t inAngle);

/*! Returns the cosine of the given fix16_t.
*/
extern fix16_t fix16_cos(fix16_t inAngle);

/*! Returns the tangent of the given fix16_t.
*/
extern fix16_t fix16_tan(fix16_t inAngle);

/*! Returns the arcsine of the given fix16_t.
*/
extern fix16_t fix16_asin(fix16_t inValue);

/*! Returns the arccosine of the given fix16_t.
*/
extern fix16_t fix16_acos(fix16_t inValue);

/*! Returns the arctangent of the given fix16_t.
*/
extern fix16_t fix16_atan(fix16_t inValue);

/*! Returns the arctangent of inY/inX.
*/
extern fix16_t fix16_atan2(fix16_t inY, fix16_t inX);



/*! Returns the square root of the given fix16_t.
*/
extern fix16_t fix16_sqrt(fix16_t inValue);



/*! Returns the exponent (e^) of the given fix16_t.
*/
extern fix16_t fix16_exp(fix16_t inValue);

#ifdef __cplusplus
}
#endif

#endif
