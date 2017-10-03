all:
	arm-none-eabi-gcc  led.s -g  -c -o led.o 
	arm-none-eabi-ld   led.o -Ttext 0x20000 -o led.elf
clean:
	rm -rf *.o *.elf 