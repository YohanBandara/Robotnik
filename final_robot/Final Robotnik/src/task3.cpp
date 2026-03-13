#include "task3.h"
#include"motion.h"
#include "lineFollowing.h"
#include"ir.h"
#include "encoder.h"


int Task3(){
    // goDistance(50,50);
    // startMotors(50,50);
    // while(true){
    //     readIR();delay(10);
    //     if (isJunction()){goDistance(120,50);turnUntilLine('R');break;}
    // }

    // int count=0;
    // int decode_array[3]={2,3,4};
    // int barcode_array[5]={0};
    // int weighted_array[5]={16,8,4,2,1};

    // // int readStatus=0;

    // // while(true){
    // //     runLineFollower(50,50);
    // //     if (isWhiteLine() and readStatus==0){resetPulses();readStatus=1;}
    // //     if (isWhiteLine()==0 and readStatus==1){
    // //         float d=distance();
    // //         if (d>45)barcode_array[count]=1;
    // //         else barcode_array[count]=0;
    // //         readStatus=0;
    // //         count++;
    // //     }
    // //     if (count==5)break;
    // // }


    // while(count < 5){
    //     readIR();
    //     if (!isWhiteLine()) {runLineFollower(50, 50); }
    //     else {
    //         resetPulses();
    //         startMotors(50, 50);     
    //         while(isWhiteLine()) {readIR();}
    //         float stripWidth = distance();
    //         if (stripWidth > 45) {barcode_array[count] = 1;Serial.println("Bit: 1 (Wide)");} 
    //         else {barcode_array[count] = 0;Serial.println("Bit: 0 (Short)");}          
    //         count++;
    //         delay(50); 
    //     }
    // }


    // while(!isWhiteLine()){runLineFollower(50,50);delay(10);}
    // stopMotors();

    // int sum=0;
    // for (int i=0;i<5;i++)sum+=barcode_array[i]*weighted_array[i];
    // int remainder=sum%3;
    // return decode_array[remainder];

}






