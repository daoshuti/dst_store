/*
 *
6.2.2.61 GPF3CON
  Base Address: 0x1140_0000
  Address = Base Address + 0x01E0, Reset Value = 0x0000_0000

6.2.2.62 GPF3DAT
  Base Address: 0x1140_0000
  Address = Base Address + 0x01E4, Reset Value = 0x00
 * */

#define GPF3CON (unsigned int *)0x114001E0
#define GPF3DAT (unsigned int *)0x114001E4

void led()
{
	*(GPF3CON) = ((*(GPF3CON)) & (~(0xf<<16))) | (0x1<<16);
	*(GPF3DAT) = *(GPF3DAT)|(0x1<<4);
	return;
}
