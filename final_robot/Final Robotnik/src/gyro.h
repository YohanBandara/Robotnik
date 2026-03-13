// #ifndef GYRO_H
// #define GYRO_H
// #include <Arduino.h>

// // extern bool gyro_ok;

// // void setupGyro();
// // float readGyro();
// // void flushGyro();

// #endif




#ifndef GYRO_H
#define GYRO_H
#include <Arduino.h>

extern bool gyro_ok;
extern float currentYaw; 
extern float currentPitch;


void setupGyro();
// float readGyro(); 
bool updateGyro();
void flushGyro();

// float readPitch();

#endif