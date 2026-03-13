#include "task6.h"
#include "tof.h"
#include "wallFollowing.h"
#include"motion.h"
#include "encoder.h"
#include "ir.h"
#include "armServo.h"

void Task6(){


    delay(1000);
    goDistance(200);    //here
    readToF();
    while(tof_values[2]>50){
        runWallFollowerLinear(50,70);delay(10);
    }
    stopMotors();delay(500);
    rotateRobot('R',90);delay(500);

    // // goDistance().       //here
    // resetPulses();
    // while(distance()<500){        //here
    //     runWallFollowerLinear(50,70);delay(10);
    //     //hidden task



    // }
    // stopMotors();


    // //pendulum
    // int ready=0;
    // while(true){
    //     readToF();
    //     if (tof_values[2]<200)ready=1;
    //     if (tof_values[2]>200 and ready){break;} //here
    // }
    // delay(1000);
    // goDistance(500,200);
    

    while(!isWhiteLine()){runWallFollowerLinear(50,70);delay(10);}
    goDistance(200,70);
    rotateRobot('R',90);


    //ball shooter
    boxHorizontalOpen();
    shoot();


}