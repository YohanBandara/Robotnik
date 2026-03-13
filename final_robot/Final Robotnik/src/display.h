#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_SSD1306.h>

extern bool display_ok;

void setupDisplay();
void showDisplay(String text, int textSize, int x=0, int y=0);
// void clearDisplay();

extern volatile bool stopFlag;

void runMenuSystem();
typedef void (*TaskFn)();
void registerTasks(TaskFn* taskArray, const char** nameArray, int count);

#endif