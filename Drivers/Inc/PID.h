#ifndef _PID_H
#define _PID_H

#include "main.h"

typedef struct 
{
    float dt ;  
    uint32_t timee ; 
    uint32_t lasttimee ; 

    float erro_current ; 
    float erro_prev ; 

    float KP ; 
    float KI ; 
    float KD ; 

    float Proportional ; 
    float Integral ; 
    float Derivative ; 

}PID_Config;
float pid(PID_Config *pid, float error, int setpoint);


#endif // _PID_H