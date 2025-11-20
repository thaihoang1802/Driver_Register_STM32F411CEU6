#include"Servo.h"
#include<math.h>



/*      
        - f = Fclk  / (PSC+1)*(ARR+1) 
            -> (PSC+1)*(ARR+1) = Fclk / f 

        - Example : Fclk = 16Mhz 
                    PSC = 15 + 1  
                    f(servo) = 50Hz -> 20ms 
               
         -> (15+1)*(ARR+1) = 16000000Hz / 50Hz  -> ARR = 19999 


        servo angle :   1ms  -> 2ms   (T) 
                        10000 -> 20000  (ARR)
                        x    -> 180   (Degreess) 
                        1 STEP -> 0.18 degree  (18,36,54,72,90,108,126,144,162,180)
                                                
*/

void Servo_Set(TIM_TypeDef *TIMx , uint8_t channel, uint8_t angle){

    uint8_t degree = constrain(angle,0,180) ;

    float angle_to_crr = 1000.0f +   (float)degree * (1000.0f / 180.0f) ;
    
    int crr = (uint16_t)(angle_to_crr + 0.5f) ;
        switch (channel)
        {
        case 1 :
            TIMx->CCR1 = crr ; 
            break;
        case  2:
            TIMx->CCR2 = crr ; 
            break;
        case 3 :
            TIMx->CCR3 = crr ; 
            break;
        case  4:
            TIMx->CCR4 = crr ; 
            break;

        default:
            break;
        }
    
    
}

void Servo_Init(Servo_Config *Servo , uint8_t channel){

    GPIO_Config SERVO_PWM;

    if (Servo->Timx == TIM2)
        {
            TIM2_CLK_ENB();
            GPIOA_CLK_ENB(); 
            SERVO_PWM.GPIOx  = GPIOA;
            SERVO_PWM.AF     = 1;                

        }
    else if (Servo->Timx == TIM3)
    {
        TIM3_CLK_ENB();
        GPIOA_CLK_ENB(); 
        SERVO_PWM.GPIOx = GPIOA;
        SERVO_PWM.AF     = 2;                

    }
     else if (Servo->Timx == TIM4)
    {
        TIM4_CLK_ENB();
        GPIOB_CLK_ENB(); 
        SERVO_PWM.GPIOx = GPIOB;
        SERVO_PWM.AF     = 2;                
    }

    SERVO_PWM.PIN    = Servo->CHx_TIMx ;   
    SERVO_PWM.MODE   = MODE_ALTF;
    SERVO_PWM.Speed  = OSPEEDR_HIGH;
    GPIO_Init(&SERVO_PWM);

    Servo->Timx->PSC = Servo->Precasler ; 
    Servo->Timx->ARR = Servo->ARR ; 

    switch (channel)
        {
            case  1 :
                Servo->Timx->CCR1   =  0 ; // Set duty cycle
                Servo->Timx->CCMR1 &= ~(7 << 4);   // Clear OC1M bits
                Servo->Timx->CCMR1 |=  (6 << 4);   // OC1M = 110: PWM mode 1 for channel 1
                Servo->Timx->CCMR1 &= ~(3 << 0);   // CC1S = 00: Output mode
                Servo->Timx->CCMR1 |=  (1 << 3);   // OC1PE = 1: Enable CCR1 preload
                Servo->Timx->CCER  |=  (1 << 0);   // CC1E = 1: Output enable
            break;
            case 2 :
                Servo->Timx->CCR2   =  0; // Set duty cycle
                Servo->Timx->CCMR1 &= ~(7 << 12);  // Clear OC2M bits
                Servo->Timx->CCMR1 |=  (6 << 12);  // OC2M = 110: PWM mode 1 for channel 2
                Servo->Timx->CCMR1 &= ~(3 << 8);   // CC2S = 00: Output mode
                Servo->Timx->CCMR1 |=  (1 << 11);  // OC2PE = 1: Enable CCR2 preload
                Servo->Timx->CCER  |=  (1 << 4);   // CC2E = 1: Output enable
            break;
                
            case 3 : 
                Servo->Timx->CCR3   =  0 ; // Set duty cycle
                Servo->Timx->CCMR2 &= ~(7 << 4);   // Clear OC3M bits
                Servo->Timx->CCMR2 |=  (6 << 4);   // OC3M = 110: PWM mode 1 for channel 3
                Servo->Timx->CCMR2 &= ~(3 << 0);   // CC3S = 00: Output mode
                Servo->Timx->CCMR2 |=  (1 << 3);   // OC3PE = 1: Enable CCR3 preload
                Servo->Timx->CCER  |=  (1 << 8);   // CC3E = 1: Output enable
            break;
            case 4 : 
                Servo->Timx->CCR4   =  0 ; // Set duty cycle
                Servo->Timx->CCMR2 &= ~(7 << 12);  // Clear OC4M bits
                Servo->Timx->CCMR2 |=  (6 << 12);  // OC4M = 110: PWM mode 1 for channel 4
                Servo->Timx->CCMR2 &= ~(3 << 8);   // CC4S = 00: Output mode
                Servo->Timx->CCMR2 |=  (1 << 11);  // OC4PE = 1: Enable CCR4 preload
                Servo->Timx->CCER  |=  (1 << 12);  // CC4E = 1: Output enable
            break;
        
            default:
                break;
        }
        // Generate update event to load the new settings
        Servo->Timx->EGR |= (1 << 0);    // UG = 1: Generate update
        Servo->Timx->CR1 |= (1 << 0);    // CEN = 1: Start timer Counter enable


}






//void SysTick_Handler(void)
//{
//    SYSTICK->LOAD = servo_time[Index] ;
//    if (Index == 0)
//    {
//         *BITBAND_PERIPH_POINTER(&(GPIOA->ODR),1) = 1 ;
//         Index ++ ;
//    }
//    else if (Index == 1){
//        Index = 0  ;
//        *BITBAND_PERIPH_POINTER(&(GPIOA->ODR),1) = 0 ;
//   }
//    SYSTICK->CTRL |= (1<<2)|(1<<1);
//    SYSTICK->VAL = 0 ;
//    SYSTICK->CTRL |= (1<<2)|(1<<1)|(1<<0); // Enable SysTick with interrupt, clock source AHBPP
//}
