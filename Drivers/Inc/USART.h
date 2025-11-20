#ifndef __UARTXXX__
#define __UARTXXX__

#include "stm32f4xx.h" 

/*	Example Used USART Function 

	USART_Config UART2 ;
	UART2.USARTx 	= USART2;
	UART2.BaudRate 	= 9600 ;
	UART2.PCLK     	= 16000000 ;
	
	USART_Init(&UART2);
*/

typedef struct
{
	USART_TypeDef *USARTx; // USART1,2,6
	uint32_t PCLK;
	uint32_t BaudRate; // 9600 or 115200
	uint32_t STOP_BIT;
	uint32_t DATA_BIT;

} USART_Config;


void USART_Init(USART_Config *usart_config);
void USART_Transmit(USART_TypeDef *USARTx, unsigned char data);
uint8_t USART_Receiv(USART_TypeDef *USARTx);
void USART_Transmit_String(USART_TypeDef *USARTx, const char *str);

#endif // __UARTXXX__
