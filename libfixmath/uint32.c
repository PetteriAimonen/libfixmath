#include "uint32.h"



uint32_t uint32_log2(uint32_t inVal) {
	if(inVal == 0)
		return 0;
	uint32_t tempOut = 0;
	if(inVal >= (1UL << 16)) { inVal >>= 16; tempOut += 16; }
	if(inVal >= (1 <<  8)) { inVal >>=  8; tempOut +=  8; }
	if(inVal >= (1 <<  4)) { inVal >>=  4; tempOut +=  4; }
	if(inVal >= (1 <<  2)) { inVal >>=  2; tempOut +=  2; }
	if(inVal >= (1 <<  1)) {               tempOut +=  1; }
	return tempOut;
}
