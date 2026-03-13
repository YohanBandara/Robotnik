#ifndef COLOR_H
#define COLOR_H

#include <Arduino.h>

extern int color;

void setupColor();
int readColor(int color_sensor_number);
void calibrateColor();

#endif