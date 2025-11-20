#ifndef ADC_H
#define ADC_H

#include "stm32f4xx.h"
#include "main.h"

#define _12bit (0b00) // Resolution
#define _10bit (0b01)
#define _8bit (0b10)
#define _6bit (0b11)

#define _3cycles (0b000) // Samplingtime
#define _15cycles (0b001)
#define _28cycles (0b010)
#define _56cycles (0b011)
#define _84cycles (0b100)
#define _112cycles (0b101)
#define _144cycles (0b110)
#define _480cycles (0b111)

typedef enum
{
    SCAN_MODE,
    DMA_MODE,
    CONTINUOUS_MODE
} Mode_ADC;

typedef enum
{
    IN0,
    IN1,
    IN2,
    IN3,
    IN4,
    IN5,
    IN6,
    IN7,
    IN8,
    IN9,
    Read_all
} INx;

typedef struct
{
    ADC_TypeDef *ADCx;
    Mode_ADC MODE;
    INx Inx;
    uint8_t Numchannel;
    uint8_t Resolution;
    uint8_t Samplingtime;
} ADC_Config;

void ADC1_Init(ADC_Config *ADC);
void ADC1_Start();
void ADC1_DMA(ADC_TypeDef *ADC, DMA_TypeDef *DMA, uint16_t *Buffer, uint8_t lengh);
uint16_t read_ADC1(ADC_TypeDef *ADC);

/*
ADC_Config ADC_1 ={
  .ADCx         = ADC1 ,
  .MODE         = DMA_MODE ,
  .Inx      	= Read_all  ,
  .Numchannel   = 8,
  .Resolution   = _12bit ,
  .Samplingtime = _480cycles
} ;
ADC1_Init(&ADC_1);
ADC1_DMA(ADC1,DMA2,ADC_Value,8);
ADC1_Start();
GPIOB->ODR |=(1<<1);
  while (1)
    {
        for (int  i = 0; i < 8; i++)
        {
            x[i] = map_adc_pwm(ADC_Value[i],3860,4010,0,1000);
        }
        printf("Range Map : %d      %d      %d      %d      %d      %d      %d      %d\n",x[0],x[1],x[2],x[3],x[4],x[5],x[6],x[7]);
        printf("***************************\n");
        // printf("Range Map : %d      %d      %d      %d      %d      %d      %d      %d\n",ADC_Value[0],ADC_Value[1],ADC_Value[2],ADC_Value[3],ADC_Value[4],ADC_Value[5],ADC_Value[6],ADC_Value[7]);
        printf("\n");
        delay_ms(300);
    }


    GPIO_ADC1.GPIOx = GPIOA ;
    GPIO_ADC1.MODE = MODE_ANALOG ;
    GPIO_ADC1.Speed = OSPEEDR_HIGH;
    GPIO_ADC1.PIN = PIN(0)|PIN(1)|PIN(2)|PIN(3)|PIN(4)|PIN(5)|PIN(6)|PIN(7);
    GPIO_Init(&GPIO_ADC1);

    GPIO_CALIB.GPIOx = GPIOB;
    GPIO_CALIB.MODE = MODE_OUTPUT ;
    GPIO_CALIB.PIN = PIN(1);
    GPIO_CALIB.Speed = OSPEEDR_HIGH ;
    GPIO_Init(&GPIO_CALIB);
*/
#endif // ADC_H