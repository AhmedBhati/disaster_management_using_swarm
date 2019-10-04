#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(48, 49); // CE, CSN
const byte address[6] = "00001";
String valued;
char text[20];
int n;
//blue, green, yellow;
int j,i;
//#include<string.h>
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
radio.begin();
radio.openWritingPipe(address);
radio.setPALevel(RF24_PA_MIN);
radio.stopListening();
}
void loop() {
while (Serial.available()>0)
   {  
  delay(10);  
    char c = Serial.read(); 
    if (c == '#') {break;} 
    valued += c; 
   // Serial.print(valued);
   }
   if(valued!="")
   {
    valued.toCharArray(text,10);
    radio.write(&text, sizeof(text));
   }
   valued="";
  
}
