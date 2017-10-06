#ifndef _UART_DOWN_H_
#define _UART_DOWN_H_

#include <stdint.h>
#include <windows.h>

int uart_init(int port, int baudrate);

void uart_close(void);

int uart_send(char *send_buff, int buff_size);

int uart_recv(char *recv_buff, int buff_size);

void uart_set_rts(void);//set RTS //gpio low

void uart_reset_rts(void);// reset RTS //gpio high

#endif /* _UART_DOWN_H_ */
