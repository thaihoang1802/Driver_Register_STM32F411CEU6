// System_Clock.h
#ifndef __SYSTEM_CLOCK_H
#define __SYSTEM_CLOCK_H

/*    MCO1  OUT TEST   

    GPIO_Config MCO2 ;
    MCO2.GPIOx 	= GPIOA;
    MCO2.PIN 	= PIN(8);
    MCO2.MODE 	= MODE_ALTF;
    MCO2.AF 		= 0 ;
    GPIO_Init(&MCO2);

    RCC->CFGR &= ~(0b11 << 21);// Clear MCO1 source
    RCC->CFGR |=  (0b11 << 21);// 
    RCC->CFGR |=  (0b00 << 24);// MCO1 = SYSCLK 16Mhz

    */
   
void System_Clock_HSE_84MHz(void);
void SystemInit_84MHz(void);


#endif //  __SYSTEM_CLOCK_H
