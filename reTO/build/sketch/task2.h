#line 1 "/home/pop-os/Documents/reTO/task2.h"
#include <Arduino.h>

void task2(){
    enum class Task2States{
        INIT,
        WAIT_TO_TOGGLE_LED
    };
    static Task2States task2State = Task2States::INIT;
    static uint32_t lasTime;
    static constexpr uint32_t INTERVAL = 500;
    static constexpr uint8_t ledRed = 14;
    static bool ledStatus = false;

    switch(task2State){
        case Task2States::INIT:{
            pinMode(ledRed,OUTPUT);
            lasTime = millis();
            task2State = Task2States::WAIT_TO_TOGGLE_LED;
            break;
        }

        case Task2States::WAIT_TO_TOGGLE_LED:{
            // evento 1:
            uint32_t currentTime = millis();
            if( (currentTime - lasTime) >= INTERVAL ){
                lasTime = currentTime;
                digitalWrite(ledRed,ledStatus);
                ledStatus = !ledStatus;
            }
            break;
        }

        default:{
            break;
        }
    }

}