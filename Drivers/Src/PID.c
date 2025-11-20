#include "PID.h"

float pid(PID_Config *pid, float error, int setpoint){

	pid->timee = millis();
	pid->dt = (pid->timee - pid->lasttimee) / 1000.f ;
	pid->lasttimee = pid->timee ;

    pid->erro_current = error ; 

    pid->Proportional   = setpoint - error ; 

    pid->Integral      += pid->Integral * pid->dt ; 

    pid->Derivative     = (pid->erro_current - pid->erro_prev) / pid->dt ; 

    pid->erro_prev      = pid->erro_current ; 

    return ((pid->KP * pid->Proportional) + (pid->KI * pid->Integral) + (pid->KD * pid->Derivative)) ;
}
/*

        int sum = 0 ;
        int average = 0 ; 
        for(int i = 0; i < 8; i++)
        {
          data[i] = map_adc_pwm(buffe[i],3800,4010,0,1000) ;
          average+= data[i] * weight[i];
          sum += data[i] ; 
        }
        value = (sum!=0) ? (float)average/sum : 0 ; 

        float out = pid(&PID,value,0);

        printf("\n");
        printf("out: %.2f  value: %.2f \n",out,value);
        printf("\n");
        printf("dt : %.2f timee : %ld lastime : %ld\n",PID.dt,PID.timee,PID.lasttimee);
    

*/