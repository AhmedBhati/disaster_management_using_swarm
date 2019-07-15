String valued;
//blue, green, yellow;
int j,i;
//#include<string.h>
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(2,OUTPUT);
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
pinMode(8,OUTPUT);
pinMode(9,OUTPUT);
pinMode(10,OUTPUT);
pinMode(11,OUTPUT);
pinMode(13,OUTPUT);
}
void loop() {
while (Serial.available()>0)
   {  
  delay(10);  
    char c = Serial.read(); 
    if (c == '#') {break;} 
    valued += c; 
    Serial.println(valued);
   }
if(valued == "orange")
  {
    digitalWrite(13,HIGH);
    delay(1000);
    digitalWrite(13,LOW);
  }
  else if(valued == "blue")
  {
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
    delay(2000);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
  }
   else if(valued == "green")
  {
    digitalWrite(8,HIGH);
    digitalWrite(9,LOW);
    delay(2000);
    digitalWrite(8,LOW);
    digitalWrite(9,LOW);
  }
   else if(valued == "yellow")
  {
    digitalWrite(10,HIGH);
    digitalWrite(11,LOW);
    delay(2000);
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);
  }
  valued="";
}
