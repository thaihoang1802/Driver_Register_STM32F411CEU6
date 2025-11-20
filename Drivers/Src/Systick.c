#include"stm32f4xx.h"
#include"GPIO.h"
#include"System_Clock.h"
#include"library.h"

/*    16Mhz Clock Configuration
    - AHB Prescaler: 1 (16MHz)
    - Load value for SysTick: 16000 (1ms tick)

*/ 
volatile uint64_t systick_ms ; 

void SysTick_Handler(void){
            systick_ms++ ;  // + 1ms 
 } 
 
void SysTick_Init(void){
    SYSTICK->LOAD = 16000 ; //  (16MHz / 16000 = 1KHz) -> 1ms 
    SYSTICK->VAL  = 16000 ; 
    SYSTICK->CTRL |= (1<<2)|(1<<1)|(1<<0); // Enable SysTick with interrupt, clock source AHBPP
}

uint32_t millis(){
    return (uint32_t)systick_ms; 
}

void delay_ms(uint32_t ms){
    uint32_t time = systick_ms;
    while((millis() - time ) < ms);

}



/*   PWM SERVO USED SYSTICK 

unsigned char Index = 0 ;
uint32_t servo_time[2] = {24000, 296000,};
void SysTick_Handler(void)
{
    SYSTICK->LOAD = servo_time[Index] ; 
    if (Index == 0)
    {
         *BITBAND_PERIPH_POINTER(&(GPIOA->ODR),1) = 1 ;
         Index ++ ; 
    }
    else if (Index == 1){
        Index = 0  ;
        *BITBAND_PERIPH_POINTER(&(GPIOA->ODR),1) = 0 ;
   }
    SYSTICK->CTRL |= (1<<2)|(1<<1);
    SYSTICK->VAL = 0 ;
    SYSTICK->CTRL |= (1<<2)|(1<<1)|(1<<0); // Enable SysTick with interrupt, clock source AHBPP
}

*/
