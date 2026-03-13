#include "pins.h"

void setupPins(){
    pinMode(indicator,OUTPUT);
    
    pinMode(L_LPWM, OUTPUT);
    pinMode(L_RPWM, OUTPUT);
    pinMode(R_LPWM, OUTPUT);
    pinMode(R_RPWM, OUTPUT);

    pinMode(ENCODER_L1,INPUT);
    pinMode(ENCODER_L2,INPUT);
    pinMode(ENCODER_R1,INPUT);
    pinMode(ENCODER_R2,INPUT);


    for (int i = 0; i < 8; i++) {
        pinMode(IRSensorPinsDigital[i], INPUT);
        // pinMode(IRSensorPinsAnalog[i], INPUT);
    }

    pinMode(XSHUT_1, OUTPUT);
    pinMode(XSHUT_2, OUTPUT);
    pinMode(XSHUT_3, OUTPUT);
    pinMode(XSHUT_4, OUTPUT);
    pinMode(XSHUT_5, OUTPUT);
    pinMode(XSHUT_6, OUTPUT);
    pinMode(XSHUT_7, OUTPUT);


    pinMode(COLOR1_S0, OUTPUT);
    pinMode(COLOR1_S1, OUTPUT);
    pinMode(COLOR1_S2, OUTPUT);
    pinMode(COLOR1_S3, OUTPUT);
    pinMode(COLOR1_OUT, INPUT);

    pinMode(COLOR2_S0, OUTPUT);
    pinMode(COLOR2_S1, OUTPUT);
    pinMode(COLOR2_S2, OUTPUT);
    pinMode(COLOR2_S3, OUTPUT);
    pinMode(COLOR2_OUT, INPUT);

    pinMode(GYRO_INTERRUPT_PIN, INPUT);


    pinMode(IRSensorPinLeft,INPUT);
    pinMode(IRSensorPinRight,INPUT);

    pinMode(BTN_UP,    INPUT_PULLUP);
    pinMode(BTN_DOWN,  INPUT_PULLUP);
    pinMode(BTN_START, INPUT_PULLUP);
    pinMode(BTN_STOP,  INPUT_PULLUP);

}