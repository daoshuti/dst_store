#include "exynos_4412.h"
#include "hardwark/beep.h"
#include "hardwark/key.h"
#include "hardwark/interrupt.h"

void mydelay_ms(int ms) {
	int i, j;
	while (ms--) {
		for (i = 0; i < 5; i++)
			for (j = 0; j < 514; j++)
				;
	}
}
void alarm_init(){


}
int main(void) {

	uart_init();
	beep_init();
	key_init();
	key4_init();

	while (1)
		;
	return 0;
}
