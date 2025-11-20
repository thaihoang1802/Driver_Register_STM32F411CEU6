#ifndef I2C_H
#define I2C_H

#include "stm32f4xx.h"
#include "main.h"

#define I2C_START       (1 << 8)
#define I2C_STOP        (1 << 9)
#define I2C_ACK         (1 << 10)
#define I2C_SR1_SB      (1 << 0)
#define I2C_SR1_ADDR    (1 << 1)
#define I2C_SR1_TXE     (1 << 7)
#define I2C_SR1_BTF     (1 << 2)
#define I2C_SR1_RXNE    (1 << 6)

#define I2C_TIMEOUT 100000

#define Standar_Mode    100000
#define Fast_Mode       400000

#define SDA1 (1<<9)  // PORT B 
#define SCL1 (1<<8)

#define SDA2 (1<<3)  // PORT B 
#define SCL2 (1<<10)

typedef struct 
{
    I2C_TypeDef *I2Cx ; 
    uint32_t APB1_Frequency_MHz ; 
    uint32_t MODE ; 

}I2C_Config;
void I2C_Init(I2C_Config *I2C) ; 
uint8_t I2C_WRITE(I2C_Config *I2C, uint8_t Dev_adress, uint8_t Readress, uint8_t *data ,uint8_t len);
uint8_t I2C_READ(I2C_Config *I2C, uint8_t Dev_adress, uint8_t Readress, uint8_t *data ,uint8_t len);

#endif // I2C_H
