'''This script precalculates the correct solutions for a set of test numbers,
and writes them to testcases.c. This is aimed for running the tests on-target,
therefore it doesn't test all the cases or use floating point math, but
instead generates a ~10k binary.

The tests are chosen randomly, so there is quite good chance to eventually
catch most errors. Because the list is not regenerated automatically, the
functioning of the benchmark application is still deterministic and easy
to debug.
'''

import math
import random
import struct

# Fix16 scaling factor
scale = 65536.

# Fix16 overflow indicator
overflow = -2**31

def f16_to_float(val):
    return val / scale

def float_to_f16(val):
    val = int(round(val * scale))
    if val >= 2**31 or val < -2**31:
        val = overflow
    return val

def to_ui32(val):
    return struct.unpack('I', struct.pack('i', val))[0]

testcases = [
    # Small numbers
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
    -1, -2, -3, -4, -5, -6, -7, -8, -9, -10,
    
    # Integer numbers
    0x10000, -0x10000, 0x20000, -0x20000, 0x30000, -0x30000,
    0x40000, -0x40000, 0x50000, -0x50000, 0x60000, -0x60000,
    
    # Fractions (1/2, 1/4, 1/8)
    0x8000, -0x8000, 0x4000, -0x4000, 0x2000, -0x2000,
    
    # Problematic carry
    0xFFFF, -0xFFFF, 0x1FFFF, -0x1FFFF, 0x3FFFF, -0x3FFFF,
    
    # Smallest and largest values
    0x7FFFFFFF, -0x80000000
]
    
for i in range(10):
    # Large random numbers
    testcases.append(random.randint(-0x80000000, 0x7FFFFFFF))
    
    # Small random numbers
    testcases.append(random.randint(-100000, 100000))
    
    # Tiny random numbers
    testcases.append(random.randint(-200, 200))

out = open("testcases.c", "w")

out.write('''
/* Automatically generated testcases for fix16 operations
 * See generate_testcases.py for the generator.
 */

#include <fix16.h>

typedef struct {
    // Input
    fix16_t a;
    
    // Correct output
    fix16_t sqrt;
    fix16_t exp;
} fix16_1op_testcase;

typedef struct {
    // Inputs
    fix16_t a;
    fix16_t b;
    
    // Correct output
    fix16_t add;
    fix16_t sub;
    fix16_t mul;
    fix16_t div;
} fix16_2op_testcase;

#define TESTCASES1_COUNT (sizeof(testcases1)/sizeof(testcases1[0]))
#define TESTCASES2_COUNT (sizeof(testcases2)/sizeof(testcases2[0]))

''')

# Write testcases for 1-operand functions

out.write('static const fix16_1op_testcase testcases1[] = {\n')

for i in range(10):
    a = random.choice(testcases)
    if a >= 0:
        sqrt = float_to_f16(math.sqrt(f16_to_float(a)))
    else:
        sqrt = 0
    
    try:
        exp = float_to_f16(math.exp(f16_to_float(a)))
    except OverflowError:
        exp = 0x7FFFFFFF
        
    out.write('    {0x%08x, 0x%08x, 0x%08x}, // %d\n'
    % (to_ui32(a), to_ui32(sqrt), to_ui32(exp), i))

out.write('};\n\n')

# Write testcases for 2-operand functions

out.write('static const fix16_2op_testcase testcases2[] = {\n')

for i in range(50):
    a = random.choice(testcases)
    b = random.choice(testcases)
    
    add = float_to_f16(f16_to_float(a) + f16_to_float(b))
    sub = float_to_f16(f16_to_float(a) - f16_to_float(b))
    mul = float_to_f16(f16_to_float(a) * f16_to_float(b))
    if b != 0:
        div = float_to_f16(f16_to_float(a) / f16_to_float(b))
    else:
        div = 0
    out.write('    {0x%08x, 0x%08x, 0x%08x, 0x%08x, 0x%08x, 0x%08x}, // %d\n'
        % (to_ui32(a), to_ui32(b), to_ui32(add), to_ui32(sub), to_ui32(mul), to_ui32(div), i))

out.write('};\n\n')

out.close()
    
