#include<Servo.h>
int xi=0,yi=0;
int x,y;
int increment=0;
String coords; //value recieving from serial communication
Servo servo_camera,servo_ultrasonic;
void setup() {
  // put your setup code here, to run once:
pinMode(2,OUTPUT);/*the motor driver pins*/
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
servo_camera.attach(6);
servo_ultrasonic.attach(7);
Serial.begin(9600);
}
void loop() {
if(Serial.available()>0)
{
  coords=Serial.readString();
  x=coords.toInt();
  Serial.write('1');
  coords=Serial.readString();
  y=coords.toInt();
  Serial.write('1');
}
  
}
