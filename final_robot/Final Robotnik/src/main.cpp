#include <Arduino.h>
#include <Wire.h> 
#include "pins.h"
#include "lineFollowing.h"
#include "wallFollowing.h"
#include "encoder.h"
#include "motion.h"
#include "gyro.h"
#include "ir.h"
#include "tof.h"
#include "display.h"
#include "color.h"
// #include <Servo.h> 
#include "armServo.h"
#include "task1.h"
#include "task2.h"
#include "task3.h"
#include "task4.h"
#include "task5.h"
#include "task6.h"










void setup() {
    Wire.begin();
    Serial.begin(9600);
    attachInterrupt(digitalPinToInterrupt(ENCODER_R1),changePulses ,RISING);
    setupPins();
    setupDisplay();
    // showDisplay("Initializing...",2,0,0);
    Serial.println("Pins and Display Initialized");
    setupGyro();
    // delay(5000);
    // Serial.println("Gyro Initialized");
    // showDisplay("Gyro Initialized",2,0,30);
    setupToF();
    // showDisplay("ToF Initialized",2,0,30);
    // setupCalibrateIR();
    // Serial.println(gyro_ok);
    Serial.println("Setup Complete");
    // showDisplay("Moda ",3,0,0);
    // showDisplay("Kariya",3,0,30);
    // initWallFollower();
    setupServo();
    // grabBox();
    setupColor();
    // calibrateColor();






    // startMotors(110,30);
    // Serial.println(gyro_ok);
    // delay(5000);
    // nodeTraversal(70,70);
    // goDistance(70,70);
    // rotateRobot('R',90);delay(1000);
    // rotateRobot('L',180);
    // resetPulses();
    // while(distance()<250)runLineFollower(50,50);
    // goDistance(-300,50);
    // Task5();
    // Task5Mo();

    int color=Task1();
    Task2();
    int count=Task3();
    Task4(color,2);
    Task5();
    Task6();
    
    // turnUntilLine('L');

    // startMotors(100,100);



    // for (int i=0;i<2;i++){
    //     nodeTraversal(70,70);
    // }
    // rotateRobot('R',90);delay(500);
    // nodeTraversal(70,70);nodeTraversal(70,70);
  
}

  

void loop() {
    // Serial.println(digitalRead(IRSensorPinLeft));delay(500);
    // readToF();delay(500);
    // runWallFollowerLinear(100,70);delay(10);
    // runWallFollowerInner(100,70,80,5,15,20);
    // updateGyro();
    // Serial.println(currentPitch);
    // delay(100);
    // runLineFollower();delay(20);
    // //ramp
    // ramp();
    // readIR();
    // if(isJunction()){
    //     count++;
    //     if (count==3){stopMotors();while(true);}
    // }
    // delay(20);


    // //object
    // objectIdentify('F');
    // delay(100);

    //colorSensing
    // readColor(1);delay(500);


    // Serial.println(getPulses());
    // objectIdentify('F');
    // delay(50);

    // readGyro();
    // Serial.print(currentYaw);Serial.print("  ");Serial.println(currentPitch);
    // delay(500);
    
    //Line follower 
    // runLineFollower();
    // delay(10);

    // //wall following
    // runWallFollowerLinear(100,70);
    // delay(10);


    // startMotors(130,10);
    // runWallFollowerLinear(50,70);
    // runWallFollowerInner();
    // startMotors(-10,190);
    // delay(10);
    // runLineFollower(70,70);delay(10);
    // for (int i=0;i<3;i++){nodeTraversal();}
    // while(true);
    // delay(10);
    // for (int i=0;i<7;i++){
    //     Serial.print(ir_thres[i]);Serial.print(" ");
    // }
    // Serial.println();
    // delay(500);

}



















































// // #include <Arduino.h>
// // #include <Wire.h>

// // #include "pins.h"
// // #include "display.h"
// // #include "motion.h"
// // #include "gyro.h"
// // #include "tof.h"
// // #include "armServo.h"
// // #include "color.h"

// // // Include Tasks
// // #include "task1.h"
// // #include "task2.h"
// // #include "task3.h"
// // #include "task4.h"
// // #include "task5.h"
// // #include "task6.h"

// // --- TASK WRAPPERS ---
// // The menu expects "void function(void)", so we wrap your tasks here.

// void wrap_Task1() {
//     // Task 1 returns a result (missing balls), we can store it if needed
//     // For now just run it.
//     Task1(); 
// }

// void wrap_Task2() {
//     Task2();
// }

// void wrap_Task3() {
//     // Task 3 returns sphere count.
//     int spheres = Task3();
//     // You might want to save 'spheres' to a global variable for Task 4
//     // extern int globalSphereCount; 
//     // globalSphereCount = spheres;
// }

// void wrap_Task4() {
//     // Task 4 needs arguments. Defaulting for now.
//     // Ideally pass the result from Task 3 here.
//     Task4(1, 2); // Color 1, Count 2 (Example)
// }

// void wrap_Task5() {
//     Task5();
// }

// void wrap_Task6() {
//     Task6();
// }

// // --- MENU ARRAYS ---
// const int TASK_COUNT = 6;

// TaskFn taskList[TASK_COUNT] = {
//     wrap_Task1,
//     wrap_Task2,
//     wrap_Task3,
//     wrap_Task4,
//     wrap_Task5,
//     wrap_Task6
// };

// const char* taskNames[TASK_COUNT] = {
//     "1. Labyrinth",
//     "2. Ramp",
//     "3. Barcode",
//     "4. Fortress",
//     "5. Wall Whisper",
//     "6. Shooting"
// };

// void setup() {
//     Serial.begin(9600);
    
//     // Hardware Setup
//     setupPins();
//     setupServo();
//     setupColor();
    
//     Wire.begin();
//     Wire.setClock(400000);

//     setupDisplay(); 
//     showDisplay("Booting...", 2, 10, 50);

//     // Sensor Setup
//     setupGyro();
//     setupToF(); // Remembers to reset XSHUTs
    
//     // Register Tasks with Menu
//     registerTasks(taskList, taskNames, TASK_COUNT);
    
//     // Ready
//     showDisplay("Ready", 2, 30, 50);
//     delay(1000);
    
//     // Draw Initial Menu
//     // We need to call this once to show the UI
//     // But since runMenuSystem handles state, just setting state is enough.
//     // Note: To force a draw, we can rely on the loop.
// }

// void loop() {
//     // The loop just runs the menu system continuously.
//     // The menu system handles buttons and calls the tasks.
//     runMenuSystem();
// }


































































































// bool allZeros(int arr[], int size){
//     for (int i=0;i<size;i++){
//         if (arr[i]==1)return 0;
//     }
//     return 1;
// }

// bool allOnes(int arr[], int size){
//     for (int i=0;i<size;i++){
//         if (arr[i]==0)return 0;
//     }
//     return 1;
// }


// bool isNextNode(){
//     readIR();
//     int count=0;
//     for (int i=0;i<8;i++){
//         if (ir_values[i]==0){count++;}
//         else{count=0;}
//         if (count>1) return 1;
//     }
//     return 0;
// }



// void Task5(){
//     char arrow_direction[10] = {'R', 'R', 'R', 'R', 'L', 'L', 'R', 'R', 'R', 'R'};
//     // int arrow_angle[10] = {0, 90, 30, 240, 15, 70, 40, 80, 50, 15};
//     // int arrow_angle2[10]={0, 90, 30, 240, };
//     int arrowCount=0;

//     while(true){
//         runLineFollower(70,70);
//         readIR();
//         if (allOnes(ir_values,8)==1){
//             if (arrowCount==0 || arrowCount==9 || arrowCount==10)startMotors(70,70);
//             else if (arrowCount==3)startMotors(55,85);
//             else if (arrowCount==8)startMotors(90,50);
//             else if (arrow_direction[arrowCount]=='R')startMotors(85,55);
//             else startMotors(65,85);
//             while(true){
//                 readIR();
//                 if (isNextNode()){
//                     if (arrowCount==10){stopMotors();return;} 
//                     goDistance(120,70);
//                     // rotateRobot(arrow_direction[arrowCount],arrow_angle[arrowCount]);
//                     turnUntilLine(arrow_direction[arrowCount]);
//                     arrowCount++;
//                     break;}
//             }
//             // if (arrowCount==11){break;}
//         }

//     }

// }








// bool ifInArray(int arr[], int size, int element) {
//     for(int i = 0; i < size; i++) {
//         if(arr[i] == element) return true;
//     }
//     return false;
// }

// void Task5(){
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




// void Task2Mod(){
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





// void Task2Mo2(){
//         // char arrow_direction[10] = {'R', 'R', 'R', 'L', 'L', 'L', 'R', 'R', 'R', 'R'};
//     // int arrow_angle[10] = {0, 90, 30, 120, 15, 70, 40, 80, 50, 15};
//     // int dashArray[5]={7, 8, 9, 13, 14};
//     // int dashCount=0;

//     while(true){
//         runLineFollower(70,100);
//         // readIR();
//         // if (dashCount==14 && allZeros(ir_values,8)==1){stopMotors();break;}
//         if (allOnes(ir_values,8)==1){
//             // if (ifInArray(dashArray,5,dashCount))startMotors(-10,120);
//             // else startMotors(50,50);
//             startMotors(50,100);
//             resetPulses();
//             while(true){
//                 readIR();
//                 if (isNextNode()){
//                     //  goDistance(10,50);
//                     // turnUntilLine('L');
//                     // dashCount++;
//                     break;}
//                 if (distance()>120){
//                     goDistance(-100,100);rotateRobot('L',15);resetPulses();
//                 }
//             }
//         }

//     }
// }




// void Task3(){
//     goDistance(120,70);delay(100);
//     rotateRobot('R',90);delay(100);
//     goDistance(250,70);delay(100);
//     rotateRobot('L',90);delay(100);
//     updateGyro();
//     float initialYaw=currentYaw;
//     float finalYaw=initialYaw+180; if(finalYaw>360)finalYaw-=360;

//     // startMotors(70,70);
//     // while(abs(currentYaw-finalYaw)>10){
//     //     runWallFollowerLinear(100,70);
//     //     updateGyro();
//     // }
//     // runWallFollowerLinear(100,70);delay(100);

//     // while(true){
//     //     runWallFollowerLinear(100,70);delay(10);
//     // }
//     // stopMotors();

//     readToF();
//     while(tof_values[6]<500){
//         runWallFollowerLinear(100,70);
//     }
//     // startMotors(115,25);

//     // updateGyro();
//     // while(abs(finalYaw-currentYaw)>5){
//     //     updateGyro();
//     // }
//     // while(tof_values[6]<400){
//     //     readToF();
//     // }
//     // // startMotors(115,25);

//     goDistance(100,70);delay(500);
//     rotateRobot('R',90);delay(500);
//     goDistance(400);delay(500);
//     rotateRobot('R',60);delay(500);
//     goDistance(150,70);
//     // stopMotors();





//     // rotateRobot('R',90);
//     // goDistance(200);
//     // rotateRobot('R',90);
//     // runWallFollowerInner();
//     readToF();
//     while(tof_values[6]<500){
//         runWallFollowerInner(100,70,80,5,15,20);
//     }
//     goDistance(100,70);

//     // rotateRobot('R',90);
//     // goDistance(200);
//     // rotateRobot('R',90);
    
// }

 






// void ramp(){
//     // readGyro();
//     updateGyro();
//     if (abs(currentPitch)<5)startMotors(70,70);
//     else if(currentPitch>5)startMotors(120,120);
//     else if(currentPitch<-5)startMotors(50,50);
// }















// void I2CScan(){
//     byte error, address;
//     int nDevices;

//     Serial.println("I2C Scanning...");

//     nDevices = 0;
//     for(address = 1; address < 127; address++ ) {

//         Wire.beginTransmission(address);
//         error = Wire.endTransmission();

//         if (error == 0) {
//         Serial.print("I2C device found at address 0x");
//         if (address < 16) Serial.print("0");
//         Serial.print(address,HEX);
//         Serial.println("  !");

//         nDevices++;
//         }
//         else if (error == 4) {
//         Serial.print("Unknown error at address 0x");
//         if (address < 16) Serial.print("0");
//         Serial.println(address,HEX);
//         }    
//     }
//     if (nDevices == 0)
//         Serial.println("No I2C devices found\n");
//     else
//         Serial.println("done\n");
// }
















// void hardwareResetGyro() {
//     Serial.println("Hardware Resetting Gyro...");

//     pinMode(BNO_BOOT_PIN, OUTPUT);
//     digitalWrite(BNO_BOOT_PIN, HIGH); 
    
//     pinMode(BNO_RESET_PIN, OUTPUT);
//     digitalWrite(BNO_RESET_PIN, LOW);
//     delay(50); 
    
//     digitalWrite(BNO_RESET_PIN, HIGH);
//     pinMode(BNO_BOOT_PIN, INPUT); // pull up

//     delay(1000); 
//     Serial.println("Gyro Reset Complete.");
// }


// void I2CSet(){
//     for (int i = 0; i < NUM_TOF_SENSORS; i++) { pinMode(xshutPins[i], OUTPUT);digitalWrite(xshutPins[i], LOW); }
//     delay(50); // Let them power down completely

//     Wire.begin();
//     Wire.setClock(400000); // Optional: Fast I2C (400kHz)

//     hardwareResetGyro();
//     setupGyro();
//     Serial.println(gyro_ok); // This calls bno.begin(). Ensure bno.begin uses correct address!
    
//     if(gyro_ok) Serial.println("Gyro OK");
//     else Serial.println("Gyro FAILED");

//     setupDisplay();
//     showDisplay("Init...", 1, 0, 0);

//     setupToF(); 

//     Serial.println("ALL I2C SYSTEMS READY.");
//     showDisplay("Ready!", 1, 0, 0);
// }



