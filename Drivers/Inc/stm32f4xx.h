#ifndef __STM32F4xxx__
#define __STM32F4xxx__

#include <stdint.h>

#define FLASH_BASE 0x08000000UL
#define SRAM1_BASE 0x20000000UL

#define RCC_BASE 0x40023800UL
#define CRC_BASE 0x40023000UL

#define Flash_BASE 0x40023C00UL

#define AHB1_BASE 0x40020000UL
#define AHB2_BASE 0x50000000UL

#define APB1_BASE 0x40000000UL
#define APB2_BASE 0x40010000UL

#define EXTI_BASE 0x40013C00UL

#define SYSCFG_BASE 0x40013800UL

/********************************** FLASH **********************************/

typedef struct
{
	volatile uint32_t ACR;
	volatile uint32_t KEYR;
	volatile uint32_t OPTKEYR;
	volatile uint32_t SR;
	volatile uint32_t CR;
	volatile uint32_t OPTCR;
} Flash_TypeDef;
#define FLASH ((Flash_TypeDef *)Flash_BASE)

/********************************** ****** **********************************/

/********************************** RCC **********************************/
typedef struct
{
	volatile uint32_t CR;
	volatile uint32_t PLLCFGR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t AHB1RSTR;
	volatile uint32_t AHB2RSTR;
	volatile uint32_t Reserved1;
	volatile uint32_t Reserved2;
	volatile uint32_t APB1RSTR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t Reserved3;
	volatile uint32_t Reserved4;
	volatile uint32_t AHB1ENR;
	volatile uint32_t AHB2ENR;
	volatile uint32_t Reserved5;
	volatile uint32_t Reserved6;
	volatile uint32_t APB1ENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t Reserved7;
	volatile uint32_t Reserved8;
	volatile uint32_t AHB1LPENR;
	volatile uint32_t AHB2LPENR;
	volatile uint32_t Reserved9;
	volatile uint32_t Reserved10;
	volatile uint32_t APB1LPENR;
	volatile uint32_t APB2LPENR;
	volatile uint32_t Reserved11;
	volatile uint32_t Reserved12;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	volatile uint32_t Reserved13;
	volatile uint32_t Reserved14;
	volatile uint32_t SSCGR;
	volatile uint32_t PLLI2SCFGR;
	volatile uint32_t Reserved15;
	volatile uint32_t DCKCFGR;
} RCC_TypeDef;
#define RCC ((RCC_TypeDef *)RCC_BASE)

/********************************** ****** **********************************/

/********************************** SYSCFG **********************************/

typedef struct
{
	volatile uint32_t MEMRMP;
	volatile uint32_t PMC;
	volatile uint32_t EXTICR1;
	volatile uint32_t EXTICR2;
	volatile uint32_t EXTICR3;
	volatile uint32_t EXTICR4;
	volatile uint32_t CMPCR;
} SYSCFG_TypeDef;
#define SYSCFG ((SYSCFG_TypeDef *)SYSCFG_BASE)
#define SYSCFG_CLK_ENB() (RCC->APB2LPENR |= (1 << 14))

/********************************** ****** **********************************/

/********************************** EXIT **********************************/

typedef struct
{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
} Exti_TypeDef;
#define EXTI ((Exti_TypeDef *)EXTI_BASE)

/********************************** ****** **********************************/

/********************************** SYSTICK **********************************/

#define SYSTICK_BASE 0xE000E010UL
typedef struct
{
	volatile uint32_t CTRL;	 // SysTick Control and Status Register
	volatile uint32_t LOAD;	 // SysTick Reload Value Register
	volatile uint32_t VAL;	 // SysTick Current Value Register
	volatile uint32_t CALIB; // SysTick Calibration Value Register
} Systick_TypeDef;
#define SYSTICK ((Systick_TypeDef *)SYSTICK_BASE)

/********************************** ****** **********************************/

/********************************** GPIO **********************************/

#define GPIOA_BASE 0x40020000UL
#define GPIOB_BASE 0x40020400UL
#define GPIOC_BASE 0x40020800UL
#define GPIOD_BASE 0x40020C00UL
#define GPIOE_BASE 0x40021000UL
#define GPIOH_BASE 0x40021C00UL // STM32F411 có GPIOH
typedef struct
{
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFR[2];
} GPIO_TypeDef;
#define GPIOA ((GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB ((GPIO_TypeDef *)GPIOB_BASE)
#define GPIOC ((GPIO_TypeDef *)GPIOC_BASE)
#define GPIOD ((GPIO_TypeDef *)GPIOD_BASE)
#define GPIOE ((GPIO_TypeDef *)GPIOE_BASE)
#define GPIOH ((GPIO_TypeDef *)GPIOH_BASE)

#define GPIOA_CLK_ENB() (RCC->AHB1ENR |= (1 << 0))
#define GPIOB_CLK_ENB() (RCC->AHB1ENR |= (1 << 1))
#define GPIOC_CLK_ENB() (RCC->AHB1ENR |= (1 << 2))
#define GPIOD_CLK_ENB() (RCC->AHB1ENR |= (1 << 3))
#define GPIOE_CLK_ENB() (RCC->AHB1ENR |= (1 << 4))
#define GPIOH_CLK_ENB() (RCC->AHB1ENR |= (1 << 7))

/********************************** ****** **********************************/

/********************************** USART **********************************/

#define USART1_BASE 0x40011000UL // APB2
#define USART2_BASE 0x40004400UL // APB1
#define USART6_BASE 0x40011400UL // APB2
typedef struct
{
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
} USART_TypeDef;
#define USART1 ((USART_TypeDef *)USART1_BASE)
#define USART2 ((USART_TypeDef *)USART2_BASE)
#define USART6 ((USART_TypeDef *)USART6_BASE)
#define USART2_CLK_ENB() (RCC->APB1ENR |= (1 << 17))
#define USART1_CLK_ENB() (RCC->APB2ENR |= (1 << 4))
#define USART6_CLK_ENB() (RCC->APB2ENR |= (1 << 5))

/********************************** ****** **********************************/

/********************************** I2C	**********************************/

#define I2C_1_BASE 0x40005400UL
#define I2C_2_BASE 0x40005800UL // APB1
#define I2C_3_BASE 0x40005C00UL
typedef struct
{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t OAR1;
	volatile uint32_t OAR2;
	volatile uint32_t DR;
	volatile uint32_t SR1;
	volatile uint32_t SR2;
	volatile uint32_t CCR;
	volatile uint32_t TRISE;
	volatile uint32_t FLTR;
} I2C_TypeDef;
#define I2C1 ((I2C_TypeDef *)I2C_1_BASE)
#define I2C2 ((I2C_TypeDef *)I2C_2_BASE)
#define I2C3 ((I2C_TypeDef *)I2C_3_BASE)
#define I2C1_CLK_ENB() (RCC->APB1ENR |= (1 << 21))
#define I2C2_CLK_ENB() (RCC->APB1ENR |= (1 << 22))
#define I2C3_CLK_ENB() (RCC->APB1ENR |= (1 << 23))

/********************************** ****** **********************************/

/********************************** TIM	**********************************/

#define TIM1_BASE 0x40010000UL // APB2
#define TIM2_BASE 0x40000000UL // APB1
#define TIM3_BASE 0x40000400UL // APB1
#define TIM4_BASE 0x40000800UL // APB1
#define TIM5_BASE 0x40000C00UL // APB1
typedef struct
{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMCR;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	volatile uint32_t CCMR1;
	volatile uint32_t CCMR2;
	volatile uint32_t CCER;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
	volatile uint32_t Reserved1;
	volatile uint32_t CCR1;
	volatile uint32_t CCR2;
	volatile uint32_t CCR3;
	volatile uint32_t CCR4;
	volatile uint32_t Reserved2;
	volatile uint32_t DCR;
	volatile uint32_t DMAR;
	volatile uint32_t OR;
} TIM_TypeDef;
#define TIM1 ((TIM_TypeDef *)TIM1_BASE) // APB2
#define TIM2 ((TIM_TypeDef *)TIM2_BASE)
#define TIM3 ((TIM_TypeDef *)TIM3_BASE)
#define TIM4 ((TIM_TypeDef *)TIM4_BASE)
#define TIM5 ((TIM_TypeDef *)TIM5_BASE)
#define TIM1_CLK_ENB() (RCC->APB2ENR |= (1 << 0)) // Enable TIM1 clock
#define TIM2_CLK_ENB() (RCC->APB1ENR |= (1 << 0))
#define TIM3_CLK_ENB() (RCC->APB1ENR |= (1 << 1))
#define TIM4_CLK_ENB() (RCC->APB1ENR |= (1 << 2))
#define TIM5_CLK_ENB() (RCC->APB1ENR |= (1 << 3))

/********************************** ****** **********************************/

/********************************** ADC1 **********************************/

#define ADC1_BASE 0x40012000UL
typedef struct
{
	volatile uint32_t SR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMPR1;
	volatile uint32_t SMPR2;
	volatile uint32_t JOFR1;
	volatile uint32_t JOFR2;
	volatile uint32_t JOFR3;
	volatile uint32_t JOFR4;
	volatile uint32_t HTR;
	volatile uint32_t LTR;
	volatile uint32_t SQR1;
	volatile uint32_t SQR2;
	volatile uint32_t SQR3;
	volatile uint32_t JSQR;
	volatile uint32_t JDR1;
	volatile uint32_t JDR2;
	volatile uint32_t JDR3;
	volatile uint32_t JDR4;
	volatile uint32_t DR;
} ADC_TypeDef;
#define ADC1_CLK_ENB() (RCC->APB2ENR |= (1 << 8))
#define ADC1 ((ADC_TypeDef *)ADC1_BASE)

/********************************** ****** **********************************/

/********************************** DMA **********************************/

#define DMA1_BASE 0x40026000UL
#define DMA2_BASE 0x40026400UL
typedef struct
{
	volatile uint32_t LISR;
	volatile uint32_t HISR;
	volatile uint32_t LIFCR;
	volatile uint32_t HIFCR;

	volatile uint32_t S0_CR;
	volatile uint32_t S0_NDTR;
	volatile uint32_t S0_PAR; // CHANNEL 0
	volatile uint32_t S0_M0AR;
	volatile uint32_t S0_M1AR;
	volatile uint32_t S0_FCR;

	volatile uint32_t S1_CR;
	volatile uint32_t S1_NDTR; // CHANNEL 1
	volatile uint32_t S1_PAR;
	volatile uint32_t S1_M0AR;
	volatile uint32_t S1_M1AR;
	volatile uint32_t S1_FCR;

	volatile uint32_t S2_CR;
	volatile uint32_t S2_NDTR; // CHANNEL 2
	volatile uint32_t S2_PAR;
	volatile uint32_t S2_M0AR;
	volatile uint32_t S2_M1AR;
	volatile uint32_t S2_FCR;

	volatile uint32_t S3_CR;
	volatile uint32_t S3_NDTR;
	volatile uint32_t S3_PAR; // CHANNEL 3
	volatile uint32_t S3_M0AR;
	volatile uint32_t S3_M1AR;
	volatile uint32_t S3_FCR;

	volatile uint32_t S4_CR;
	volatile uint32_t S4_NDTR; // CHANNEL 4
	volatile uint32_t S4_PAR;
	volatile uint32_t S4_M0AR;
	volatile uint32_t S4_M1AR;
	volatile uint32_t S4_FCR;

	volatile uint32_t S5_CR;
	volatile uint32_t S5_NDTR; // CHANNEL 5
	volatile uint32_t S5_PAR;
	volatile uint32_t S5_M0AR;
	volatile uint32_t S5_M1AR;
	volatile uint32_t S5_FCR;

	volatile uint32_t S6_CR;
	volatile uint32_t S6_NDTR; // CHANNEL 6
	volatile uint32_t S6_PAR;
	volatile uint32_t S6_M0AR;
	volatile uint32_t S6_M1AR;
	volatile uint32_t S6_FCR;

	volatile uint32_t S7_CR;
	volatile uint32_t S7_NDTR; // CHANNEL 7
	volatile uint32_t S7_PAR;
	volatile uint32_t S7_M0AR;
	volatile uint32_t S7_M1AR;
	volatile uint32_t S7_FCR;

} DMA_TypeDef;
#define DMA1 ((DMA_TypeDef *)DMA1_BASE)
#define DMA2 ((DMA_TypeDef *)DMA2_BASE)
#define DMA1_CLK_ENBLE() (RCC->AHB1ENR |= (1 << 21))
#define DMA2_CLK_ENBLE() (RCC->AHB1ENR |= (1 << 22))

/********************************** ****** **********************************/

#endif // __STM32F4xxx__
