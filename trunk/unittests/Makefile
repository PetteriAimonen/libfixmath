# Makefile for running the unittests of libfixmath.
CC = gcc

# Basic CFLAGS for debugging
CFLAGS = -g -O0 -I../libfixmath -Wall -Wextra -Werror

# The files required for tests
FIX16_SRC = ../libfixmath/fix16.c ../libfixmath/fix16_sqrt.c \
	../libfixmath/fix16_exp.c ../libfixmath/fix16.h

all: run_fix16_unittests run_fix16_exp_unittests

clean:
	rm -f fix16_unittests_????

# The library is tested automatically under different compilations
# options.
#
# Test naming:
# r = rounding, n = no rounding
# o = overflow detection, n = no overflow detection
# 64 = int64_t math, 32 = int32_t math

run_fix16_unittests: \
	fix16_unittests_ro64 fix16_unittests_no64 \
	fix16_unittests_rn64 fix16_unittests_nn64 \
	fix16_unittests_ro32 fix16_unittests_no32 \
	fix16_unittests_rn32 fix16_unittests_nn32 \
	fix16_unittests_ro08 fix16_unittests_no08 \
	fix16_unittests_rn08 fix16_unittests_nn08
	$(foreach test, $^, \
	echo $(test) && \
	./$(test) > /dev/null && \
	) true

fix16_unittests_no64: DEFINES=-DFIXMATH_NO_ROUNDING
fix16_unittests_rn64: DEFINES=-DFIXMATH_NO_OVERFLOW
fix16_unittests_nn64: DEFINES=-DFIXMATH_NO_ROUNDING -DFIXMATH_NO_OVERFLOW
fix16_unittests_ro32: DEFINES=-DFIXMATH_NO_64BIT
fix16_unittests_no32: DEFINES=-DFIXMATH_NO_ROUNDING -DFIXMATH_NO_64BIT
fix16_unittests_rn32: DEFINES=-DFIXMATH_NO_OVERFLOW -DFIXMATH_NO_64BIT
fix16_unittests_nn32: DEFINES=-DFIXMATH_NO_OVERFLOW -DFIXMATH_NO_ROUNDING -DFIXMATH_NO_64BIT
fix16_unittests_ro08: DEFINES=-DFIXMATH_OPTIMIZE_8BIT
fix16_unittests_no08: DEFINES=-DFIXMATH_NO_ROUNDING -DFIXMATH_OPTIMIZE_8BIT
fix16_unittests_rn08: DEFINES=-DFIXMATH_NO_OVERFLOW -DFIXMATH_OPTIMIZE_8BIT
fix16_unittests_nn08: DEFINES=-DFIXMATH_NO_OVERFLOW -DFIXMATH_NO_ROUNDING -DFIXMATH_OPTIMIZE_8BIT

fix16_unittests_% : fix16_unittests.c $(FIX16_SRC)
	$(CC) $(CFLAGS) $(DEFINES) -o $@ $^ -lm


# Tests for the exponential function, run only in default config
run_fix16_exp_unittests: fix16_exp_unittests
	./fix16_exp_unittests > /dev/null

fix16_exp_unittests: fix16_exp_unittests.c $(FIX16_SRC)
	$(CC) $(CFLAGS) $(DEFINES) -o $@ $^ -lm
