#include "armServo.h"
#include "pins.h"
#include "motion.h"
#include "sharpIr.h"
#include "encoder.h"
#include "lineFollowing.h"
// #include <Arduino.h>
#include <Servo.h>

Servo boxVertical;     // 100 - 15
Servo boxHorizontal;   // 142 - 100
Servo ballVertical;    // 0 - 180
Servo ballHorizontal;  // 0 -180
Servo ballCylinder;    // 0 - 160

Servo esc1;
Servo esc2; 


int boxVerticalStatus=0;      //0-up  1-down
int boxHorizontalStatus=0;    //0-closed  1-open
int ballVerticalStatus=0;     //0-up 1-down
int ballCylinderStatus=0;     //0-in 1-out
int ballHorizontalStatus=0;   //0-in 180-out
int ballHorizontalDiscreteStatus=180;   //0-in 180-out


void setupServo(){
    boxVertical.attach(BOX_SERVO_VERTICAL_PIN);boxVertical.write(70);
    boxHorizontal.attach(BOX_SERVO_HORIZONTAL_PIN);boxHorizontal.write(160);

    ballVertical.attach(BALL_SERVO_VERTICAL_PIN);ballVertical.write(180);
    ballHorizontal.attach(BALL_SERVO_HORIZONTAL_PIN);ballHorizontal.write(180);
    ballCylinder.attach(BALL_SERVO_CYLINDER_PIN);ballCylinder.write(180);

    esc1.attach(46);
    esc2.attach(13);

}



//box
void boxVerticalUp(){
    if (boxVerticalStatus==0){return;}
    else{
       for (int i=5;i<=100;i++){
           boxVertical.write(i);
           delay(5);
       }
       boxVerticalStatus=0;
    }
}

void boxVerticalDown(){
    if (boxVerticalStatus==1){return;}
    else{
       for (int i=100;i>=5;i--){
           boxVertical.write(i);
           delay(5);
       }
       boxVerticalStatus=1;
    }
}

void boxHorizontalClose(){
    if (boxHorizontalStatus==0){return;}
    else{
       for (int i=100;i<=160;i++){
           boxHorizontal.write(i);
           delay(5);
       }
       boxHorizontalStatus=0;
    }
}

void boxHorizontalOpen(){
    if (boxHorizontalStatus==1){return;}
    else{
       for (int i=160;i>=100;i--){
           boxHorizontal.write(i);
           delay(5);
       }
       boxHorizontalStatus=1;
    }
}

void getBox(){boxHorizontalOpen();boxVerticalDown();boxHorizontalClose();}

void grabBox(){
    resetPulses();
    while(distance()<200)runLineFollower(50,50);
    boxHorizontalOpen();boxVerticalDown();
    goDistance(-450,50);
    boxHorizontalClose();
    goDistance(100,50);
}

void releaseBox(){boxVerticalUp();}








// ball
void ballVerticalUp(){
    if (ballVerticalStatus==0){return;}
    else{
       for (int i=0;i<=0;i++){
           ballVertical.write(i);
           delay(10);
       }
       ballVerticalStatus=0;
    }
}


void ballVerticalDown(){
    if (ballVerticalStatus==1){return;}
    else{
       for (int i=180;i>=0;i--){
           ballVertical.write(i);
           delay(10);
       }
       ballVerticalStatus=1;
    }
}



void ballCylinderIn(){
    if (ballCylinderStatus==0){return;}
    else{
       for (int i=0;i<=180;i++){
           ballCylinder.write(i);
           delay(5);
       }
       ballCylinderStatus=0;
    }
}

void ballCylinderOut(){
    if (ballCylinderStatus==1){return;}
    else{
       for (int i=180;i>=0;i--){
           ballCylinder.write(i);
           delay(5);
       }
       ballCylinderStatus=1;
    }
}


void ballHorizontalIn(){
    if (ballHorizontalStatus==0){return;}
    else{
       for (int i=0;i<=180;i++){
           ballHorizontal.write(i);
           delay(5);
       }
       ballHorizontalStatus=0;
    }
}


void ballHorizontalOut(){
    if (ballHorizontalStatus==1){return;}
    else{
       for (int i=180;i>=0;i--){
           ballHorizontal.write(i);
           delay(5);
       }
       ballHorizontalStatus=1;
    }
}




// void ballHorizontalIn(){
//     if (ballHorizontalStatus==180){return;}
//     else{
//        for (int i=ballHorizontalStatus;i<=180;i++){
//            ballHorizontal.write(i);
//            delay(5);
//        }
//        ballHorizontalStatus=180;
//     }
// }


// void ballHorizontalOut(){
//     if (ballHorizontalStatus==0){return;}
//     else{
//        for (int i=ballHorizontalStatus;i>=0;i--){
//            ballHorizontal.write(i);
//            delay(5);
//        }
//        ballHorizontalStatus=0;
//     }
// }



// void ballHorizontalAdjust(){
//     float goDistance=readSharpIR()-100;
//     goDistance=constrain(goDistance,0,40);
//     int goPhase=180-goDistance*180/40;
//     if (goPhase>ballHorizontalStatus){
//         for (int i=ballHorizontalStatus;i<=goPhase;i++){ballHorizontal.write(i);delay(5);}
//     }
//     else {
//         for (int i=ballHorizontalStatus;i>=goPhase;i--){ballHorizontal.write(i);delay(5);}
//     }
//     ballHorizontalStatus=goPhase;
// }





void runBallPicker(){
    ballCylinderOut();delay(500);
    // ballHorizontalOut();delay(500);
}

void pickBall(){
    ballHorizontalOut();delay(500);
    ballVerticalDown();delay(500);
    ballVerticalUp();delay(500);
    ballHorizontalIn();delay(500);

}


void endBallPicker(){
    // ballHorizontalIn();delay(500);
    ballCylinderIn();delay(500);
}







void shoot(){
  esc1.writeMicroseconds(2000);
  esc2.writeMicroseconds(2000);

  delay(5000);

  esc1.writeMicroseconds(1000);
  esc2.writeMicroseconds(1000);

  while (true) {
    esc1.writeMicroseconds(1000);
    esc2.writeMicroseconds(1000);
    delay(20);
  }

}





