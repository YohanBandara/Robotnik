#ifndef WALL_FOLLOWING_H
#define WALL_FOLLOWING_H
#include <Arduino.h>

void initWallFollower();
void runWallFollower(int targetDistance = 50, char direction='R', String status ="linear");
void runWallFollowerLinear( int targetDistance = 50,int baseSpeed=100,int tolarance=60, float wall_Kp=10, float wall_Kd=0.2, float wall_Kp_angle=15);
void runWallFollowerInner(int targetDistance = 100,int baseSpeed=90,int innerOffset=90,int tolarance=10, float wall_Kp=5, float wall_Kd=0, float wall_Kp_angle=10);
void runWallFollowerOuter(int targetDistance = 50,int baseSpeed=70,int outerOffset=40,int tolarance=30, float wall_Kp=0, float wall_Kd=0, float wall_Kp_angle=5);

#endif




