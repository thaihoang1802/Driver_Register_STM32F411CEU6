#include"main.h"
#include"Encoder.h"


void Enoder_Init(Encoder_Config *Encoder){
    GPIO_Config ENCODER_GPIO ; 
    if (Encoder->TIMx == TIM3)
    {
        TIM3_CLK_ENB(); 
        ENCODER_GPIO.GPIOx = GPIOA ;
        ENCODER_GPIO.PIN   = PIN(6)|PIN(7);  // PA6 T1 / PA7 T2 
        ENCODER_GPIO.MODE  = MODE_ALTF ;
        ENCODER_GPIO.AF    = 2 ;
        GPIO_Init(&ENCODER_GPIO);
    }
    else if (Encoder->TIMx == TIM4)
    {
        TIM4_CLK_ENB();
        ENCODER_GPIO.GPIOx = GPIOB ;
        ENCODER_GPIO.PIN   = PIN(6)|PIN(7);  // PB6 T1 / PB7 T2
        ENCODER_GPIO.MODE  = MODE_ALTF ;
        ENCODER_GPIO.AF    = 2 ;
        GPIO_Init(&ENCODER_GPIO);
    }
    Encoder->TIMx->SMCR    &=~(0x111<<0);           // RESET SMS
        // IC1F & IC2F Filter
    switch (Encoder->MODE)
    {
    case 1:
        Encoder->TIMx->SMCR    |= Encoder->MODE ;   // SMS
        Encoder->TIMx->CCMR1   |=(1<<0) ;           // CC1S 
        Encoder->TIMx->CCER    |=(1<<0) ;           // CC1E
        Encoder->TIMx->CCER    |=(Encoder->Polarity<<1); // CC1P 0 : Rasing , 1 Faling
        break;
    case 2 :
        Encoder->TIMx->SMCR    |= Encoder->MODE ;   //SMS
        Encoder->TIMx->CCMR1   |=(1<<8) ;           //CC2S
        Encoder->TIMx->CCER    |=(1<<4) ;           //CC1E 
        Encoder->TIMx->CCER    |=(Encoder->Polarity<<5); // CC2P 0 : Rasing , 1 Faling
        break;
    case 3 : 
        Encoder->TIMx->SMCR    |= Encoder->MODE ;   //SMS 
        Encoder->TIMx->CCMR1   |=(1<<0) | (1<<8) ;  //CC1S & CC2S
        Encoder->TIMx->CCER    |=(1<<0) | (1<<4);   //CC1E & CC2E
        Encoder->TIMx->CCER    |=(Encoder->Polarity<<1) | (Encoder->Polarity<<5); // CC1P & CC2P 0 : Rasing , 1 Faling
        break;
    default:
        break;
    
    }
    Encoder->TIMx->CCMR1   |= ( Encoder->Filter << 4) | ( Encoder->Filter <<12) ;
    Encoder->TIMx->ARR = 0xFFFF ;                   // MAX VALUE COUTER
    Encoder->TIMx->CNT = 0 ;                        // RESET COUTER 
    Encoder->TIMx->CR1 |=(1<<0) ;                   // COUNTER ENBLE
}
float Result_Encoder_1s(TIM_TypeDef *TIMx,uint8_t Mode , float pulse){
    static int Current = 0 ; 
    static int Past = 0 ; 
    int Delta   = 0 ;
    pulse = (Mode == MODE3) ? (pulse*4) : pulse ; 

    uint32_t timee = millis();
        printf("Past Pulse: %d\n",Past) ;
    while ( (millis() - timee) < 1000){}
    
    Current = TIMx->CNT ; 
        printf("Current Pulse: %d\n",Current ) ;

    Delta = Current - Past ; 
        printf("Delta Pulse: %d\n",Delta ) ;
    if (Delta > 32767)
        {
            Delta -=65536 ; 
        }
    else if (Delta < -32767)
        {
            Delta +=65536 ; 
        }
    float Result = (Delta*60) / pulse   ; // RPM
        printf("Result: %f PRM\n",Result);

    Past = Current ; 

    return Result ; 
}

/*
 float result_encoder(){

       uint32_t timee = millis() ;
           printf("Past Pulse: %d\n",past) ;

       while( (millis() - timee) < 1000 ){}

       current = TIM4->CNT ;
           printf("Current Pulse: %d\n",current ) ;


       int delta = (current - past ) ;

           printf("Delta Pulse: %d\n",delta ) ;

           if (delta > 32767){
              delta -=65536 ;
           }

           else if (delta < -32767){
               delta +=65536 ;
           }

           delta = abs(delta);

       float result = (delta/PULSE)*60 ;
           printf("Result: %f PRM\n",result);

       past = current ;

       return result ;

}
 */
