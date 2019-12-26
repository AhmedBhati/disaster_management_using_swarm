#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(48,49);
bool radioNumber = 1;
byte addresses[][6] = {"1Node","2Node","3Node","4Node","5Node"};
bool role = 0;
int n=4;
char text[9] = "";
char label[9] = "";
String valued;
String k;
bool node = 0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
    radio.begin();
    radio.setPALevel(RF24_PA_LOW);
    radio.openWritingPipe(addresses[1]);
    radio.openReadingPipe(1,addresses[0]);
    radio.startListening();
}


void loop() {
  for(int i=0;i<n;i++)
  {
    radio.openWritingPipe(addresses[i]);
    radio.openReadingPipe(1,addresses[0]);
/*           while (Serial.available()>0)
   {  
  delay(10);  
    char c = Serial.read(); 
    if (c == '#') {break;} 
    valued += c; 
   }
   if(valued!="")
   {
    valued.toCharArray(text,10);
   // Serial.println(valued);
//   bool cond=radio.write( &text, sizeof(text));
//   Serial.println(cond); 
   }*/
  if(i==1)
  {
    k="orange12";
    k.toCharArray(text,10);
    //Serial.println("asd");
  }
  else
  {
        k="blue123";
    k.toCharArray(text,10);
    //Serial.println("xyz");
  }
        
        radio.stopListening();                                                         
        if (!radio.write( &text, sizeof(text)) ){
            //Serial.println(F("failed"));
        }
        valued="";
        radio.startListening();
        role=1;                                                                     
        while( radio.available() && role==1){                            
          radio.read(&label, sizeof(label));
          Serial.println(label);
          role=0;
        }

        delay(1000);
  }

}
