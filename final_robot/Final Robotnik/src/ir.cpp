#include "ir.h"
#include "pins.h" 
#include "gyro.h"
#include "motion.h"

const int NUM_IR_SENSORS = 8;
int ir_values[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int ir_values2[10]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int ir_thresholds[8] = {218,249,189,197,208,229,235,232};//{0, 0, 0, 0, 0, 0, 0, 0};
bool isCalibrated = false;



// void calibrateIR() {
//     int min_vals[8];
//     int max_vals[8];

//     for (int i = 0; i < NUM_IR_SENSORS; i++) {
//         min_vals[i] = 1023;
//         max_vals[i] = 0;
//     }

//     Serial.println("Calibrating... SWIPE ROBOT OVER LINE!");

//     unsigned long startTime = millis();
//     while (millis() - startTime < 5000) {
//         for (int i = 0; i < NUM_IR_SENSORS; i++) {
//             int val = analogRead(IRSensorPinsAnalog[i]);
            
//             if (val > max_vals[i]) max_vals[i] = val; // Found new Black
//             if (val < min_vals[i]) min_vals[i] = val; // Found new White
//         }
//         delay(5); 
//     }

//     Serial.println("Calibration Done. Thresholds:");
//     for (int i = 0; i < NUM_IR_SENSORS; i++) {
//         ir_thresholds[i] = (min_vals[i] + max_vals[i]) / 2;
        
//         Serial.print(ir_thresholds[i]);
//         Serial.print("\t");
//     }
//     isCalibrated = true;
//     Serial.println();
// }


// // void setupCalibrateIR() {
// //     float initial_orientation_x=readGyro();
// //     startMotors(150,-150);
// //     calibrateIR();
// //     stopMotors();
// //     float final_orientation_x=readGyro();
// //     float difference_orientation_x = initial_orientation_x - final_orientation_x ;
// //     if (initial_orientation_x > final_orientation_x ) rotateRobot('R', difference_orientation_x);
// //     else rotateRobot('L', -difference_orientation_x);
// // }


// void readAnalogIR() {
//     for (int i = 0; i < NUM_IR_SENSORS; i++) {
//         int val = analogRead(IRSensorPinsAnalog[i]);
        
//         if (val > ir_thresholds[i]) ir_values[i] = 1;
//         else ir_values[i] = 0;
//     }
// }




void readDigitalIR() {
    for (int i = 0; i < NUM_IR_SENSORS; i++) {
        ir_values[i] = digitalRead(IRSensorPinsDigital[i]);
    }
}


void readIR() {
    // if (isCalibrated) readAnalogIR();
    // else readDigitalIR();
    readDigitalIR();
}


void readIR2(){
    ir_values2[0]=digitalRead(IRSensorPinLeft);
    for (int i = 1; i < 9; i++) {
        ir_values2[i] = digitalRead(IRSensorPinsDigital[i-1]);
    }
    ir_values2[9]=digitalRead(IRSensorPinRight);
}








bool allZeros(int arr[], int size){
    for (int i=0;i<size;i++){
        if (arr[i]==1)return 0;
    }
    return 1;
}

bool allOnes(int arr[], int size){
    for (int i=0;i<size;i++){
        if (arr[i]==0)return 0;
    }
    return 1;
}


bool isNextNode(){
    readIR();
    int count=0;
    for (int i=0;i<8;i++){
        if (ir_values[i]==0){count++;}
        else{count=0;}
        if (count>1) return 1;
    }
    return 0;
}


bool isNextNode2(){
    readIR2();
    int count=0;
    for (int i=1;i<9;i++){
        if (ir_values2[i]==0){count++;}
        else{count=0;}
        if (count>1) return 1;
    }
    if (!ir_values2[0])return 1;
    if (!ir_values2[9])return 1;

    return 0;
}



bool isJunction(){
    bool isLeft=true;
    bool isRight=true;
    // readIR();
    for(int i=0;i<5;i++){
        if (ir_values[i]==1){isLeft=false;break;}
    }
    for(int i=3;i<8;i++){
        if (ir_values[i]==1){isRight=false;break;}
    }
    if (digitalRead(IRSensorPinLeft))isLeft=false;
    if (digitalRead(IRSensorPinRight))isRight=false;
    return (isRight || isLeft);
}


bool isWhiteLine(){
    readIR();
    int count=0;
    for (int i=0;i<8;i++){
        if (ir_values[i]==0){count++;}
        if (count>6) return 1;
    }
    return 0;
}