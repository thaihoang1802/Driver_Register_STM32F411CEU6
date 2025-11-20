#ifndef __GPIOPIN__
#define __GPIOPIN__

#include "stm32f4xx.h"
#include <stdint.h>

#define PIN(n) (1U << (n))

/************MODE***************/
#define MODE_INPUT 0x00UL
#define MODE_OUTPUT 0x01UL
#define MODE_ALTF 0x02UL
#define MODE_ANALOG 0x03UL

/************OTYPER***************/
#define OTYPER_PP 0x0UL
#define OTYPER_OPDRAIN 0x1UL

/************OSPEEDR***************/
#define OSPEEDR_LOW 0x00UL
#define OSPEEDR_MEDIUM 0x01UL
#define OSPEEDR_FAST 0x02UL
#define OSPEEDR_HIGH 0x03UL

/************PUPDR***************/
#define PUPDR_NOPULL 0x00UL
#define PUPDR_PU 0x01UL
#define PUPDR_PD 0x02UL
//		PUPDR_RESERVED 	0x03UL

typedef struct
{
	GPIO_TypeDef *GPIOx;
	uint16_t PIN;
	uint16_t MODE;
	uint16_t OType;
	uint16_t Speed;
	uint16_t Pull;
	uint16_t AF; // AF=7 : USART ; AF=8 SPI ; AF=2 TIMx PWM
} GPIO_Config;

void GPIO_Init(GPIO_Config *GPIO_CONFIG);

/*
	GPIO_Config GPIO_C;
	GPIO_C.GPIOx 	= GPIOC ;
	GPIO_C.MODE 	= MODE_OUTPUT;
	GPIO_C.PIN 		= PIN(n)|PIN(n);
	GPIO_C.OType 	= OTYPER_PP;
	GPIO_C.Pull 	= PUPDR_NOPULL;
	GPIO_C.Speed 	= OSPEEDR_LOW;
	GPIO_Init(&GPIO_C);
 */

void GPIO_WRITE(GPIO_TypeDef *GPIOx, uint16_t PIN, uint8_t state);
uint16_t GPIO_READ(GPIO_TypeDef *GPIOx, uint16_t PIN);
void GPIO_TOGGLE(GPIO_TypeDef *GPIOx, uint16_t PIN);
#endif //__GPIOPIN__
