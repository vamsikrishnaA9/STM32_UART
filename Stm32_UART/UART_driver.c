#include "UART_driver.h"

void UART_init(unsigned short uart, unsigned long BR)
	{
	//If using USART1 clock speed 72Mhz, else 36Mhz
		//USART3-> PB10(TX),PB11(RX)
		//USART2-> PA2(TX),PA3(RX)
		//USART1-> PA9(TX),PA10(RX)
		
		unsigned long BRR_cal;
		BRR_cal = UART_BRR(uart, BR);
		
		RCC->APB2ENR |=1;
		
		if(uart == 1){
		//enable UART2
                    RCC->APB2ENR|= 0x4000;
                      //Enable the related PINS
                     init_gpio(PA,9,OP_50, O_AF_PP);
                     init_gpio(PA,10,IN,I_PP);

	//setup the buard rate
	USART1->BRR = BRR_cal;
	//enable UART2 transmit
	USART1->CR1 |= 8;
	//Enable UART2 recieve
	USART1->CR1 |= 4;
	//Enable UART2
	USART1->CR1 |= 0x2000;		
	}
		else if(uart ==2){
		RCC->APB1ENR|= 0x20000;
//Enable the related PINS
init_gpio(PA,2,OP_50, O_AF_PP);
init_gpio(PA,3,IN,I_PP);
	//setup the buard rate
	USART2->BRR = BRR_cal;
	//enable UART2 transmit
	USART2->CR1 |= 8;
	//Enable UART2 recieve
	USART2->CR1 |= 4;
	//Enable UART2
	USART2->CR1 |= 0x2000;					
		}
		else if(uart == 3){
	RCC->APB1ENR |=0x40000;
	init_gpio(PB,10,OP_50,O_AF_PP);
	init_gpio(PA,11,IN,I_PP);
	// Setup the baude rate for 9600 bps
	USART3->BRR = BRR_cal; 
	USART3->CR1 |= 8;
	USART3->CR1 |= 4;
	USART3->CR1 |= 0x2000;		
			
		}
	}
unsigned long UART_BRR(unsigned short uart, unsigned long BR){
	unsigned long div = 36000000UL;
	unsigned long dec;
	unsigned long final;
	double frac = 36000000.00;
	double frac2 = 1.00;
	
	if(uart ==1){
		div = 72000000UL;
	frac = 72000000.00; 
	}
	div =div/(BR*16);
	frac = 16*((frac/(BR*16))-div);
	dec = frac;
	frac2 = 100*(frac-dec);
	if(frac2>50){
		dec++;
		if(dec==16){
			
	dec=0;
			div++;
		}
	}
	final = (div<<4);
	final+= dec;
	return final;
}

void Write_UART(char mesg, unsigned short uart){
	
	if(uart == 1){
		
	while((USART1->SR & (0x80))==0x00){}
  USART1->DR =(char) mesg;	
		
	}
	if(uart == 2){
		
	while((USART2->SR & (0x80))==0x00){}
  USART2->DR =(char) mesg;	
		
	}
	if(uart == 3){
		
	while((USART3->SR & (0x80))==0x00){}
  USART3->DR =(char) mesg;	
		
	}
	
}

void Write_UART_string(char str[],unsigned short uart){
	int i=0;
	DelayInit();
	while(str[i]!= '\0'){
		Write_UART(str[i],uart);
		i++;
		DelayMs(1);
	}
		
}
	


char Read_UART(unsigned short uart)
	{
	char c;
	if(uart==1){
			while((USART1->SR & 0x20)==0x00){}
	    c = (char)USART1->DR;
		
	}
		if(uart==2){
			while((USART2->SR & 0x20)==0x00){}
	    c = (char)USART2->DR;
		
	}
			if(uart==3){
			while((USART3->SR & 0x20)==0x00){}
	    c = (char) USART3->DR;
		
	}
			return c;
	
}
	
