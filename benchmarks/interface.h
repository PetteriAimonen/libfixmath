// This file defines the hardware or simulator interface that will be used to
// measure timings and report results.

#include <stdint.h>

/* Tools for profiling */

typedef struct {
    uint32_t min;
    uint32_t max;
    uint32_t sum;
    uint32_t count;
} cyclecount_t;

// Initialize
void interface_init();

// Reset timer/counter/something
void start_timing();

// Return the number of clock cycles passed since start_timing();
uint16_t end_timing();

// Print a value to console, along with a descriptive label
void print_value(const char *label, int32_t value);

void print(const char *label, cyclecount_t *count);
