#include "task1.h"
#include "motion.h"
#include "lineFollowing.h"
#include "tof.h"
#include "armServo.h"
#include "color.h"
#include "display.h"

int robotX = 0;
int robotY = 0;
int facing = NORTH;

int grabCount=0;
int prev_color=1;
int next_color=2;

int gridMap[GRID_SIZE][GRID_SIZE] = {UNKNOWN};


int objectIdentify(char direction){
    readToF();
    float lowerToF;
    float upperToF;
    if (direction =='L'){lowerToF=tof_values[0]; upperToF=tof_values[1];}
    else if (direction =='F'){lowerToF=tof_values[2]; upperToF=tof_values[3];}
    else if (direction =='R'){lowerToF=tof_values[4]; upperToF=tof_values[5];}
    if (lowerToF==-1 || upperToF==-1)return;
    
    if (upperToF<250.0 && lowerToF<250.0){
        Serial.println("Obstacle Detected");return 2;
        digitalWrite(13,HIGH);delay(100);digitalWrite(13,LOW);delay(100);
    }
    else if (lowerToF<250.0 && upperToF>250.0){
        Serial.println("Object Detected");return 3;
        digitalWrite(13,HIGH);delay(1000);digitalWrite(13,LOW);delay(1000);
    }
    else{Serial.println("No Object Detected");return 1;
        digitalWrite(13,LOW);
    }
}



void turnTo(int targetDirection) {
    if (facing == targetDirection) return;
    int diff = targetDirection - facing;
    if (diff == 1 || diff == -3) rotateRobot('R', 90);
    else if (diff == 2 || diff == -2) rotateRobot('L', 180);
    else if (diff == 3 || diff == -1) rotateRobot('L', 90);
    facing = targetDirection;
}


void move() {
    nodeTraversal(70,70); 
    //goDistance(70,70); // Center on node
    
    if (facing == NORTH) robotY++;
    else if (facing == EAST)  robotX++;
    else if (facing == SOUTH) robotY--;
    else if (facing == WEST)  robotX--;
    
    // Mark map
    // gridMap[robotX][robotY] = 1; 
    
    // Serial.print("Moved to: "); Serial.print(robotX); Serial.print(","); Serial.println(robotY);
}


// void getNeighborCoords(int dir, int &nx, int &ny) {
//     nx = robotX; ny = robotY;
//     if (dir == NORTH) ny++;
//     else if (dir == EAST)  nx++;
//     else if (dir == SOUTH) ny--;
//     else if (dir == WEST)  nx--;
// }





// void keepBoox(int color){
//     if (robotX==8){
//         turnTo(EAST);
//         goDistance(-1*color_distance[color],70);
//         releaseBox();
//         goDistance(color_distance[color],70);
//         turnTo(NORTH);

        
//     }
//     else {
//         turnTo(WEST);
//         goDistance(color_distance[color]-1500,70);
//         releaseBox();
//         goDistance(1500-color_distance[color],70);
//         turnTo(NORTH);

//     }
// }


// int comeBack(){
//     if (robotX==8){
//         turnTo(SOUTH);
//         for (int i=8;i>0;i--)move();
//         turnTo(WEST);
//         for (int i=8;i>0;i--)move();
//         turnTo(NORTH);
//     }
//     else{
//         turnTo(SOUTH);
//         for (int i=8;i>0;i--)move();
//         turnTo(NORTH);
//     }
// }


// void initialCheck(){
//     for (int i=0;i<8;i++){
//         if (objectIdentify('F')==1)move();
//         else{
//             turnTo(SOUTH);
//             grabBox();
//             turnTo(NORTH);
//             for (int j=i;j<8;j++)move();
//             keepBoox(readColor(1));
//             break;
//         }
//     }
//     comeBack();
//     turnTo(EAST);
//     for (int i=0;i<8;i++){
//         if (objectIdentify('F')==1)move();
//         else{
//             turnTo(WEST);
//             grabBox();
//             for (int j=i;j>0;j--)move();
//             turnTo(NORTH);
//             for (int z=0;z<8;z++)move();
//             keepBoox(readColor(1));
//             comeBack();
//             break;
//         }
//     }
    

// }



///////////



int color_distance[4]={0, 250, 750, 1250};

void deliverBoxLeft(int color){
        for (int i=0;i<8;i++)move();
        turnTo(WEST);
        goDistance(color_distance[color]-1500,70);
        releaseBox();
        goDistance(1500-color_distance[color],70);
        turnTo(SOUTH);
        for (int i=8;i>0;i--)move();
        turnTo(NORTH); 
}


void deliverBoxRight(int color){
    turnTo(EAST);
    for (int i=0;i<8;i++)move();
    turnTo(NORTH);
    for (int i=0;i<8;i++)move();
    turnTo(EAST);
    goDistance(-1*color_distance[color],70);
    releaseBox();
    goDistance(color_distance[color],70);
    turnTo(NORTH);

}


int deliverBox(){
    int color=readColor(1);
    if (grabCount==0){
        deliverBoxLeft(color);
        grabCount++;
        prev_color=color;
        return 0;
    }
    else{
        if (color>prev_color){
            deliverBoxLeft(color);
            turnTo(EAST);
            for (int i=0;i<8;i++)move();
            turnTo(NORTH);
            for (int i=0;i<8;i++)move();
        }
        else {
            deliverBoxRight(color);
        }
        grabCount++;
        next_color=color;
        return 1;
    }

}





void leftLineCheck(){
    for (int i=0;i<8;i++){
        if (objectIdentify('F')==1)move();
        else{
            turnTo(SOUTH);
            grabBox();
            for (int j=i;j>0;j--)move();
            turnTo(NORTH);
            deliverBox();
            return;
        }
    }
    turnTo(SOUTH);
    for (int i=8;i>0;i--)move();
    turnTo(NORTH);
}


int RightLineCheck(){
    for (int i=0;i<8;i++){
        if (objectIdentify('F')==1)move();
        else{
            turnTo(SOUTH);
            grabBox();
            while (robotY>0)move();
            turnTo(WEST);
            while (robotX>0)move();
            turnTo(NORTH);
            if (deliverBox())return 1;
            else {
                turnTo(EAST);
                while (robotX<8)move();
                turnTo(NORTH);
                return 0;
            }
        }
    }
    turnTo(SOUTH);
    while (robotY>0)move();
    turnTo(NORTH);
}





int leftSteps(){
    turnTo(EAST);delay(100);
    while(true){
        if (objectIdentify('F')==2 || robotX==8){
            turnTo(WEST);
            while(robotX>0){move();}
            turnTo(NORTH);
            return 0;
        }
        if (objectIdentify('F')==3){
            turnTo(WEST);delay(200);
            grabBox(); delay(200);
            while(robotX>0){move();}
            turnTo(SOUTH);
            int prev_robotY=robotY;
            while(robotY>0){move();}
            turnTo(NORTH);
            if (deliverBox())return 1;
            else {while(robotY<prev_robotY)move();return 0;}
        }
        move();
    }
}




int RightSteps(){
    turnTo(WEST);delay(100);
    while(true){
        if (objectIdentify('F')==2 || robotX==0){
            turnTo(EAST);
            while(robotX<8){move();}
            turnTo(NORTH);
            return 0;
        }
        if (objectIdentify('F')==3){
            turnTo(EAST);delay(200);
            grabBox(); delay(200);
            while(robotX<8){move();}
            turnTo(SOUTH);
            int prev_robotY=robotY;
            while(robotY>0){move();}
            turnTo(WEST);
            for (int i=8; i>0; i--)move();
            turnTo(NORTH);
            if (deliverBox())return 1;
            else{
                turnTo(EAST);
                while(robotX<8)move();
                turnTo(NORTH);
                while(robotY<prev_robotY)move();
                return 0;
            }
        }
        move();
    }
}






void getOffTask1(){
    turnTo(WEST);
    goDistance(250);
    rotateRobot('R',90);
}



int Task1(){
    leftLineCheck(); delay(1000);
    for (int i=0; i<8; i++){
        if(leftSteps()==1){getOffTask1(); return(6-prev_color-next_color);}
        move();
    }

    turnTo(SOUTH);
    while(robotY>0)move();
    turnTo(EAST);
    while(robotX<8)move();
    turnTo(NORTH);

    if (RightLineCheck()==1){getOffTask1(); return(6-prev_color-next_color);}
    move();

    for (int i=1; i<8; i++){
        if(RightSteps()==1){getOffTask1(); return(6-prev_color-next_color);}
        move();
    }

   getOffTask1();
   return(6-prev_color-next_color);

}



