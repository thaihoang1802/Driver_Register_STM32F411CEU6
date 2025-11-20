#include "ADC.h"

void ADC1_Init(ADC_Config *ADC){

    /************** ENABLE_CLK **************/
    if (ADC->ADCx == ADC1)
    {
        ADC1_CLK_ENB() ;
    }
    else 
    {
        /* code .... ADC2 */
    }
    
    
/********************* READ ALL & READ SINGLE IN */
    if (ADC->Inx == Read_all)
    {   
        
        ADC->ADCx->SQR3 |=(0<<0) // Channel 1,2,3,4,5,6
                        |(1<<5)
                        |(2<<10)
                        |(3<<15)
                        |(4<<20)
                        |(5<<25) ; 

        ADC->ADCx->SQR2 |=(6<<0)|(7<<5); // 7,8 
        
        ADC->ADCx->SMPR2 |=  (ADC->Samplingtime << 0) // 0 
                            |(ADC->Samplingtime << 3) // 1   
                            |(ADC->Samplingtime << 6) // 2
                            |(ADC->Samplingtime << 9) // 3 
                            |(ADC->Samplingtime << 12)// 4
                            |(ADC->Samplingtime << 15)// 5
                            |(ADC->Samplingtime << 18)// 6
                            |(ADC->Samplingtime << 21);//7
                           
    }
    else{
        if ( ADC->Inx < 6)
        {
            ADC->ADCx->SQR3 |=( ADC->Inx << (ADC->Inx*5) ) ; // IN0,..IN5 

        }
        else if (ADC->Inx > 5 && ADC->Inx < 12)
        {
            ADC->ADCx->SQR2 |=( ADC->Inx << (ADC->Inx*5)); // IN6,..IN11
        }
        
        else{
            // ... SQR1  
        }
        ADC->ADCx->SMPR2 |=(ADC->Samplingtime << (ADC->Inx*3)) ;
    }

/****************** MODE DMA , SCAN , CONTINUOUS*******************/
    switch (ADC->MODE )
    {
    case DMA_MODE:
        ADC->ADCx->CR1 |=(1<<8);   // Scan mode
        ADC->ADCx->CR1  |=(ADC->Resolution << 24) ;  
        ADC->ADCx->CR2 |= (1<<1);    // CONT: Continuous conversion
        ADC->ADCx->CR2 |= (1<<10);   // EOC End of conversion selection
        ADC->ADCx->CR2 &= ~(1<<11);  // SHIFT right
        ADC->ADCx->SQR1 &=~(0xF << 20); 
        ADC->ADCx->SQR1 |=((ADC->Numchannel-1)<<20); // Number Channel
        ADC->ADCx->CR2 |= (1<<8);    // Direct memory access mode
        ADC->ADCx->CR2 |= (1<<9);    // DMA disable selection
        break;
    case SCAN_MODE :
        break;
    case CONTINUOUS_MODE:
        break;
    default:
        break;
    }
   
    
    
    ADC->ADCx->CR2 |=(1 << 0);   // ENABLE ADC (ADON)
    delay_ms(10);
}
void ADC1_Start(){
    ADC1->SR = 0 ;      // Disable Interupt
    ADC1->CR2|=(1<<30); // Start Conversion
}

void ADC1_DMA(ADC_TypeDef *ADC ,DMA_TypeDef *DMA, uint16_t *Buffer,uint8_t lengh){
    
    /* 
        ADC ONLY DMA2 
    */
   
    DMA2_CLK_ENBLE(); 

    DMA->S0_CR &= ~(1<<0);
    while (DMA->S0_CR & (1<<0)); // Wait until disabled

    DMA->S0_CR &=~(0b11 << 6);
    DMA->S0_CR |= (1<<8) ;
    DMA->S0_CR |= (1<<10) ;
    DMA->S0_CR |= (1 << 13)|(1 << 11) ;


    DMA->S0_CR &=~(7 << 25); // Stream 0

    DMA->S0_NDTR   = lengh ; 
    DMA->S0_PAR    = (uint32_t)&ADC->DR ;  // Address Peripheral 
    DMA->S0_M0AR   = (uint32_t)Buffer ;    // Address MemmoryMemmory
    
    DMA->S0_CR |=(1<<0);

} 

uint16_t read_ADC1(ADC_TypeDef *ADC){
    ADC->CR2|=(1<<30);
    while (!(ADC->SR & (1<<1)));
    return ADC->DR ; 
}

