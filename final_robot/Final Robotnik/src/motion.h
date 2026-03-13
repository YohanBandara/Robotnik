#ifndef MOTION_H
#define MOTION_H
#include <Arduino.h>

// extern volatile long pulses;
//  pulses;
// void changePulses();
// void resetPulses();
// long getPulses();


// basic motor control
void startMotors(int leftSpeed,int rightSpeed);
void stopMotors();
void rotateRobot(char direction, float target_angle);
void turnUntilLine(char direction);


float distance();
void goDistance(float distance, int speed=100);
void nodeTraversal(int speed=100,int variation=100);
void countTraversal(int target_count=1,int speed=100,int variation=100);
// bool isJunction();

#endif
