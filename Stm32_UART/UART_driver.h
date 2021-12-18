#include "gp_drive.h"
#include "stm32f10x.h"
#include "Delay.h"

void UART_init(unsigned short uart, unsigned long BR);
unsigned long UART_BRR(unsigned short uart, unsigned long BR);

char Read_UART(unsigned short uart);
void Write_UART(char mesg, unsigned short uart);

void Write_UART_string(char str[],unsigned short uart);