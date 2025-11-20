#include "GPIO.h"

void GPIO_Init(GPIO_Config *GPIO_CONFIG){
	if (GPIO_CONFIG->MODE <= MODE_ANALOG){
	// Enable Clock
	if(GPIO_CONFIG->GPIOx == GPIOA) GPIOA_CLK_ENB();
	if(GPIO_CONFIG->GPIOx == GPIOB) GPIOB_CLK_ENB();
	if(GPIO_CONFIG->GPIOx == GPIOC) GPIOC_CLK_ENB();
	if(GPIO_CONFIG->GPIOx == GPIOD) GPIOD_CLK_ENB();
	if(GPIO_CONFIG->GPIOx == GPIOE) GPIOE_CLK_ENB();
	if(GPIO_CONFIG->GPIOx == GPIOH) GPIOH_CLK_ENB();

	    uint16_t pin_mask = GPIO_CONFIG->PIN;

	    for (uint8_t pin = 0; pin < 16; pin++) {
	        if (pin_mask & (1 << pin)) {
	            // MODE
	            GPIO_CONFIG->GPIOx->MODER &= ~(3U << (pin * 2));
	            GPIO_CONFIG->GPIOx->MODER |=  ((GPIO_CONFIG->MODE & 0x03U) << (pin * 2));

	            // OUTPUT TYPE
	            GPIO_CONFIG->GPIOx->OTYPER &= ~(1U << pin);
	            GPIO_CONFIG->GPIOx->OTYPER |=  ((GPIO_CONFIG->OType & 0x01U) << pin);

	            // SPEED
	            GPIO_CONFIG->GPIOx->OSPEEDR &= ~(3U << (pin * 2));
	            GPIO_CONFIG->GPIOx->OSPEEDR |=  ((GPIO_CONFIG->Speed & 0x03U) << (pin * 2));

	            // PUPD
	            GPIO_CONFIG->GPIOx->PUPDR &= ~(3U << (pin * 2));
	            GPIO_CONFIG->GPIOx->PUPDR |=  ((GPIO_CONFIG->Pull & 0x03U) << (pin * 2));

	            if (GPIO_CONFIG->MODE == MODE_ALTF) {
	         	        uint8_t af = GPIO_CONFIG->AF & 0x0F;

	         	        if (pin < 8) {
	         	            GPIO_CONFIG->GPIOx->AFR[0] &= ~(0xF << (pin * 4));
	         	            GPIO_CONFIG->GPIOx->AFR[0] |=  (af << (pin * 4));
	         	        } else {
	         	            GPIO_CONFIG->GPIOx->AFR[1] &= ~(0xF << ((pin - 8) * 4));
	         	            GPIO_CONFIG->GPIOx->AFR[1] |=  (af << ((pin - 8) * 4));
	         	        }
	         	    }
	        }
	    }
	}
	else {
		// Interrupt
	}
}
void GPIO_WRITE(GPIO_TypeDef *GPIOx,uint16_t PIN ,uint8_t state){
	if(state != 1)	GPIOx->ODR &= ~(1<<PIN); 	// Clear Bit
	else GPIOx->ODR |=(1<<PIN) ; 				// Set Bit
}
uint16_t GPIO_READ(GPIO_TypeDef *GPIOx,uint16_t PIN){
	return GPIOx->IDR & (1<<PIN) ;
}
void GPIO_TOGGLE(GPIO_TypeDef *GPIOx, uint16_t PIN){
	GPIOx->ODR ^= (1 << PIN);  // Toggle the specified pin
}



