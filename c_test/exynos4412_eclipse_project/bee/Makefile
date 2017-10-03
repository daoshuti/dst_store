SHELL=C:\Windows\System32\cmd.exe

all:
	arm-none-eabi-gcc -g -c led.s -o led.o
	arm-none-eabi-ld -Ttext 0x40001000 led.o -o led.elf
	arm-none-eabi-objdump -D led.elf > led.dis
	
.PHONY: clean
clean:
	rm -rf *.o *.elf