#ifndef ENCODER_H
#define ENCODER_H
#include "main.h"

/*
    ENCODER :   - TIM3  A6 A7  
                - TIM 4 B6 B7 
*/

/*
    Example use code :      ENODER1.TIMx = TIM4 ; 
                            ENODER1.MODE = MODE3 ; 
                            ENODER1.Filter = 4 ; 
                            ENODER1.Polarity = 0 ;
                            Enoder_Init(&ENODER1) ;
*/
#define MODE1 1 
#define MODE2 2 
#define MODE3 3 

#define RASING 0 
#define FALLING 1 

typedef struct  
{
    TIM_TypeDef *TIMx ; 
    uint8_t MODE ; 
    uint8_t Polarity ; 
    uint8_t Filter ;  // 1 ..... 15 common 3,4 
}Encoder_Config;

void Enoder_Init(Encoder_Config *encoder);
float Result_Encoder_1s(TIM_TypeDef *TIMx,uint8_t Mode , float pulse);
#endif // ENCODER_H