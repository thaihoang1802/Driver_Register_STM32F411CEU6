#include"library.h"
#include "Systick.h"


int constrain(int value, int min, int max)
{
    if (value <= min) {
        value = min;
    } else if (value >= max) {
        value = max;
    }
    return value;
}
void config_led13(void){
    GPIO_Config LED ; 
    LED.GPIOx 	= GPIOC;
    LED.PIN 	= PIN(13);
    LED.MODE 	= MODE_OUTPUT;
    LED.OType 	= OTYPER_PP;
    LED.Speed 	= OSPEEDR_LOW;
    LED.Pull 	= PUPDR_NOPULL;
    GPIO_Init(&LED);
}
void Led_13_toggle(void)
{
    config_led13();
    GPIOC->ODR ^= (1 << 13); // Toggle PC13 (LED)
}

double filter_average(int *data , uint8_t step){
    float sum = 0 ; 
    for (int i = 0 ; i < step ; i++){
        sum+= data[i] ; 
    }
    sum = sum / step ; 
    return sum  ; 
}

double filter_mean_position(int *data , uint8_t step){
    int temp[step]; 
    for (int  i = 0; i < step; i++)
    {
        temp[i] = data[i] ;
    }
    for(int i = 0  ; i < step - 1 ; i++){

        for (int j = i+1; j < step ; j++)
        {
            if (temp[j] < temp[i])
            {
               sawp(&temp[i],&temp[j]);
            }
        }
    }
    int t = (step % 2 == 1) ? step/2 : ((step/2-1) + step/2 )/2.0f ; 
    return temp[t]; 
}

void sawp(int *x , int *y){
    int temp = *x ; 
    *x = *y ; 
    *y = temp;
}
int map(int value , uint16_t Inmin, uint16_t Inmax,int16_t Outmin, int16_t Outmax){
    if (value >= Inmax)
    {
        return Outmax ; 
    }
    else if (value <= Inmin)
    {
       return Outmin ; 
    }
    else{
        return ((value - Inmin)*Outmax)/((Inmax - Inmin) + Outmin); 
    }
}

uint16_t Result_Setpoint(int position , int angle){
    int Setpoint = position + angle ; 
    return (Setpoint >= 360) ? Setpoint-=360 : (Setpoint<0) ?  Setpoint+=360 : Setpoint ;
}




