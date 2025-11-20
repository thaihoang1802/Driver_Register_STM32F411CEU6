#ifndef SERVO_
#define SERVO_

#include "stm32f4xx.h"
#include "GPIO.h"
#include "time.h"
#include "library.h"

#define PIN(n) (1U << (n))

#define   CH1_TIM2  PIN(5)  //A5
#define   CH2_TIM2  PIN(1)  //A6 TIM2
#define   CH3_TIM2  PIN(2)  //A2
#define   CH4_TIM2  PIN(3)  //A3

#define   CH1_TIM3  PIN(6)  //A6
#define   CH2_TIM3  PIN(7)  //A7
#define   CH3_TIM3  PIN(0)  //B0
#define   CH4_TIM3  PIN(1)  //A1

#define   CH1_TIM4 PIN(6)   //B6
#define   CH2_TIM4 PIN(7)   //B7
#define   CH3_TIM4 PIN(8)   //B8
#define   CH4_TIM4 PIN(9)   //B9

/*
    Example used Servo  Fclk = 16Mhz 

    Servo : ON 50Hz 1->2 ms 
        
    Servo_Config Servo ;
    Servo.TIMx        = TIM2;
    Servo.Prescaler   = 15 ;           // Prescaler value (15+1)
    Servo.ARR         = 19999;         // Auto-reload value for 50Hz    

    Servo_Init(&Servo,CH1_TIMx);

    Servo_Set(&Servo, 1, 1500) ;  // ~ 90 degree 
*/

typedef struct 
{
   TIM_TypeDef *Timx ; 
   volatile uint32_t Precasler ;  
   volatile uint32_t ARR ; 
   volatile uint32_t CHx_TIMx ;
}Servo_Config;
void Servo_Init(Servo_Config *TIMx, uint8_t channel);
void Servo_Set(TIM_TypeDef *TIMx , uint8_t channel ,uint8_t angle) ;

#endif // SERVO_ 
