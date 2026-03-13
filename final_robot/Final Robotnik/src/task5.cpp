#include "task5.h"
#include "lineFollowing.h"
#include "ir.h"
#include "motion.h"


void Task5Mo(){
    char arrow_direction[10] = {'R', 'R', 'R', 'L', 'L', 'L', 'R', 'R', 'R', 'R'};
    // int arrow_angle[10] = {0, 90, 30, 240, 15, 70, 40, 80, 50, 15};
    // int arrow_angle2[10]={0, 90, 30, 240, };
    int arrowCount=0;

    while(true){
        runLineFollower(70,70);
        // readIR();
        if (allOnes(ir_values,8)==1){
            // startMotors(70,70);
            if (arrowCount==0 || arrowCount==1 || arrowCount==9 || arrowCount==10)startMotors(70,70);
            // else if (arrowCount==3)startMotors(70,60);
            // else if (arrowCount==4)startMotors(45,105);
            else if (arrowCount==8)startMotors(90,50);
            else if (arrow_direction[arrowCount]=='R')startMotors(80,60);
            else startMotors(60,80);
            while(true){
                // readIR();
                if (isNextNode()){
                    if (arrowCount==10){stopMotors();return;} 
                    goDistance(80,70);
                    // rotateRobot(arrow_direction[arrowCount],arrow_angle[arrowCount]);
                    turnUntilLine(arrow_direction[arrowCount]);
                    arrowCount++;
                    break;}
            }
            // if (arrowCount==11){break;}
        }
    }
}




void Task5(){
    char arrow_direction[10] = {'R', 'R', 'R', 'L', 'L', 'L', 'R', 'R', 'R', 'R'};
    // int arrow_angle[10] = {0, 90, 30, 240, 15, 70, 40, 80, 50, 15};
    // int arrow_angle2[10]={0, 90, 30, 240, };
    int arrowCount=0;

    while(true){
        runLineFollower(70,70);
        // readIR();
        if (allOnes(ir_values,8)==1){
            if (arrowCount==0|| arrowCount==1 || arrowCount==10)startMotors(70,70);
            // else if (arrowCount==3)startMotors(55,85);
            else if (arrowCount==4)startMotors(40,100);
            else if (arrowCount==6)startMotors(70,70);

            else if (arrowCount==9)startMotors(95,55);
            else if (arrow_direction[arrowCount]=='R')startMotors(90,50);
            else startMotors(50,90);
            delay(50);
            // startMotors(70,70);
            while(true){
                // readIR();
                if (isNextNode2()){
                    if (arrowCount==10){stopMotors();return;} 
                    goDistance(80,70);
                    // rotateRobot(arrow_direction[arrowCount],arrow_angle[arrowCount]);
                    turnUntilLine(arrow_direction[arrowCount]);
                    // turnUntilLine('R');
                    arrowCount++;
                    break;}
            }
            // if (arrowCount==11){break;}
        }
    }
}





// void Task5_prev(){
//     char arrow_direction[10] = {'R', 'R', 'R', 'L', 'L', 'L', 'R', 'R', 'R', 'R'};
//     int arrow_angle[10] = {0, 90, 30, 120, 15, 70, 40, 80, 50, 15};
//     int arrowCount=0;

//     while(true){
//         runLineFollower(70,70);
//         readIR();
//         if (allOnes(ir_values,8)==1){
//             if (arrowCount==0)startMotors(70,70);
//             else if (arrow_direction[arrowCount]=='R')startMotors(80,60);
//             else startMotors(60,80);
//             while(true){
//                 readIR();
//                 if (isNextNode()){
//                     goDistance(120,70);
//                     rotateRobot(arrow_direction[arrowCount],arrow_angle[arrowCount]);
//                     arrowCount++;
//                     break;}
//             }
//             if (arrowCount==11)break;
//         }
//     }
// }

