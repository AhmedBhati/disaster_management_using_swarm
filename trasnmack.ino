#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
char text[9] = "";
char label[9]="";
String valued;
RF24 radio(8, 7 ); // CE, CSN
const byte address[6] = "00001";
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
  radio.setChannel(0x66);
  radio.setRetries(4, 10);
  radio.enableAckPayload();
  radio.openWritingPipe(address);
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
   bool sent_flag;
   sent_flag=radio.write( &text, sizeof(text));
   Serial.print(sent_flag);
  if(sent_flag)
  {
   if(radio.isAckPayloadAvailable())
   {
    radio.read(&label, sizeof(label));
    Serial.print(label);
    Serial.print("Transmitted to  node");
   }
   }
   else
   {
    Serial.print("Not Transmitted");
   }
   }
   valued="";
  }
