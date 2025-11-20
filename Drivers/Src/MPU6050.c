#include"main.h"
#include"MPU6050.H"

uint8_t MPU_Init(){
    uint8_t data ; 
    uint8_t check ; 
    uint8_t Check_error ; 
    I2C_Config i2c1 ; 
    i2c1.I2Cx = I2C1 ; 

    Check_error = I2C_READ(&i2c1,MPU_ADDR,WHO_I_AM,&check,1);

    if (check == MPU_ADDR )
    {
        //1 Wake up MPU 
            data = 0 ;
            I2C_WRITE(&i2c1,MPU_ADDR,PWR_MGMT_1,&data,1);

        //2 CONFIG DLPF
                /*
                 ->Gyroscope Output Rate = 8KHz : CONFIG_Register(0x1A) bit DLPF is disabled 
                 ->Gyroscope Output Rate = 1KHz : CONFIG_Register(0x1A) bit DLPF is enabled 
                */
            data = 0x00; 
            I2C_WRITE(&i2c1,MPU_ADDR,CONFIG,&data,1); 

        //3 Sample Rate 
            data = 0x07 ; 
            I2C_WRITE(&i2c1,MPU_ADDR,SMPRT_DIV,&data,1); 
                /*  Sample Rate = Gyroscope Output Rate / (1 + SMPLRT_DIV) :
                       
                        -> Sample Rate = 8khz / (1 + 7) = 1KHz 
                */
        //4  Gyroscope Configuration  
                /*
                        FS_SEL   Full Scale Range
                        0            ± 250 °/s                        
                        1            ± 500 °/s 
                        2            ± 1000 °/s 
                        3            ± 2000 °/s 
                */  
            data = 0x00 ;
            I2C_WRITE(&i2c1,MPU_ADDR,GYRO_CONFIG,&data,1); 
        //5 Accelerometer Configuration 
                /*
                AFS_SEL     Full Scale Range 
                    0           ± 2g 
                    1           ± 4g 
                    2           ± 8g 
                    3           ± 16g
                */
            data = 0x00 ;
            I2C_WRITE(&i2c1,MPU_ADDR,ACCEL_CONFIG,&data,1); 

        printf(" MPU Complete \n");
        return 1 ;
    }
    
    else 
    {  
        printf("None connect Check 104!!! %d\n",Check_error); 
        return 0 ;
    } 
}
double MPU_ACCEL(MPU *Structure){
    I2C_Config i2c1 ;
    i2c1.I2Cx = I2C1 ;

    uint8_t data[6] ; 
    I2C_READ(&i2c1,MPU_ADDR,ACCEL_XOUT_H,data,6); 

    Structure->ACCEL_Xraw = (int16_t)((data[0] << 8) | data[1]) ; 

    Structure->ACCEL_Yraw = (int16_t)((data[2] << 8) | data[3]) ; 

    Structure->ACCEL_Zraw = (int16_t)((data[4] << 8) | data[5]) ; 

    // printf(" ACCEL_Xraw : %d ACCEL_Yraw : %d  ACCEL_Zraw : %d\n",ACCEL_Xraw,ACCEL_Yraw,ACCEL_Zraw);


    // float accel_x = (float)(ACCEL_Xraw / 16384.0f)   ;
    // float accel_y = (float)(ACCEL_Yraw / 16384.0f)   ;
    // float accel_z = (float)(ACCEL_Zraw / 16384.0f)   ;

    // printf(" accel_x : %f accel_y : %f accel_z : %f\n",accel_x,accel_y,accel_z);
     

    if (Structure->ACCEL_Xraw != 0)
    {
        float s1 =   sqrt(Structure->ACCEL_Yraw*Structure->ACCEL_Yraw + Structure->ACCEL_Zraw*Structure->ACCEL_Zraw);
        Structure->roll = atan((float)Structure->ACCEL_Xraw/s1) * (57.29577951307855f);
    }
    else{
        Structure->roll = 0 ;
    }


    if (Structure->ACCEL_Xraw != 0)
    {
        float s2 =   sqrt(Structure->ACCEL_Xraw*Structure->ACCEL_Xraw + Structure->ACCEL_Zraw*Structure->ACCEL_Zraw);
        Structure->pitch = atan((float)Structure->ACCEL_Yraw/s2) * (57.29577951307855f);
    }
    else{
        Structure->pitch = 0 ;
    }
    return 0 ; 
}

double MPU_GYRO(MPU *Structure,Yaw_config *yaw){
    
    I2C_Config i2c1 ;
    i2c1.I2Cx = I2C1 ;

    uint8_t data[6] ; 

    yaw->timee = millis();

    I2C_READ(&i2c1,MPU_ADDR,GYRO_XOUT_H,data,6); 
    Structure->GYRO_Zraw = (int16_t)((data[4] << 8) | data[5]) ;

    yaw->dt = (yaw->timee - yaw->time_prev) / 1000.f ; 

    yaw->time_prev = yaw->timee ; 

    Structure->gyro_z = Structure->GYRO_Zraw  / 131.0f  ; // -237.79 , -236.75 , -238.06 offset
    
    Structure->Yaw +=(Structure->gyro_z)*yaw->dt ; 
    printf(" dt : %.2f\n",yaw->dt);

    return Structure->Yaw ; 
}

double cablib(){

    I2C_Config i2c1 ;
    i2c1.I2Cx = I2C1 ;

    uint8_t data[6] ; 
    int16_t GYRO_Zraw ; 
    float sum =0 ;
    for (int i = 0; i < 500; i++)
    {
        I2C_READ(&i2c1,MPU_ADDR,GYRO_XOUT_H,data,6); 
        GYRO_Zraw = (int16_t)((data[4] << 8) | data[5]) ;
        GYRO_Zraw +=GYRO_Zraw ; 
    }
    return sum = GYRO_Zraw/500;
    

}



uint8_t MPU_Temperature(){
    I2C_Config i2c1 ;
    i2c1.I2Cx = I2C1 ;
    uint8_t TEMP_OUT[2] ;

    I2C_READ(&i2c1,MPU_ADDR,TEMP,TEMP_OUT,2); 

    int16_t temp_raw = (int16_t)((TEMP_OUT[0] << 8) | TEMP_OUT[1]);
    
    float Temperature = ((float)temp_raw / 340.0f) + 36.53f  ;

    return Temperature ;
}
