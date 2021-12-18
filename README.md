Its UART driver developed on STM32 using KEIL software

1.void UART_init(unsigned short uart,unsigned long BR)
uart - uart number 1,2,3
BR - buard rate (9600,115200,...)

2.void Write_UART(char mesg,unsigned short uart)
This function enables sending a character through UART


3.char Read_UART(unsigned short uart);
Reading function from UART

4.void Write_UART_string(char str[],unsigned short uart);
function used for sending multiple character message through uart.
