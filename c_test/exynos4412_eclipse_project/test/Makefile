SHELL=C:\WINDOWS\system32\cmd.exe

all:
	arm-none-eabi-gcc -g -c test.s -o test.o
	arm-none-eabi-gcc -g -c led.c -o led.o
	arm-none-eabi-ld -Ttext 0x40001000 test.o led.o -o test.elf
	arm-none-eabi-objdump -D test.elf > test.dis

.PHONY:clean
clean:
	rm -rf *.o *.elf