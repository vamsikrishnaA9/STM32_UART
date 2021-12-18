#include "stm32f10x.h"
#include "gp_drive.h"
#include "Delay.h"
#include "UART_driver.h"

char mesg[250]="Welcome to Bare metal programming\n";
char chat;
int i=0; uint32_t counter =0;
int main(){
//Init UART
//Enable the alternate functions for pins
DelayInit();
UART_init(2,115200);
init_gpio(PA,1,OP_50,O_GP_PP);
	
	//-------------------------------------
	//DMA data transfer to memory to pheripheral USART
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
	USART2->CR3 |= USART_CR3_DMAT;
	
	
	while(mesg[counter]!='\0'){
		counter++;
	}
	DMA1_Channel7->CNDTR = counter; //length of message 
	DMA1_Channel7->CCR |= DMA_CCR7_MINC | DMA_CCR7_CIRC |DMA_CCR7_DIR |DMA_CCR7_TCIE;
	// memory incrememnt , circular mode, direction mode, 
	DMA1_Channel7->CPAR = (uint32_t)&USART2->DR;
	DMA1_Channel7->CMAR = (uint32_t)mesg;
	
	
	
	while(i<2){
						
//only char values will be sent	
//  Write_UART_string(mesg,2);
//	chat= Read_UART(2);
		
		
		//only by DMA transfer to USART 
		DMA1_Channel7->CCR |= DMA_CCR4_EN;
		while((DMA1->ISR & DMA_ISR_TCIF7)==0){}
			DMA1->IFCR= DMA_IFCR_CTCIF7;
			DMA1_Channel7->CCR &= ~(unsigned int)DMA_CCR4_EN; //disabling DMA after complete. if not infinite loop of sending data
		i++;
	}
}


