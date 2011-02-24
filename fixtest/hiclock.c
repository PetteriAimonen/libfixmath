#include "hiclock.h"

#if defined(__WIN32) || defined(__WIN64)
LONGLONG HICLOCKS_PER_SEC = 0;

void hiclock_init() {
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	HICLOCKS_PER_SEC = freq.QuadPart;
}
#endif

hiclock_t hiclock() {
	#if defined(__unix__)
	timeval clocks;
	gettimeofday(&clocks, NULL);
	return ((uint64_t)clocks.tv_sec * 1000000ULL) + clocks.tv_usec;
	#elif defined(__WIN32) || defined(__WIN64)
	LARGE_INTEGER clocks;
	QueryPerformanceCounter(&clocks);
	return clocks.QuadPart;
	#else
	return clock();
	#endif
}
