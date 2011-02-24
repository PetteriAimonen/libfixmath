#ifndef __hiclock_h__
#define __hiclock_h__

#include <stdint.h>
#include <inttypes.h>

#if defined(__unix__)
#include <sys/time.h>
#define PRIuHICLOCK PRIu64
#define PRIiHICLOCK PRIi64
typedef uint64_t hiclock_t;
#define HICLOCKS_PER_SEC 1000000
#define hiclock_init()
#elif defined(__WIN32) || defined(__WIN64)
#include <windows.h>
#define PRIuHICLOCK PRIu64
#define PRIiHICLOCK PRIi64
typedef LONGLONG hiclock_t;
extern LONGLONG HICLOCKS_PER_SEC;
extern void hiclock_init();
#else
#include <time.h>
#define PRIuHICLOCK PRIu32
#define PRIiHICLOCK PRIi32
typedef clock_t hiclock_t;
#define HICLOCKS_PER_SEC CLOCKS_PER_SEC
#define hiclock_init()
#endif

extern hiclock_t hiclock();

#endif

