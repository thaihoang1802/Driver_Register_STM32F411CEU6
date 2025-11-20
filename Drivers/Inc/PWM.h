#ifndef PWM_H
#define PWM_H

#include"stm32f4xx.h"
#include"GPIO.h"
 /*
                        PA5         CH1    TIM2
                        PA1         CH2
                        PA2         CH3
                        PA3         CH4

                        PA6         CH1    TIM3
                        PA7         CH2
                        PB0         CH3
                        PA1         CH4
*/

#define   CH1_TIM2  PIN(5)
#define   CH2_TIM2  PIN(1)
#define   CH3_TIM2  PIN(2)
#define   CH4_TIM2  PIN(3)

#define   CH1_TIM3  PIN(6)
#define   CH2_TIM3  PIN(7)
#define   CH3_TIM3  PIN(0)
#define   CH4_TIM3  PIN(1)


/*  Example usage of PWM functions:

    Fclk = 16Mhz / (1599 + 1) = 1KHz 

    PWM_Config PWM ;
    PWM.TIMx        = TIM2;
    PWM.Prescaler   = 0;            // Prescaler value
    PWM.Period      = 1599;         // Auto-reload value for 1kHz
	
    PWM_Init(&PWM,CH1_TIM2); // Initialize PWM port and pin

    PWM_SET(&PWM,1,50);		 // Initialize PWM

*/

typedef struct {
    TIM_TypeDef 	*TIMx;
    uint32_t 		Prescaler; // Prescaler value
    uint32_t 		Period;    // Auto-reload value
} PWM_Config;
void PWM_SET_ALL(PWM_Config *PWM , uint32_t duty_ch1 , uint32_t duty_ch2, uint32_t duty_ch3, uint32_t duty_ch4);
void PWM_SET(PWM_Config *PWM,uint8_t Chanle, uint8_t duty);
void PWM_Init(PWM_Config *TIMx,uint32_t Channel_x_TIMx);
#endif // PWM_H
