#include "wallFollowing.h"
#include "pins.h"   
#include "motion.h"
#include "tof.h"
#include "display.h"





const float wall_Kp = 3;
const float wall_Kd = 0.2;               // 0.02 - 0.1
const float wall_Kp_angle = 8;         // 10 * Kp
const int WALL_PID_SPEED_TOLERANCE = 50;  // 20% - 30% from base speed

int baseSpeed=100;
int innerOffset=40;
int outerOffset=60;

float wall_last_error = 0;
const int SMOOTH_LEN = 5;
float front_history[SMOOTH_LEN];
float back_history[SMOOTH_LEN];
int h_index = 0;

void setMotors2(int leftSpeed, int rightSpeed) {
    analogWrite(L_LPWM, leftSpeed);
    digitalWrite(L_RPWM, LOW);
    analogWrite(R_RPWM, rightSpeed);
    digitalWrite(R_LPWM, LOW);
}

void setMotors3(int leftSpeed,int rightSpeed){
  int l=abs(leftSpeed);
  int r=abs(rightSpeed);
  if (leftSpeed>0){analogWrite(L_LPWM, l);analogWrite(L_RPWM, 0);}
  else if(leftSpeed<0){analogWrite(L_LPWM, 0);analogWrite(L_RPWM, l);}
  if (rightSpeed>0){analogWrite(R_LPWM, 0);analogWrite(R_RPWM, r);}
  else if(rightSpeed<0){analogWrite(R_LPWM, r);analogWrite(R_RPWM, 0);}
}


void initWallFollower() {
    float startFront;
    float startBack;
    int error_count=0;
    while(true) {
        readToF();
        startFront = tof_values[0];
        startBack = tof_values[1];
        if (startFront > 0 and startBack > 0) break;
        error_count++;
        if (error_count == 10) {showDisplay("ToF Error Wall Following",1,0,0);}
    }

    for (int i = 0; i < SMOOTH_LEN; i++) {
        front_history[i] = startFront;
        back_history[i] = startBack;
    }
    wall_last_error = 0;
    h_index = 0;
}


float getSmoothed(float newVal, float *history) {
    history[h_index] = newVal;
    float sum = 0;
    for (int i = 0; i < SMOOTH_LEN; i++) sum += history[i];
    float avg = sum / SMOOTH_LEN;
    return avg;
}


void runWallFollower( int targetDistance = 50, char direction='R', String status ="linear") {
    readToF();
    float rawFront;
    float rawBack;
    if (direction == 'L'){rawFront = tof_values[2];rawBack = tof_values[0];}
    else if(direction == 'R'){rawFront = tof_values[5]; rawBack = tof_values[6];}
    if (rawFront <= 0 || rawBack <= 0) return;

    float smoothFront = getSmoothed(rawFront, front_history);
    float smoothBack = getSmoothed(rawBack, back_history);
    h_index = (h_index + 1) % SMOOTH_LEN;


    float currentDistance = smoothFront;
    currentDistance = constrain(currentDistance, 1, 300);
    float wall_error = targetDistance - currentDistance;
    if (abs(wall_error) < 5) wall_error = 0;  //to prevent overshooting stable betwee 10mm

    float angle_error = smoothFront - smoothBack;

    int wall_PID_value = (wall_error * wall_Kp) + ((wall_error - wall_last_error )* wall_Kd) - (angle_error * wall_Kp_angle);
    wall_PID_value= constrain(wall_PID_value, -WALL_PID_SPEED_TOLERANCE, WALL_PID_SPEED_TOLERANCE);
    wall_last_error = wall_error;


    int leftSpeed;
    int rightSpeed;


    if (status=="linear"){
        if (direction == 'L'){
            leftSpeed = baseSpeed + wall_PID_value;    
            rightSpeed = baseSpeed - wall_PID_value;} 
        else if(direction == 'R'){
            leftSpeed = baseSpeed - wall_PID_value;     
            rightSpeed = baseSpeed + wall_PID_value;}  
    }


    if (status == "inner"){
        if (direction == 'L'){
            leftSpeed = baseSpeed + innerOffset + wall_PID_value; 
            rightSpeed = baseSpeed - innerOffset - wall_PID_value;} 
        else if(direction == 'R'){
            leftSpeed = baseSpeed - innerOffset - wall_PID_value;     
            rightSpeed = baseSpeed + innerOffset + wall_PID_value;}  
        }    


    if (status=="outer"){
        if (direction == 'L'){
            leftSpeed = baseSpeed - outerOffset + wall_PID_value;    
            rightSpeed = baseSpeed + outerOffset - wall_PID_value;} 
        else if(direction == 'R'){
            leftSpeed = baseSpeed + outerOffset - wall_PID_value;     
            rightSpeed = baseSpeed - outerOffset + wall_PID_value;}  
    }


    setMotors2(leftSpeed, rightSpeed);
}




void runWallFollowerLinear(int targetDistance = 50,int baseSpeed=100,int tolarance=60, float wall_Kp=10, float wall_Kd=0.2, float wall_Kp_angle=15) {
    readToF();
    float rawFront;
    float rawBack;
    rawFront = tof_values[5]; rawBack = tof_values[6];
    if (rawFront <= 0 || rawBack <= 0) return;

    float smoothFront = getSmoothed(rawFront, front_history);
    float smoothBack = getSmoothed(rawBack, back_history);
    h_index = (h_index + 1) % SMOOTH_LEN;


    float currentDistance = smoothFront;
    currentDistance = constrain(currentDistance, 1, 100);
    float wall_error = targetDistance - currentDistance;
    if (abs(wall_error) < 5) wall_error = 0;  //to prevent overshooting stable betwee 10mm

    float angle_error = smoothFront - smoothBack;

    int wall_PID_value = (wall_error * wall_Kp) + ((wall_error - wall_last_error )* wall_Kd) - (angle_error * wall_Kp_angle);
    wall_PID_value= constrain(wall_PID_value, -WALL_PID_SPEED_TOLERANCE, WALL_PID_SPEED_TOLERANCE);
    wall_last_error = wall_error;

    int leftSpeed = baseSpeed - wall_PID_value;     
    int rightSpeed = baseSpeed + wall_PID_value;

    setMotors2(leftSpeed, rightSpeed);
}





void runWallFollowerInner(int targetDistance = 100,int baseSpeed=90,int innerOffset=90,int tolarance=10, float wall_Kp=5, float wall_Kd=0, float wall_Kp_angle=10) {
    readToF();
    float rawFront;
    float rawBack;
    rawFront = tof_values[5]; rawBack = tof_values[6];
    if (rawFront <= 0 || rawBack <= 0) return;

    float smoothFront = getSmoothed(rawFront, front_history);
    float smoothBack = getSmoothed(rawBack, back_history);
    h_index = (h_index + 1) % SMOOTH_LEN;


    float currentDistance = smoothFront;
    currentDistance = constrain(currentDistance, 1, 300);
    float wall_error = targetDistance - currentDistance;
    if (abs(wall_error) < 5) wall_error = 0;  //to prevent overshooting stable betwee 10mm

    float angle_error = smoothFront - smoothBack;

    int wall_PID_value = (wall_error * wall_Kp) + ((wall_error - wall_last_error )* wall_Kd) - (angle_error * wall_Kp_angle);
    wall_PID_value= constrain(wall_PID_value, -WALL_PID_SPEED_TOLERANCE, WALL_PID_SPEED_TOLERANCE);
    wall_last_error = wall_error;

    int leftSpeed = baseSpeed - innerOffset - wall_PID_value;     
    int rightSpeed = baseSpeed + innerOffset + wall_PID_value;

    setMotors3(leftSpeed, rightSpeed);
}



void runWallFollowerOuter(int targetDistance = 50,int baseSpeed=70,int outerOffset=40,int tolarance=30, float wall_Kp=0, float wall_Kd=0, float wall_Kp_angle=5) {
    readToF();
    float rawFront;
    float rawBack;
    rawFront = tof_values[5]; rawBack = tof_values[6];
    if (rawFront <= 0 || rawBack <= 0) return;

    float smoothFront = getSmoothed(rawFront, front_history);
    float smoothBack = getSmoothed(rawBack, back_history);
    h_index = (h_index + 1) % SMOOTH_LEN;


    float currentDistance = smoothFront;
    currentDistance = constrain(currentDistance, 1, 300);
    float wall_error = targetDistance - currentDistance;
    if (abs(wall_error) < 5) wall_error = 0;  //to prevent overshooting stable betwee 10mm

    float angle_error = smoothFront - smoothBack;

    int wall_PID_value = (wall_error * wall_Kp) + ((wall_error - wall_last_error )* wall_Kd) - (angle_error * wall_Kp_angle);
    wall_PID_value= constrain(wall_PID_value, -WALL_PID_SPEED_TOLERANCE, WALL_PID_SPEED_TOLERANCE);
    wall_last_error = wall_error;

    int leftSpeed = baseSpeed + outerOffset - wall_PID_value;     
    int rightSpeed = baseSpeed - outerOffset + wall_PID_value;

    setMotors2(leftSpeed, rightSpeed);
}











































