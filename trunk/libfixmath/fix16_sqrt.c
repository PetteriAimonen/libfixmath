#include "fix16.h"

/* The square root algorithm is quite directly from
 * http://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Binary_numeral_system_.28base_2.29
 * An important difference is that it is split to two parts
 * in order to use only 32-bit operations.
 *
 * Note that for negative numbers we return -sqrt(-inValue).
 * Not sure if someone relies on this behaviour, but not going
 * to break it for now. It doesn't slow the code much overall.
 */
fix16_t fix16_sqrt(fix16_t inValue)
{
	uint8_t  neg = (inValue < 0);
	uint32_t num = (neg ? -inValue : inValue);
	uint32_t result = 0;
	uint32_t bit;
	uint8_t  n;
	
	// Many numbers will be less than 15, so
	// this gives a good balance between time spent
	// in if vs. time spent in the while loop
	// when searching for the starting value.
	if (num & 0xFFF00000)
		bit = (uint32_t)1 << 30;
	else
		bit = (uint32_t)1 << 18;
	
	while (bit > num) bit >>= 2;
	
	// The main part is executed twice, in order to avoid
	// using 64 bit values in computations.
	for (n = 0; n < 2; n++)
	{
		// First we get the top 24 bits of the answer.
		while (bit)
		{
			if (num >= result + bit)
			{
				num -= result + bit;
				result = (result >> 1) + bit;
			}
			else
			{
				result = (result >> 1);
			}
			bit >>= 2;
		}
		
		if (n == 0)
		{
			// Then process it again to get the lowest 8 bits.
			if (num > 65535)
			{
				// The remainder 'num' is too large to be shifted left
				// by 16, so we have to add 1 to result manually and
				// adjust 'num' accordingly.
				// num = a - (result + 0.5)^2
				//	 = num + result^2 - (result + 0.5)^2
				//	 = num - result - 0.5
				num -= result;
				num = (num << 16) - 0x8000;
				result = (result << 16) + 0x8000;
			}
			else
			{
				num <<= 16;
				result <<= 16;
			}
			
			bit = 1 << 14;
		}
	}

#ifndef FIXMATH_NO_ROUNDING
	// Finally, if next bit would have been 1, round the result upwards.
	if (num > result)
	{
		result++;
	}
#endif
	
	return (neg ? -result : result);
}
