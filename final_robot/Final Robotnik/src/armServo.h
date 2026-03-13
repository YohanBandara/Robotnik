#ifndef ARM_SERVO_H
#define ARM_SERVO_H
#include <Arduino.h>
// #include <Servo.h>

void setupServo();
void boxHorizontalOpen();
void boxHorizontalClose();
void boxVerticalUp();
void boxVerticalDown();


void getBox();
void releaseBox();
void grabBox();

void ballVerticalUp();
void ballVerticalDown();
void ballCylinderIn();
void ballCylinderOut();
void ballHorizontalIn();
void ballHorizontalOut();
// void ballHorizontalAdjust();

void runBallPicker();
void pickBall();
void endBallPicker();

void shoot();

#endif