#include"BUTTON.h"

#define HIGH 1 
#define LOW  0 
#define FALSE LOW 
#define TRURE HIGH

uint8_t Button_check(GPIO_TypeDef *GPIO , uint8_t pin){
    static uint16_t lasttimee   = 0 ;
    static uint8_t  sate        = HIGH;
    static uint8_t  lastsate    = HIGH ; 

    uint32_t t = 10 ; 

    sate = ((GPIO->IDR >> pin ) & 1 ) ; // PUL_UP 

    if (sate != lastsate)
    {
        lasttimee = millis() ; 
    }
    
    if (sate == LOW && ((millis() - lasttimee) > t))
    {
        sate = !sate ; 
    }
    lastsate = sate ; 
    return sate ; 
}
/*
uint8_t Button_check(GPIO_TypeDef *GPIO, uint8_t pin) {
    static uint32_t last_debounce_time = 0;
    static uint8_t last_state = HIGH;
    static uint8_t stable_state = HIGH;

    uint8_t current_state = (GPIO->IDR >> pin) & 1; // Đọc trạng thái chân

    if (current_state != last_state) {
        last_debounce_time = millis(); // Ghi lại thời điểm thay đổi
    }

    if ((millis() - last_debounce_time) > 10) { // debounce 10ms
        // Nếu trạng thái ổn định trong khoảng thời gian
        if (current_state != stable_state) {
            stable_state = current_state;
            if (stable_state == LOW) {
                // Nút được nhấn
                last_state = current_state;
                return 1;
            }
        }
    }

    last_state = current_state;
    return 0;
}
*/