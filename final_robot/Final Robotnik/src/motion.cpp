#include "motion.h"
#include "pins.h"
#include "encoder.h"
#include "gyro.h"
#include "ir.h"
#include "lineFollowing.h"

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

// volatile long pulses = 0;

// void changePulses(){
//   if (digitalRead(ENCODER_R2) == LOW) {pulses++;} 
//   else {pulses--;}
// }

// void resetPulses() {
//     noInterrupts();pulses = 0;interrupts();
// }

// long getPulses() {
//     noInterrupts();long p = pulses;interrupts();
//     return p;
// }

// float distance(){
//   return (getPulses()*PI*65/224);
// }





void startMotors(int leftSpeed,int rightSpeed){
  int l=abs(leftSpeed);
  int r=abs(rightSpeed);
  if (leftSpeed>0){analogWrite(L_LPWM, l);analogWrite(L_RPWM, 0);}
  else if(leftSpeed<0){analogWrite(L_LPWM, 0);analogWrite(L_RPWM, l);}
  if (rightSpeed>0){analogWrite(R_LPWM, 0);analogWrite(R_RPWM, r);}
  else if(rightSpeed<0){analogWrite(R_LPWM, r);analogWrite(R_RPWM, 0);}
}


void stopMotors() {
  analogWrite(L_LPWM, 0);
  analogWrite(L_RPWM, 0);
  analogWrite(R_LPWM, 0);
  analogWrite(R_RPWM, 0);
}



float time_per_degree = 1400.0 / 90.0; 

void setRotation(char direction, int speed = 175) {
  int rotationOffsetL=0;
  int rotationOffsetR=-10;
  if (direction == 'L') {
    analogWrite(L_LPWM, 0);
    analogWrite(L_RPWM, speed+rotationOffsetL);
    analogWrite(R_LPWM, 0);
    analogWrite(R_RPWM, speed-rotationOffsetL);
    time_per_degree=1400/90.0;
  } else if (direction == 'R') {
    analogWrite(L_LPWM, speed-rotationOffsetR);
    analogWrite(L_RPWM, 0);
    analogWrite(R_LPWM, speed+rotationOffsetR);
    analogWrite(R_RPWM, 0);
    time_per_degree=1000/90.0;
  }
}


// void rotateRobot(char direction, float target_angle) {
//   if (target_angle < 0) target_angle = 360 - target_angle;
//   if (!gyro_ok) {
//     setRotation(direction);
//     delay(time_per_degree * target_angle); 
//     stopMotors();
//     return;
//   }
//   else {
//     flushGyro();
//     readGyro();
//     float previous_angle = currentYaw;
//     float total_turned = 0; 
//     setRotation(direction);

//     while (true) {
//       readGyro();
//       float current_angle = currentYaw;
//       float delta = current_angle - previous_angle;

//       if (delta < -180) {delta += 360; }
//       else if (delta > 180) {delta -= 360;}

//       total_turned += abs(delta);
//       previous_angle = current_angle;

//       if (total_turned >= target_angle) {stopMotors();break;} 
//       delay(10); 
//     }
//   }
// }


void rotateRobot(char direction, float target_angle) {
  // stopMotors();
  // delay(100);
  if (target_angle < 0) target_angle = 360.0 - target_angle;
  
  if (!gyro_ok) {
    setRotation(direction);
    delay(time_per_degree * target_angle); 
    stopMotors();
    return;
  }

  flushGyro(); 
  bool starting_valid = false;
  for(int i=0; i<10; i++) {
     if(updateGyro()) { starting_valid = true; break; }
     delay(5);
  }
  
  float previous_angle = currentYaw;
  float total_turned = 0; 
  
  unsigned long start_time = millis();
  unsigned long timeout = 5000; 

  setRotation(direction);

  while (millis() - start_time < timeout) {
    if (updateGyro()) {
        float current_angle = currentYaw;
        float delta = current_angle - previous_angle;

        if (delta < -180) delta += 360;
        else if (delta > 180) delta -= 360;

        total_turned += abs(delta);
        previous_angle = current_angle;

        if (total_turned >= target_angle) {
            stopMotors();
            return;
        }
    }
  }

  stopMotors();
}






void turnUntilLine(char direction){
  setRotation(direction);
  while(true){
    readIR();
    if (ir_values[2]==0 && ir_values[3]==0 && ir_values[4]==0){stopMotors();return;}
    if (ir_values[3]==0 && ir_values[3]==0 && ir_values[5]==0){stopMotors();return;}
  }
}


void turnUntilLine2(char direction){
  rotateRobot(direction,45);
  setRotation(direction);
  while(true){
    readIR();
    if (ir_values[2]==0 && ir_values[3]==0 && ir_values[4]==0){stopMotors();return;}
    if (ir_values[3]==0 && ir_values[3]==0 && ir_values[5]==0){stopMotors();return;}
  }
}





// float time_per_degree=700.0/90.0;

// void rotateRobot(char direction, float target_angle) {
//   if (!imu_ok){
//     setRotation(direction);
//     delay(time_per_degree*target_angle); 
//     stopMotors();
//   }
//   else{
//   float initial_x = readGyro();
//   setRotation(direction);
//   while (true) {
//     float current_x = readGyro();
//     float angle_turned;
    
//     if (direction == 'L') {
//       angle_turned = initial_x - current_x;
//       if (angle_turned < 0) angle_turned += 360;
//     } else if (direction == 'R') {
//       angle_turned = current_x - initial_x;
//       if (angle_turned < 0) angle_turned += 360;
//     }
    
//     if (angle_turned >= target_angle) {
//       stopMotors();
//       break;
//     }
//     delay(10); // Small delay to prevent overwhelming the IMU
//   }}
// }




int ENCODER_COUNT=224;
float CIR=PI*65; //mm

void goDistance(float distance, int speed=100){
    float rotations=abs(distance)/CIR;
    float target_pulses=rotations*(float)ENCODER_COUNT;
    resetPulses();
    if (distance>0)startMotors(speed,speed);
    else if (distance<0)startMotors(-speed,-speed);
    while(true){
      long current_pulses = getPulses();
        Serial.println(current_pulses);
        if (abs(current_pulses)>target_pulses){stopMotors();return;}
    }
}

// bool isJunction(){
//     bool isLeft=true;
//     bool isRight=true;
//     for(int i=0;i<5;i++){
//         if (ir_values[i]==1){isLeft=false;break;}
//     }
//     for(int i=3;i<8;i++){
//         if (ir_values[i]==1){isRight=false;break;}
//     }
//     return (isRight || isLeft);
// }



bool isJunction2(){
    bool isLeft=true;
    bool isRight=true;
    for(int i=0;i<5;i++){
        if (ir_values[i]==1){isLeft=false;break;}
    }
    for(int i=3;i<8;i++){
        if (ir_values[i]==1){isRight=false;break;}
    }
    return (isRight || isLeft);
}


void nodeTraversal(int speed=100,int variation=100){
  while(true){
      runLineFollower(speed,variation);
      if (isJunction()){
          goDistance(120,speed);
          return;
      }
  }
}

  
    
void countTraversal(int target_count=1,int speed=100,int variation=100){
  int count=0;
  resetPulses();

  while(true){ 
    runLineFollower(speed,variation);
    if(isJunction() && (getPulses())>50){      //counting
        count++;
        resetPulses();
    }
    if (count==target_count){
        goDistance(120,speed);
        return;
    }
  }

}



