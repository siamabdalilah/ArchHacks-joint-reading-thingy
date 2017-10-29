#include <Wire.h>
#include <math.h>
#include "MMA7660.h"

#define accelPin1 8
#define accelPin2 9
#define DEL 5000 
#define Pi 3.1416

MMA7660 accel;


bool pin1 = 1;
//bool pin2 = 0;

unsigned long startTime = 0;
int count = 0;
float avg = 0;
float angMax = 0;

void setup()
{
  accel.init();  
  Serial.begin(9600);
  pinMode(accelPin1, OUTPUT);
  pinMode(accelPin2, OUTPUT);
  digitalWrite(accelPin1, pin1);
  digitalWrite(accelPin2, !pin1);
}
void loop()
{
  float ax,ay,az;
  accel.getAcceleration(&ax,&ay,&az);
//  Serial.print(ax);
//  Serial.print(" ");
//  Serial.print(ay);
//  Serial.print(" ");
//  Serial.print(az);
//  Serial.println(" ");
 
  float angle1 = asin(ay / sqrt(ax*ax + ay*ay + az*az));

  digitalWrite(accelPin1, 0);
  digitalWrite(accelPin2, 1);

  accel.getAcceleration(&ax, &ay, &az);
//  Serial.print(ax);
//  Serial.print(" ");
//  Serial.print(ay);
//  Serial.print(" ");
//  Serial.print(az);
//  Serial.println(" ");

  float angle2 = asin(ay / sqrt(ax*ax + ay*ay + az*az));
  digitalWrite(accelPin2, 0);
  digitalWrite(accelPin1, 1);
  
  float bendAngle = angle1 - angle2 + Pi;
  angMax = (bendAngle > angMax) ? bendAngle : angMax;
  if (millis() - startTime > DEL)
  {
    avg = avg*count + angMax;
    count++;
    avg = avg / count;
    angMax = 0;
    startTime = millis();
  }

  if (Serial.available() > 0)
  {
    Serial.read();
    //int avgInt = (int) (avg * 10000);
    //byte c1 = (avgInt >> 8);
    //byte c2 = avgInt & 11111111;

    //Serial.printl(c1);
    //Serial.print(c2);
    Serial.println(avg*180/Pi);
  }
}


