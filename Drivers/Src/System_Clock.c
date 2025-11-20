#include "stm32f4xx.h"
#include "System_Clock.h"

/*
    * HSE clock     = 25MHz
    * System clock  = 84MHz
    * APB1 clock    = 42MHz
    * APB2 clock    = 84MHz
    *AHB prescaler  = 84MHz
    * APB1 prescaler = 42MHz (max 50MHz)
    * APB2 prescaler = 84MHz (max 100MHz)
    * PLLM = 25
    * PLLN = 168
    * PLLP = 2   
*/

void System_Clock_HSE_84MHz(void)
{
    // 0. Cấu hình Flash
    FLASH->ACR  = 0;
    FLASH->ACR |= (2 << 0);  // 2 Wait states (84 MHz)
    FLASH->ACR |= (1 << 8);  // Prefetch enable
    FLASH->ACR |= (1 << 9);  // Instruction cache enable
    FLASH->ACR |= (1 << 10); // Data cache enable

    // 1. Bật HSE (đã bật sẵn sau reset, nhưng đảm bảo)
    RCC->CR |= (1 << 16);           // HSE ON
    while (!(RCC->CR & (1 << 17))); // Wait HSI ready

    // 2. Cấu hình PLL dùng HSE
    RCC->PLLCFGR |= (25   << 0);        // PLLM = 25
    RCC->PLLCFGR |= (168  << 6);        // PLLN = 168
    RCC->PLLCFGR |= (0b00 << 16);       // PLLP = 2
    RCC->PLLCFGR |= (1    << 22);       // PLL source = HSE

    // 3. Bật PLL
    RCC->CR |= (1 << 24);           // PLL ON
    while (!(RCC->CR & (1 << 25))); // Wait PLL ready

    // 4. Cấu hình clock cho các bus
    RCC->CFGR &= ~((0xF << 4) | (0x7 << 10) | (0x7 << 13)); // Clear prescalers
    RCC->CFGR |=  (0b0000 << 4);                            // AHB prescaler /1 = 84 MHz 
    RCC->CFGR |=  (0b100  << 10);                           // APB1 prescaler /2 = 42 MHz ( max 50 MHz )
    RCC->CFGR |=  (0b000  << 13);                           // APB2 prescaler /1 = 84 MHz ( max 100 MHz )

    // 5. Chọn PLL làm nguồn clock chính
    RCC->CFGR &= ~(0x3 << 0);
    RCC->CFGR |=  (0x2 << 0);                       // PLL selected as system clock
    while ((RCC->CFGR & (0x3 << 2)) != (0x2 << 2)); // Wait until PLL is used
}
void SystemInit_84MHz(void)
{
    RCC->CR         |= (1  <<  0);   // Bật HSI
    RCC->CR         &= ~(1 << 24);   // Tắt PLL
    RCC->CR         &= ~(1 << 16);   // Tắt HSE
    RCC->PLLCFGR     = 0x24003010;   // Giá trị reset mặc định
    RCC->CFGR        = 0x00000000;   // Reset cấu hình clock
    RCC->CIR         = 0x00000000;   // Tắt toàn bộ interrupt clock
    System_Clock_HSE_84MHz();
}

