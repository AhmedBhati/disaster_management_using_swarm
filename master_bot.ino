#include <Wire.h>
#include <MPU6050.h>
int steps=0;
int counter=0;
int aState;
int aLastState=0;  
int w=-1;
MPU6050 mpu;
int d=30;
// Timers
unsigned long timer = 0;
float timeStep = 0.01;
float temp=0;
// Pitch, Roll and Yaw values
int outputA=6;
int outputB=7;
float pitch = 0;
float roll = 0;
float yaw = 0;
#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <Servo.h>
#include <SPI.h>
#include <math.h>
String x1,y1,x12,y12,x13,y13="";
const int trig=9;
const int echo=10;
int flag1=0;
int flag2=0;
int flag3=0;
int bkl=1;
int i,x,y=0;
int duration, inches, c;
Servo servo;
int starting_x=0;
int destination_x=0;
int starting_y=0;
int destination_y=0;
RF24 transmit (48,49);                            
byte address [5] ="00001";                     
struct package
  {
    int starting_x=0;
    int destination_x=0;
    int starting_y=0;
    int destination_y=0;
  };
typedef struct package Package;
Package data;
void setup()
{
  Serial.begin(9600);
  //mpu.calibrateGyro();
  // Set threshold sensivty. Default 3.
  // If you don't want use threshold, comment this line or set 0.
  //mpu.setThreshold(1);
  transmit.begin();
  transmit.openWritingPipe(address);            
  transmit.setPALevel(RF24_PA_MIN);             
  transmit.setDataRate(RF24_250KBPS);           
  transmit.setChannel(100);                       
  transmit.stopListening();
  servo.attach(8);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT); 
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(A7,OUTPUT);
  analogWrite(A7,LOW);
  digitalWrite(7,LOW);
  delay(3000);
  x1=Serial.readString();
  delay(2000);
}
void loop()
{
  timer=millis();
   for(int i=180;i>=1;i--)
  {
   servo.write(i);
   delay(50);
  if(Serial.available()>0)
  {
    String c=Serial.readString();
    if(c=="orange")
    {
   Serial.println('r');
   digitalWrite(trig, LOW);
   delayMicroseconds(2);
   digitalWrite(trig, HIGH);
   delayMicroseconds(10);
   digitalWrite(trig, LOW);
   duration = pulseIn(echo, HIGH);
   c = duration/29/2;
   delay(1000);
   Serial.println(c);
   delay(1000);
   Serial.println(servo.read());
   delay(3000);
   String m=Serial.readString();
   String n1=Serial.readString();
   int n=x1.length();
   for(i=0;i<n;i++)
  {
    if(x1[i]=='k')
    {
      flag1=bkl;
      i++;
    }
    if(flag1!=1)
    {
      x12+=x1[i];
    }
    else
    {
      y12+=x1[i];
    }
  }
  data.destination_x=x12.toInt();
  data.destination_y=y12.toInt(); 
  flag1=0;
  n=m.length();
  for(i=0;i<n;i++)
  {
    if(m[i]=='k')
    {
      flag1=bkl;
      i++;
    }
    if(flag1!=1)
    {
      x13+=m[i];
    }
    else{
      y13+=m[i];
    }
  }
  if(x13[0]=='-')
  {
    flag2=1;
    x13.remove(0,1);
  }
    if(y13[0]=='-')
  {
    flag3=1;
    y13.remove(0,1);
  }
  data.starting_x=x13.toInt();
  data.starting_y=y13.toInt();
  if(flag2==1)
    data.starting_x=-data.starting_x;
    if(flag3==1)
    data.starting_y=-data.starting_y;
   transmit.write(&data,sizeof(data)); 
  int b=data.destination_y;
   int a=data.destination_x;
    double z= b/a;
     w = atan(z);
    w=w*57.2958; // degree conversion
    double distance1 = sqrt((a*a) + (b*b));
    distance1=1.8*distance1;
    if(w<0)
  w=w-(2*w);
if(a>0 && b>0)
  w=int(90-w);
if(a<0 && b>0)
  w=int(270+w);
if(a<0 && b<0)
  w=int(270-w);
if(a>0 && b<0)
  w=int(90+w);
    }
  }
  }
Vector norm = mpu.readNormalizeGyro();
yaw = yaw + norm.ZAxis * timeStep;
temp=-(yaw +norm.ZAxis * timeStep);
if(temp<=34)
{
Serial.println(w);
analogWrite(2,0);
analogWrite(3,HIGH);
analogWrite(4,0);
analogWrite(5,170);
delay(9);
analogWrite(5,0);
analogWrite(4,0);
analogWrite(3,0);
analogWrite(2,0);
}
Serial.println(temp);
if(temp>=w)
{
if(counter!=steps)
{
Serial.println("entered");
analogWrite(2,0);
analogWrite(3,200);
analogWrite(4,130);
analogWrite(5,0);
delay(20);
analogWrite(2,0);
analogWrite(3,0);
analogWrite(4,0);
analogWrite(5,0);

aState=digitalRead(outputA);
if (aState != aLastState){     
if (digitalRead(outputB) != aState) 
   counter--;
else
   counter++;    
aLastState = aState;
}
}
}
}

//Serial.pritln("translating in straight direction");
//Serial.print("counter value is :");
//Serial.println(counter);
