#include "color.h"
#include "pins.h"
#include "display.h"


int redMin1 =30; //14; // Red minimum value
int redMax1 = 274;//92; // Red maximum value
int greenMin1 = 50;//15; // Green minimum value
int greenMax1 = 235;//111; // Green maximum value
int blueMin1 = 50;//13; // Blue minimum value
int blueMax1 = 230;//93; // Blue maximum value

int redMin2 = 15; // Red minimum value
int redMax2 = 92; // Red maximum value
int greenMin2 = 15; // Green minimum value
int greenMax2 = 111; // Green maximum value
int blueMin2 = 13; // Blue minimum value
int blueMax2 = 93; // Blue maximum value


int color=0;


int getRed1()   { digitalWrite(COLOR1_S2,LOW);  digitalWrite(COLOR1_S3,LOW);  return pulseIn(COLOR1_OUT, LOW); }
int getGreen1() { digitalWrite(COLOR1_S2,HIGH); digitalWrite(COLOR1_S3,HIGH); return pulseIn(COLOR1_OUT, LOW); }
int getBlue1()  { digitalWrite(COLOR1_S2,LOW);  digitalWrite(COLOR1_S3,HIGH); return pulseIn(COLOR1_OUT, LOW); }

int getRed2()   { digitalWrite(COLOR2_S2,LOW);  digitalWrite(COLOR2_S3,LOW);  return pulseIn(COLOR2_OUT, LOW); }
int getGreen2() { digitalWrite(COLOR2_S2,HIGH); digitalWrite(COLOR2_S3,HIGH); return pulseIn(COLOR2_OUT, LOW); }
int getBlue2()  { digitalWrite(COLOR2_S2,LOW);  digitalWrite(COLOR2_S3,HIGH); return pulseIn(COLOR2_OUT, LOW); }



void setupColor(){
    digitalWrite(COLOR1_S0,HIGH); digitalWrite(COLOR1_S1,LOW);
    digitalWrite(COLOR2_S0,HIGH); digitalWrite(COLOR2_S1,LOW);
}


int readColor(int color_sensor_number){
    int r, g, b;
    Serial.print(getRed1());Serial.print("  "); Serial.print(getGreen1());Serial.print("  "); Serial.println(getBlue1());
    if (color_sensor_number==1){
    r = map(getRed1(),   redMin1, redMax1, 255, 0);
    g = map(getGreen1(), greenMin1, greenMax1, 255, 0);
    b = map(getBlue1(),  blueMin1, blueMax1, 255, 0);
    }

    if (color_sensor_number==2){
    r = map(getRed2(),   redMin2, redMax2, 255, 0);
    g = map(getGreen2(), greenMin2, greenMax2, 255, 0);
    b = map(getBlue2(),  blueMin2, blueMax2, 255, 0);
    }
    r = constrain(r, 0, 255);
    g = constrain(g, 0, 255);
    b = constrain(b, 0, 255);


    if      (r > g && r > b)  {  Serial.println("RED"); showDisplay("RED",3,0,0); color = 1;    }
    else if (g > r && g > b)  {  Serial.println("GREEN"); showDisplay("Green",3,0,0); color = 2;  }
    else if (b > r && b > g)  {  Serial.println("BLUE"); showDisplay("Blue",3,0,0); color = 3;   }  
    else                      {  Serial.println("No color"); color = 0; }
    return color;

}



void calibrateColor(){
  Serial.println("Place White Paper");
  delay(5000);
  Serial.println("Minmum Values");
  Serial.print("Sensor 1 ");
  Serial.print(" R:"); Serial.print(getRed1());
  Serial.print(" G:"); Serial.print(getGreen1());
  Serial.print(" B:"); Serial.println(getBlue1());

  Serial.print("Sensor 2 ");
  Serial.print(" R:"); Serial.print(getRed2());
  Serial.print(" G:"); Serial.print(getGreen2());
  Serial.print(" B:"); Serial.println(getBlue2());
  Serial.println();

  Serial.println("Place Black Paper");
  delay(5000);
  Serial.println("Maximum Values");
  Serial.print("Sensor 1 ");
  Serial.print(" R:"); Serial.print(getRed1());
  Serial.print(" G:"); Serial.print(getGreen1());
  Serial.print(" B:"); Serial.println(getBlue1());

  Serial.print("Sensor 2");
  Serial.print(" R:"); Serial.print(getRed2());
  Serial.print(" G:"); Serial.print(getGreen2());
  Serial.print(" B:"); Serial.println(getBlue2());
  Serial.println();
}





// void calibrateColor(int color_sensor_number){
//     int minlist[3];
//     int maxlist[3];
//     unsigned long t_initial=millis();
//     int r,g,b;
//     if (color_sensor_number==1){
//         r=getRed1(); minlist[0]=r; maxlist[0]=r;
//         g=getGreen1(); minlist[1]=g; maxlist[1]=g;
//         b=getBlue1(); minlist[2]=b; maxlist[2]=b;
//         while ((millis()-t_initial)<5000){
//             r=getRed1();
//             if (r<minlist[0])minlist[0]=r;
//             if (r>maxlist[0])maxlist[0]=r;
//             g=getGreen1();
//             if (g<minlist[1])minlist[1]=g;
//             if (g>maxlist[1])maxlist[1]=g;
//             b=getBlue1();
//             if (b<minlist[2])minlist[2]=b;
//             if (b>maxlist[2])maxlist[2]=b;
//         }
//     }
//     if (color_sensor_number==2){
//         r=getRed2(); minlist[0]=r; maxlist[0]=r;
//         g=getGreen2(); minlist[1]=g; maxlist[1]=g;
//         b=getBlue2(); minlist[2]=b; maxlist[2]=b;
//         while ((millis()-t_initial)<5000){
//             r=getRed2();
//             if (r<minlist[0])minlist[0]=r;
//             if (r>maxlist[0])maxlist[0]=r;
//             g=getGreen2();
//             if (g<minlist[1])minlist[1]=g;
//             if (g>maxlist[1])maxlist[1]=g;
//             b=getBlue2();
//             if (b<minlist[2])minlist[2]=b;
//             if (b>maxlist[2])maxlist[2]=b;
//         }
//     }
//     Serial.println("Color Sensor ");Serial.println(color_sensor_number);
//     Serial.print("Red Min: ");Serial.print(minlist[0]); Serial.print("  Max: ");Serial.println(maxlist[0]);
//     Serial.print("Green Min: ");Serial.print(minlist[1]); Serial.print("  Max: ");Serial.println(maxlist[1]);
//     Serial.print("Blue Min: ");Serial.print(minlist[2]); Serial.print("  Max: ");Serial.println(maxlist[2]);
// }