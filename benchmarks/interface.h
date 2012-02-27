// This file defines the hardware or simulator interface that will be used to
// measure timings and report results.

#include <stdint.h>

// Initialize
void interface_init();

// Reset timer/counter/something
void start_timing();

// Return the number of clock cycles passed since start_timing();
uint16_t end_timing();

// Print a value to console, along with a descriptive label
void print_value(const char *label, int32_t value);
