
#include "main.h"
USART_Config USART_6 ;
I2C_Config I2C_1 ; 
GPIO_Config LED , STEP ;


PID_Config PID ={
    .KP = 100 ,
    .KI = 0 , 
    .KD = 0 
};
int Input ; 

static void MX_USART6_INIT(void);
static void MX_GPIO_INIT(void);


uint16_t buffe[8] ; 
uint16_t data[8];
int16_t weight[8] = {-3,-2,-1,0,0,1,2,3}; 

int average = 0 ; 
int sum = 0 ; 
float value ;

void temp(){

}
int main(void)
{
SysTick_Init();

MX_USART6_INIT();   /*USART2*/
MX_GPIO_INIT();     /*GPIO*/
//MX_ADC_INIT();      /*ADC*/
//ADC1_DMA(ADC1,DMA2,buffe,8);
//ADC1_Start();
    while (1)
    {   int t = 50 ;
    	for ( int var = 0;  var < 200; var ++) {
    		GPIOA->ODR |=(1<<7);
    		delay_ms(t);
    		GPIOA->ODR &=~(1<<7);
    		delay_ms(t);

		}
    	delay_ms(1000);

    }
}


static void MX_GPIO_INIT(void){
	LED.GPIOx = GPIOC ;
	LED.MODE  = MODE_OUTPUT ;
	LED.PIN    = PIN(13);
	LED.Speed = OSPEEDR_LOW;
    GPIO_Init(&LED);

    STEP.GPIOx = GPIOA ;
    STEP.MODE 	= MODE_OUTPUT ;
    STEP.PIN	= PIN(7) ;
    STEP.Pull	= PUPDR_PD ;
    STEP.Speed	= OSPEEDR_HIGH;
    GPIO_Init(&STEP);
}
static void MX_USART6_INIT(void){
   USART_6.USARTx 		= USART6 ;
   USART_6.BaudRate 	= 115200 ;
   USART_6.PCLK     	= 16000000 ;
   USART_Init(&USART_6) ;
}
//static void MX_ADC_INIT(void){
//    adc.ADCx = ADC1 ;
//    adc.Inx = Read_all ;
//    adc.MODE = DMA_MODE ;
//    adc.Numchannel = 8 ;
//    adc.Resolution = _12bit ;
//    adc.Samplingtime = _15cycles ;
//    ADC1_Init(&adc);
//}
//static void MX_I2C_INIT(void){
//    I2C_1.APB1_Frequency_MHz = 16 ;
//    I2C_1.I2Cx = I2C1 ;
//    I2C_1.MODE = Standar_Mode ;
//    I2C_Init(&I2C_1);
//}

