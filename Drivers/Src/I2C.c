#include "I2C.h"

void I2C_Init(I2C_Config *I2C) {

    GPIO_Config I2C_PORT ;

    GPIOB_CLK_ENB() ; 

    I2C_PORT.GPIOx  = GPIOB ; 
    I2C_PORT.MODE   = MODE_ALTF ; 
    I2C_PORT.OType  = OTYPER_OPDRAIN ; 
    I2C_PORT.AF     = 4 ;
    I2C_PORT.Pull   = PUPDR_PU ;
    I2C_PORT.Speed  = OSPEEDR_HIGH ; 

    if (I2C->I2Cx == I2C1)
    {
        I2C1_CLK_ENB();
        I2C_PORT.PIN = SDA1 | SCL1 ; 
    }
    else if (I2C->I2Cx == I2C2)
    {
        I2C2_CLK_ENB(); 
        I2C_PORT.PIN = SDA2 | SCL2 ; 
    }
    GPIO_Init(&I2C_PORT);
    
    I2C->I2Cx->CR1 &=~(1<<0) ; // disable CR1 PE 
    I2C->I2Cx->CR2  = I2C->APB1_Frequency_MHz; // (MHz) min 2MHZ max 50MHZ 
    
    if (I2C->MODE == Standar_Mode)
        {
            I2C->I2Cx->CCR &=~(1<<15) ; // Set Fast Mode 
            // 16000KHz / ( 2*time * 100khz) Standar Mode
            I2C->I2Cx->CCR  = (I2C->APB1_Frequency_MHz*1000000) / (2*I2C->MODE) ;
        }
    else if (I2C->MODE == Fast_Mode)
    {
        // .... 
    }

    I2C->I2Cx->TRISE = I2C->APB1_Frequency_MHz + 1 ;  // (1000ns / (1/16Mhz))  + 1 

    I2C->I2Cx->CR1 |= I2C_ACK|(1<<0);   // Enable Peripheral
}

uint8_t I2C_WRITE(I2C_Config *I2C,uint8_t Dev_adress,uint8_t Readress, uint8_t *data , uint8_t len)
{
    uint32_t timee = I2C_TIMEOUT ; 
/*
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│Start│Addr7│ W=0 │ ACK │ Reg │ ACK │Data1│ ACK │... .│DataN│ Stop│
└─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
*/

// 1 Start condition 
    I2C->I2Cx->CR1 |= I2C_START ; 
    while (!(I2C->I2Cx->SR1  & I2C_SR1_SB))
    {
        if(--timee == 0 ){
                    printf("1");

            return 1 ;
        }
    }
    (void)I2C->I2Cx->SR1 ;  // Clear I2C_SR1_SB

// 2 Transmit Adress slave + write(0) 
    I2C->I2Cx->DR = (Dev_adress << 1 ) | 0 ;  // read: 1 , write: 0
    while (!(I2C->I2Cx->SR1 & I2C_SR1_ADDR))
    {
        if(--timee == 0){
                    printf("2");

            return 2 ; 
        }
    } 
    (void)I2C->I2Cx->SR2 ; // Clear I2C_SR1_ADDR
    
// 3 Transmit Register adress 
    I2C->I2Cx->DR = (Readress) ; 
    while (!(I2C->I2Cx->SR1 & I2C_SR1_BTF))
    {
        if (--timee == 0){
                    printf("3");

            return 3 ; 
        }
    }
    
// 4 Transmit Data 
    for (uint8_t i = 0; i < len; i++)
    {
        I2C->I2Cx->DR = data[i] ; 
        while (!(I2C->I2Cx->SR1 & I2C_SR1_TXE))
        {
            if(--timee == 0){
                        printf("4");

                return 4 ;
            }
        }
    }
// 5 Wait end transmit data 
    while (!(I2C->I2Cx->SR1 & I2C_SR1_BTF))
    {
        if(--timee == 0){
            printf("5");
            return 5 ;
        }
    }
// 6 Stop transmit
    I2C->I2Cx->CR1 |=I2C_STOP;
    // printf("e");
    return 0 ; 
}   

uint8_t I2C_READ(I2C_Config *I2C, uint8_t Dev_adress, uint8_t Readress, uint8_t *data ,uint8_t len)
{

/*
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│Start│Addr7│ W=0 │ ACK │ Reg │ ACK │Start│Addr7│ R=1 │ ACK │Data1│ NACK│
└─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
*/
    uint32_t timee = I2C_TIMEOUT ; 

    // 1 Start condition 
    I2C->I2Cx->CR1 |= I2C_START ; 
    while (!(I2C->I2Cx->SR1  & I2C_SR1_SB))
    {
        if(--timee == 0 )
            return 1 ;
    }
    (void)I2C->I2Cx->SR1 ;  // Clear I2C_SR1_SB


    // 2 Transmit Adress slave + Write(0) 
    I2C->I2Cx->DR = (Dev_adress << 1 ) | 0 ;  // read: 1 , write: 0
    while (!(I2C->I2Cx->SR1 & I2C_SR1_ADDR))
    {
        if(--timee == 0)
            return 2 ; 
    } 
    (void)I2C->I2Cx->SR2 ; // Clear I2C_SR1_ADDR

    // 3 Transmit Register adress 
    I2C->I2Cx->DR = (Readress) ; 
    while (!(I2C->I2Cx->SR1 & I2C_SR1_BTF))
    {
        if (--timee == 0)
            return 3 ; 
    }

    // 4 Start condition 
    I2C->I2Cx->CR1 |= I2C_START ; 
    while (!(I2C->I2Cx->SR1  & I2C_SR1_SB))
    {
        if(--timee == 0 )
            return 44 ;
    }
    (void)I2C->I2Cx->SR1 ;  // Clear I2C_SR1_SB


    // 5 Transmit Adress slave + Read(1) 
    I2C->I2Cx->DR = (Dev_adress << 1 ) | 1 ;  // read: 1 , write: 0
    while (!(I2C->I2Cx->SR1 & I2C_SR1_ADDR))
    {
        if(--timee == 0)
            return 5 ; 
    } 
    (void)I2C->I2Cx->SR2 ; // Clear I2C_SR1_ADDR


    for (uint8_t i = 0; i < len; i++)
    {
        while (!(I2C->I2Cx->SR1 & I2C_SR1_RXNE))
        {
            if (--timee == 0) return 6;
        }
        if (i == len - 1 )
        {
            I2C->I2Cx->CR1 &= ~I2C_ACK ; 
        }
        else{I2C->I2Cx->CR1 |= (I2C_ACK);}

        data[i] = I2C->I2Cx->DR ;  // During clear RxNE
    }
    // 6 Stop transmit
    I2C->I2Cx->CR1 |=I2C_STOP;
    return 0 ; 
}
