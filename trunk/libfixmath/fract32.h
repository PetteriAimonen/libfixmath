#ifndef __libfixmath_fract32_h__
#define __libfixmath_fract32_h__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

typedef uint32_t fract32_t;

/*! Creates a fraction using unsigned integers.
	\param inNumerator the unsigned integer numerator
	\param inDenominator the unsigned integer denominator
	\return a fraction using the given numerator and denominator
*/
extern fract32_t fract32_create(uint32_t inNumerator, uint32_t inDenominator);

/*! Inverts the given fraction, swapping the numerator and the denominator.
*/
extern fract32_t fract32_invert(fract32_t inFract);

/*! Performs unsigned saturated (overflow-protected) multiplication with the two given fractions and returns the result as an unsigned integer.
*/
extern uint32_t  fract32_usmul(uint32_t inVal, fract32_t inFract);

/*! Performs saturated (overflow-protected) multiplication with the two given fractions and returns the result as a signed integer.
*/
extern int32_t   fract32_smul(int32_t inVal, fract32_t inFract);

#ifdef __cplusplus
}
#endif

#endif
