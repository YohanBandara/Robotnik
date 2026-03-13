#include "lineFollowing.h"
#include "pins.h"
#include "ir.h"
#include "motion.h"



// PID Constants
const float line_Kp = 15;   //digital-15, 20 ,25.   //analoo-5,8,10
const float line_Ki = 0;
const float line_Kd = 5;  //digital-10.             //analog-1,3,5

int line_lastError = 0;
int line_P = 0, line_I = 0, line_D = 0;
int line_PID_value = 0;


// Motor Speed Settings

// const int LINE_MAX_SPEED = 200;
// const int LINE_MIN_SPEED = 0;




void setMotors(int leftSpeed, int rightSpeed) {
    analogWrite(L_LPWM, leftSpeed);
    digitalWrite(L_RPWM, LOW);
    analogWrite(R_RPWM, rightSpeed);
    digitalWrite(R_LPWM, LOW);
}


int calculateError() {
    long weightedSum = 0;
    int activeSensors = 0;
    int weights[8] = {-4, -3, -2, -1, 1, 2, 3, 4};

    for (int i = 0; i < NUM_IR_SENSORS; i++) {
        if (ir_values[i] == 0) {
            weightedSum += weights[i];
            activeSensors++;
        }
    }

    if (activeSensors == 0) {
        return line_lastError;
    }

    return weightedSum;
}







void runLineFollower(int LINE_BASE_SPEED = 100, int tolerance =100 ) {
    readIR();
    int line_error = calculateError();
    // Serial.println(error);

    line_P = line_error;
    line_I = line_I + line_error;
    line_D = line_error - line_lastError;
    line_PID_value = (line_Kp * line_P) + (line_Ki * line_I) + (line_Kd * line_D);
    line_lastError = line_error;

    int leftMotorSpeed = LINE_BASE_SPEED + line_PID_value;
    int rightMotorSpeed = LINE_BASE_SPEED - line_PID_value;

    leftMotorSpeed = constrain(leftMotorSpeed, LINE_BASE_SPEED-tolerance, LINE_BASE_SPEED+tolerance);
    rightMotorSpeed = constrain(rightMotorSpeed, LINE_BASE_SPEED-tolerance, LINE_BASE_SPEED+tolerance);

    setMotors(leftMotorSpeed, rightMotorSpeed);

}





int calculateError2() {
    long weightedSum = 0;
    int activeSensors = 0;
    int weights[10] = {-5,-4, -3, -2, -1, 1, 2, 3, 4, 5};

    for (int i = 0; i <10; i++) {
        if (ir_values2[i] == 0) {
            weightedSum += weights[i];
            activeSensors++;
        }
    }

    if (activeSensors == 0) {
        return line_lastError;
    }

    return weightedSum;
}







void runLineFollower2(int LINE_BASE_SPEED = 100, int tolerance =100 ) {
    readIR2();
    int line_error = calculateError2();
    // Serial.println(error);

    line_P = line_error;
    line_I = line_I + line_error;
    line_D = line_error - line_lastError;
    line_PID_value = (line_Kp * line_P) + (line_Ki * line_I) + (line_Kd * line_D);
    line_lastError = line_error;

    int leftMotorSpeed = LINE_BASE_SPEED + line_PID_value;
    int rightMotorSpeed = LINE_BASE_SPEED - line_PID_value;

    leftMotorSpeed = constrain(leftMotorSpeed, LINE_BASE_SPEED-tolerance, LINE_BASE_SPEED+tolerance);
    rightMotorSpeed = constrain(rightMotorSpeed, LINE_BASE_SPEED-tolerance, LINE_BASE_SPEED+tolerance);

    setMotors(leftMotorSpeed, rightMotorSpeed);

}

