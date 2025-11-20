#ifndef MPU6050_H
#define MPU6050_H

#include "main.h"



#define MPU_ADDR        0x68
#define WHO_I_AM        0x75 
#define PWR_MGMT_1      0x6B
#define GYRO_XOUT_H     0x43 
#define ACCEL_XOUT_H    0x3B
#define SMPRT_DIV       0x19
#define GYRO_CONFIG     0x1B
#define ACCEL_CONFIG    0x1C
#define CONFIG          0x1A
#define TEMP            0x41

typedef struct 
{
    int16_t GYRO_Xraw;
    int16_t GYRO_Yraw;
    int16_t GYRO_Zraw;

    int16_t ACCEL_Xraw;
    int16_t ACCEL_Yraw;
    int16_t ACCEL_Zraw;

    float gyro_x ; 
    float gyro_y ; 
    float gyro_z ; 

    float roll ; 
    float pitch ;
    float Yaw ;
}MPU;

typedef struct 
{
   double dt ; 
   uint32_t timee ; 
   uint32_t time_prev ; 
}Yaw_config;


double Kalman();

uint8_t MPU_Init();

double MPU_ACCEL(MPU *Structure);

double MPU_GYRO(MPU *Structure,Yaw_config *Yaw );

uint8_t MPU_Temperature();


double cablib();


#endif // MPU_6050
