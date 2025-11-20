#include"PWM.h"
#include"library.h"

 
void PWM_Init(PWM_Config *PWM,uint32_t Channel_x_TIMx){
    if (PWM->TIMx == TIM2)
    {
        
        GPIOA_CLK_ENB(); // Enable GPIOA clock       TIM2
        GPIO_Config pwm_port;
        pwm_port.GPIOx  = GPIOA;
        pwm_port.PIN    = Channel_x_TIMx ;    // Example: PIN(5)|PIN(1) for PA5 and PA2
        pwm_port.MODE   = MODE_ALTF;
        pwm_port.Speed  = OSPEEDR_HIGH;
        pwm_port.AF     = 1;                // AF1 for TIM2
        GPIO_Init(&pwm_port);
    }
    else if (PWM->TIMx == TIM3)
    {
      // ..... 
        
    }
    
}

void PWM_SET_ALL(PWM_Config *PWM , uint32_t duty_ch1 , uint32_t duty_ch2, uint32_t duty_ch3, uint32_t duty_ch4)
{

    if (PWM->TIMx == TIM2) {

        TIM2_CLK_ENB();             // Enable TIM2 clock
        TIM2->PSC = PWM->Prescaler; // Set prescaler value
        TIM2->ARR = PWM->Period;    // Set auto-reload value
        TIM2->CR1 |= (1 << 7);      // ARPE = 1: Enable ARR preload

        // Set duty cycle for each channel 1 
        TIM2->CCR1   =  (TIM2->ARR + 1) * (constrain(duty_ch1,0,100)) / 100; // Set duty cycle
        TIM2->CCMR1 &= ~(7 << 4);   // Clear OC1M bits
        TIM2->CCMR1 |=  (6 << 4);   // OC1M = 110: PWM mode 1 for channel 1
        TIM2->CCMR1 &= ~(3 << 0);   // CC1S = 00: Output mode
        TIM2->CCMR1 |=  (1 << 3);   // OC1PE = 1: Enable CCR1 preload
        TIM2->CCER  |=  (1 << 0);   // CC1E = 1: Output enable
        
        // Set duty cycle for each channel 2 
        TIM2->CCR2   =  (TIM2->ARR + 1) * (constrain(duty_ch2,0,100)) / 100; // Set duty cycle
        TIM2->CCMR1 &= ~(7 << 12);  // Clear OC2M bits
        TIM2->CCMR1 |=  (6 << 12);  // OC2M = 110: PWM mode 1 for channel 2
        TIM2->CCMR1 &= ~(3 << 8);   // CC2S = 00: Output mode
        TIM2->CCMR1 |=  (1 << 11);  // OC2PE = 1: Enable CCR2 preload
        TIM2->CCER  |=  (1 << 4);   // CC2E = 1: Output enable

    
        // Set duty cycle for each channel 3
        TIM2->CCR3   =  (TIM2->ARR + 1) * (constrain(duty_ch3,0,100)) / 100; // Set duty cycle
        TIM2->CCMR2 &= ~(7 << 4);   // Clear OC3M bits
        TIM2->CCMR2 |=  (6 << 4);   // OC3M = 110: PWM mode 1 for channel 3
        TIM2->CCMR2 &= ~(3 << 0);   // CC3S = 00: Output mode
        TIM2->CCMR2 |=  (1 << 3);   // OC3PE = 1: Enable CCR3 preload
        TIM2->CCER  |=  (1 << 8);   // CC3E = 1: Output enable


        // Set duty cycle for each channel 4
        TIM2->CCR4   =  (TIM2->ARR + 1) * (constrain(duty_ch4,0,100)) / 100; // Set duty cycle
        TIM2->CCMR2 &= ~(7 << 12);  // Clear OC4M bits
        TIM2->CCMR2 |=  (6 << 12);  // OC4M = 110: PWM mode 1 for channel 4
        TIM2->CCMR2 &= ~(3 << 8);   // CC4S = 00: Output mode
        TIM2->CCMR2 |=  (1 << 11);  // OC4PE = 1: Enable CCR4 preload
        TIM2->CCER  |=  (1 << 12);  // CC4E = 1: Output enable

        // Generate update event to load the new settings
        TIM2->EGR |= (1 << 0);    // UG = 1: Generate update
        TIM2->CR1 |= (1 << 0);    // CEN = 1: Start timer Counter enable

    } else if (PWM->TIMx == TIM3) {
        
    }
 }

void PWM_SET(PWM_Config *PWM,uint8_t Channle, uint8_t duty){

    int duty_cycle = constrain(duty, 0, 100);

    if(PWM->TIMx == TIM2){

        TIM2_CLK_ENB();             // Enable TIM2 clock
        TIM2->PSC = PWM->Prescaler; // Set prescaler value
        TIM2->ARR = PWM->Period;    // Set auto-reload value

        TIM2->CR1 |= (1 << 7);      // ARPE = 1: Enable ARR preload

        switch (Channle)
        {
        case 1 :
            TIM2->CCR1   =  (TIM2->ARR + 1) * duty_cycle / 100; // Set duty_cycle cycle
            TIM2->CCMR1 &= ~(7 << 4);       // Clear OC1M bits
            TIM2->CCMR1 |=  (6 << 4);       // OC1M = 110: PWM mode 1 for channel 1
            TIM2->CCMR1 &= ~(3 << 0);       // CC1S = 00: Output mode
            TIM2->CCMR1 |=  (1 << 3);       // OC1PE = 1: Enable CCR1 preload
            TIM2->CCER  |=  (1 << 0);        // CC1E = 1: Output enable
            break;
        case 2 :
            TIM2->CCR2   =  (TIM2->ARR + 1) * duty_cycle / 100; // Set duty_cycle cycle
            TIM2->CCMR1 &= ~(7 << 12);      // Clear OC2M bits
            TIM2->CCMR1 |=  (6 << 12);      // OC2M = 110: PWM mode 1 for channel 2
            TIM2->CCMR1 &= ~(3 << 8);       // CC2S = 00: Output mode
            TIM2->CCMR1 |=  (1 << 11);      // OC2PE = 1: Enable CCR2 preload
            TIM2->CCER  |=  (1 << 4);       // CC2E = 1: Output enable
            break;
        case 3 :
            TIM2->CCR3   =  (TIM2->ARR + 1) * duty_cycle / 100; // Set duty_cycle cycle
            TIM2->CCMR2 &= ~(7 << 4);       // Clear OC3M bits
            TIM2->CCMR2 |=  (6 << 4);       // OC3M = 110: PWM mode 1 for channel 3
            TIM2->CCMR2 &= ~(3 << 0);       // CC3S = 00: Output mode
            TIM2->CCMR2 |=  (1 << 3);       // OC3PE = 1: Enable CCR3 preload
            TIM2->CCER  |=  (1 << 8);       // CC3E = 1: Output enable
            break;
        case 4 :
            TIM2->CCR4   =  (TIM2->ARR + 1) * duty_cycle / 100; // Set duty cycle
            TIM2->CCMR2 &= ~(7 << 12);      // Clear OC4M bits
            TIM2->CCMR2 |=  (6 << 12);      // OC4M = 110: PWM mode 1 for channel 4
            TIM2->CCMR2 &= ~(3 << 8);       // CC4S = 00: Output mode
            TIM2->CCMR2 |=  (1 << 11);      // OC4PE = 1: Enable CCR4 preload
            TIM2->CCER  |=  (1 << 12);      // CC4E = 1: Output enable
            break;
        default:
            break;
        }
        // Generate update event to load the new settings
        TIM2->EGR |= (1 << 0);    // UG = 1: Generate update
        TIM2->CR1 |= (1 << 0);    // CEN = 1: Start timer Counter enable
    }

    else if(PWM->TIMx == TIM3) {

	}
}
