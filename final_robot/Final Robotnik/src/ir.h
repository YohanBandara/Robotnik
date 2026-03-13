#ifndef IR_H
#define IR_H
#include <Arduino.h>

extern const int NUM_IR_SENSORS;
extern int ir_values[8];
extern int ir_values2[10];

void readIR();
void readIR2();
void calibrateIR();
// void setupCalibrateIR();

bool allZeros(int arr[], int size);
bool allOnes(int arr[], int size);
bool isNextNode();
bool isNextNode2();
bool isJunction();
bool isWhiteLine();

#endif

