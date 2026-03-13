#include "task2.h"
#include "lineFollowing.h"
#include "ir.h"
#include "motion.h"
#include "encoder.h"
#include"gyro.h"



void ramp(){
    // readGyro();
    updateGyro();
    if (abs(currentPitch)<5)startMotors(70,70);
    else if(currentPitch>5)startMotors(120,120);
    else if(currentPitch<-5)startMotors(50,50);
}


bool ifInArray(int arr[], int size, int element) {
    for(int i = 0; i < size; i++) {
        if(arr[i] == element) return true;
    }
    return false;
}




void Task2(){
    // left 
    float initialYawT2;
    float finalYawT2;
    float difYawT2;
    int task2Count=0;
    goDistance(50,50);
    while(true){
        runLineFollower(50,50);
        if (task2Count==2){updateGyro(); initialYawT2=currentYaw;}
        task2Count++;
        if (isWhiteLine()){stopMotors();delay(500);break;}
        if (allOnes(ir_values,8)==1){
            resetPulses();
            while(true){
                readIR();
                if (isNextNode()){
                    break;}
                if (distance()>120){
                    goDistance(-100,50);rotateRobot('L',15);resetPulses();startMotors(50,50);
                }
            }
        }
    }
    finalYawT2=initialYawT2+180;
    if (finalYawT2>360)finalYawT2-=360;
    updateGyro();
    difYawT2=currentYaw-finalYawT2;
    if (difYawT2<0)difYawT2+=360;
    rotateRobot('L',difYawT2-5);


    // pushing the ramp
    goDistance(400,50);delay(1000);
    goDistance(-280,50);delay(1000);
    rotateRobot('L',180);


    // right side of the left side one
    goDistance(50,50);
    while(true){
        runLineFollower(50,50);
        if (isWhiteLine()){stopMotors();delay(500);break;}
        if (allOnes(ir_values,8)==1){
            resetPulses();
            while(true){
                readIR();
                if (isNextNode()){
                    break;}
                if (distance()>120){
                    goDistance(-100,50);rotateRobot('R',15);resetPulses();startMotors(50,50);
                }
            }
        }
    }



    goDistance(-275,70);
    rotateRobot('R',90);

    //ramp
    int countAfterRamp=0;
    int lineStatus=0;
    while(true){
        ramp();
        readIR();
        if (isJunction() and lineStatus==0){countAfterRamp++;lineStatus=1;}
        if (allOnes(ir_values,8))lineStatus=0;
        if (countAfterRamp==2){stopMotors();break;}
    }
    delay(500);

}









// void Task2Mo(){
//     // char arrow_direction[10] = {'R', 'R', 'R', 'L', 'L', 'L', 'R', 'R', 'R', 'R'};
//     // int arrow_angle[10] = {0, 90, 30, 120, 15, 70, 40, 80, 50, 15};
//     int dashArray[5]={7, 8, 9, 13, 14};
//     int dashCount=0;

//     while(true){
//         runLineFollower(50,50);
//         // readIR();
//         if (dashCount==14 && allZeros(ir_values,8)==1){stopMotors();break;}
//         if (allOnes(ir_values,8)==1){
//             if (ifInArray(dashArray,5,dashCount))startMotors(-10,120);
//             else startMotors(50,50);
//             // startMotors(50,50);
//             while(true){
//                 readIR();
//                 if (isNextNode()){
//                     //  goDistance(10,70);
//                     // turnUntilLine('L');
//                     dashCount++;
//                     break;}
//             }
//         }
//     }
// }




// void Task2Mo2(){
//     // char arrow_direction[10] = {'R', 'R', 'R', 'L', 'L', 'L', 'R', 'R', 'R', 'R'};
//     // int arrow_angle[10] = {0, 90, 30, 120, 15, 70, 40, 80, 50, 15};
//     int dashArray[5]={7, 8, 9, 13, 14};
//     int dashCount=0;

//     while(true){
//         runLineFollower(50,50);
//         // readIR();
//         if (dashCount==14 && allZeros(ir_values,8)==1){stopMotors();break;}
//         if (allOnes(ir_values,8)==1){
//             if (ifInArray(dashArray,5,dashCount))startMotors(-10,120);
//             // else startMotors(50,50);
//             // startMotors(50,50);
//             while(true){
//                 readIR();
//                 if (isNextNode()){
//                      goDistance(10,50);
//                     turnUntilLine('L');
//                     dashCount++;
//                     break;}
//             }
//         }

//     }

// }
