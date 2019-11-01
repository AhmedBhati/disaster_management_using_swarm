/*
 * for clockwise pin 5 is high and 6 is low
 * for anticlockwise pin 10 is high and 9 is low
 */
const int trigPin = 11;
const int echoPin = 12;
// defines variables
#include <math.h>
#include <Wire.h>
#include <MPU6050.h>
float pitch = 0;
float roll = 0;
float yaw = 0;
double temp=1.0;
unsigned long timer = 0;
float timeStep = 0.01;
double m=-1;
int steps=0;
int counter=0;
//double M=-1;
MPU6050 mpu;
int outputA=6;
int outputB=7;
int aState;
int aLastState=0;  
int flag=0;
int bkl=1;
void setup() 
{ 
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(2,OUTPUT);
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
//pinMode(10,OUTPUT);
//digitalWrite(7,HIGH);
pinMode(outputA,INPUT);
pinMode(outputB,INPUT);
Serial.begin(115200);
aLastState = digitalRead(outputA); 
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  mpu.calibrateGyro();
  mpu.setThreshold(3);
}
void loop() 
{
  int distance;
timer = millis();
while(Serial.available()>0)
{
  delay(10);
double a=Serial.parseInt();
Serial.println(a);
double b=Serial.parseInt();
Serial.println(b);
char bd = Serial.read();
double z= b/a;
m = atan(z);
m=m*57.2958; // degree conversion
double distance = sqrt((a*a) + (b*b));
steps=int((distance)*1.8);
if(m<0)
  m=m-(2*m);
if(a>0 && b>0)
  m=int(90-m);
if(a<0 && b>0)
  m=int(270+m);
if(a<0 && b<0)
  m=int(270-m);
if(a>0 && b<0)
  m=int(90+m);
}
Vector norm = mpu.readNormalizeGyro();
yaw = yaw + norm.ZAxis * timeStep;
temp=-(yaw +norm.ZAxis * timeStep);
//if(flag!=bkl)
//{
if(temp<=m)
{
Serial.println(m);
analogWrite(2,0);
analogWrite(3,200);
analogWrite(4,0);
analogWrite(5,200);
delay(9);
analogWrite(2,0);
analogWrite(3,0);
analogWrite(4,0);
analogWrite(5,0);
}
if(temp>=m)
{ 
  while(counter!=steps)//1.8 is the multiplying factor
  {
 aState = digitalRead(outputA); // Reads the "current" state of the outputA
  // If the previous and the current state of the outputA are different, that means a Pulse has occured
  analogWrite(2,LOW);
  analogWrite(3,200);
  digitalWrite(4,200);
  analogWrite(5,LOW);
  delay(10);
  analogWrite(2,LOW);
  analogWrite(3,LOW);
  analogWrite(4,LOW);
  analogWrite(5,LOW); 
  counter++;
     Serial.print("Position: ");
     Serial.println(counter); 
   aLastState = aState; 
 /* distance=sonar(trigPin,echoPin);
  Serial.print("distance:");
  Serial.println(distance);
  if(distance<10)
  {
    Serial.println("entered");
analogWrite(10,0);
analogWrite(4,200);
analogWrite(5,0);
analogWrite(6,200);
delay(1000);
analogWrite(4,0);
analogWrite(5,0);
analogWrite(6,0);
analogWrite(10,0);
delay(10);
analogWrite(10,LOW);
  analogWrite(4,128);
  digitalWrite(5,HIGH);
  analogWrite(6,LOW);
  delay(500);
  analogWrite(10,LOW);
  analogWrite(4,LOW);
  analogWrite(5,LOW);
  analogWrite(6,LOW); 
delay(10);
analogWrite(10,200);
analogWrite(4,0);
analogWrite(5,200);
analogWrite(6,0);
delay(1200);
analogWrite(4,0);
analogWrite(5,0);
analogWrite(6,0);
analogWrite(10,0);
counter++;*/
}
}
}
//}
//flag=flag+1;
//}
/*int sonar(int trigPin,int echoPin)
{
  int distance,duration;
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;
return(distance);
}*/
