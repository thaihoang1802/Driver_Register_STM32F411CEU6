#include "stm32f4xx.h"
#include "USART.h"
#include "GPIO.h"
#include <math.h>

void USART_Init(USART_Config *usart_config){

	GPIO_Config GPIO;

	if(usart_config->USARTx == USART1){ 
		USART1_CLK_ENB();
		GPIOA_CLK_ENB();
		GPIO.GPIOx = GPIOA ;
		GPIO.PIN = PIN(9)|PIN(10) ;   	// TX/RX : A9/A10 AF7
		GPIO.AF = 7 ;
	}
	if(usart_config->USARTx == USART2){ // TX/RX : A2/A3 AF7
			USART2_CLK_ENB();
			GPIOA_CLK_ENB();
			GPIO.GPIOx = GPIOA;
			GPIO.PIN = PIN(2) | PIN(3) ;
			GPIO.AF = 7 ;
		}
	if(usart_config->USARTx == USART6){ //TX/RX : A11/A12 AF8
			USART6_CLK_ENB();
			GPIOA_CLK_ENB();
			GPIO.GPIOx = GPIOA ;
			GPIO.PIN = PIN(11) | PIN(12) ;
			GPIO.AF = 8 ;
		}
	GPIO.MODE  = MODE_ALTF ;
	GPIO.OType = OTYPER_PP ;
	GPIO.Pull  = PUPDR_NOPULL;
	GPIO.Speed = OSPEEDR_FAST;


	GPIO_Init(&GPIO);

	// 1. Cau hinh BaudRate
	uint32_t usartdiv = (25 * usart_config->PCLK) / (4 * usart_config->BaudRate);
	uint32_t mantissa = usartdiv / 100;
	uint32_t fraction = ((usartdiv - (mantissa * 100)) * 16 + 50) / 100;
	usart_config->USARTx->BRR = (mantissa << 4) | (fraction & 0xF);

	// 2.Bat RX TX
	usart_config->USARTx->CR1 |= (1<<3) | (1<<2)  ;

	// 3.Bat UART
	usart_config->USARTx->CR1 |= (1<<13) ;
}


void USART_Transmit(USART_TypeDef *USARTx,unsigned char data){
	while(!(USARTx->SR & (1<<7))) ;
	USARTx->DR = data;
}

uint8_t USART_Receiv(USART_TypeDef *USARTx){
	while(!(USARTx->SR & (1<<5)));
	return (uint8_t)(USARTx->DR & 0xFF);
}

void USART_Transmit_String(USART_TypeDef *USARTx, const char *str) {
    while(*str) {
        USART_Transmit(USARTx, (uint8_t)(*str));
        str++;
    }
}



// void UART_Print(const char *format, ...) {
// 	char buffer[256];
// 	va_list args;
// 	va_start(args, format);
// 	vsnprintf(buffer, sizeof(buffer), format, args);
// 	va_end(args);
//     USART_Transmit_String(USART2,buffer);
// }


 int __io_putchar(int ch) {
     USART_Transmit(USART6, (char)ch);
     return ch;
 }
