#include"TIMx.h"

void TIM_Init(TIM_Config *tim_config){
  
}
  
/*
    // TIM1 INTERUPT TEST

    // // BASE_CLOCK = 16MHz TIM1 

    // TIM1_CLK_ENB();         // Enable TIM1 clock

    // TIM1->DIER |= (1 << 0); // Enable update interrupt
    // TIM1->PSC = 0 ;
    // TIM1->ARR = 15999;      // Set auto-reload value (ARR)
    // TIM1->CR1 |= (1 << 7);  // Enable auto-reload preload
    // TIM1->CR1 |= (1 << 0);  // Enable the timer
    // TIM1->CR1 |= (1<< 2);   // Set the timer to upcounting mode
     
    // // NVIC ENABLE
    // *((unsigned long *)0xE000E100) |= (1 << 25); // Enable TIM1 update interrupt in NVIC
    // //NVIC DISABLE
    // *((unsigned long *)0xE000E180) |= (1 << 25); // Disable TIM1 update interrupt in NVIC


*/