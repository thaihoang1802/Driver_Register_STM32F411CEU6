#ifndef LB_H
#define LB_H

#include <stdint.h>
#include <math.h>

#include "stm32f4xx.h"
#include "GPIO.h"

void config_led13(void);
void Led_13_toggle(void); 
int constrain(int value, int min, int max) ;
double filter_average(int *data , uint8_t step);
double filter_mean_position(int *data , uint8_t step);
void sawp(int *x , int *y);
int map(int value , uint16_t Inmin, uint16_t Inmax,int16_t Outmin, int16_t Outmax);
uint16_t Result_Angle(int position , int angle);
#endif // LB_H
