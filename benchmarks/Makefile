# These are testcases & benchmarks for the library on the target processors
# (currently ARM Cortex M3 and AVR). They are a bit tricky to run, as they
# depend on specific simulator versions.

FILES = benchmark.c ../libfixmath/fix16.c ../libfixmath/fix16_sqrt.c ../libfixmath/fix16_exp.c

CFLAGS = -DFIXMATH_NO_OVERFLOW -DFIXMATH_NO_ROUNDING -ffast-math -I../libfixmath

testcases.c: generate_testcases.py
	python $<

benchmark-arm.elf: $(FILES) interface-arm.c testcases.c
	# Note: this needs hacked QEmu that "makes no sense":
	# https://bugs.launchpad.net/qemu/+bug/696094
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -T generic-m-hosted.ld \
		-Wall -O2 $(CFLAGS) \
		-o $@ -I .. $(FILES) interface-arm.c -lm

run-benchmark-arm: benchmark-arm.elf
	qemu-system-arm -cpu cortex-m3 -icount 0 -device armv7m_nvic \
		-nographic -monitor null -serial null \
		-semihosting -kernel $<

benchmark-avr.elf: $(FILES) interface-avr.c testcases.c
	avr-gcc -Wall -mmcu=atmega128 $(CFLAGS) \
		-O2 -DFIXMATH_OPTIMIZE_8BIT \
		-o $@ -I .. $(FILES) interface-avr.c

run-benchmark-avr: benchmark-avr.elf
	# Note: this needs simulavrxx 1.0rc0 or newer
	simulavr -d atmega128 -f $< -W 0x20,- -T exit


