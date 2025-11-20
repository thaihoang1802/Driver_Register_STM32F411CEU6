#ifndef __TIMx__
#define __TIMx__

#include "stm32f4xx.h"
typedef struct {
    TIM_TypeDef *TIMx;          // Pointer to the timer peripheral
    uint32_t Prescaler;         // Prescaler value
    uint32_t Period;            // Auto-reload value
    uint32_t ClockDivision;     // Clock division
    uint32_t Mode;              // Timer mode (e.g., TIM_OCMODE_PWM1)
} TIM_Config;
void TIM_Init(TIM_Config *tim_config);

#endif // TIMx.h