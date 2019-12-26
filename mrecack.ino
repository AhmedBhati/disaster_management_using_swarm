#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(48,49);
bool radioNumber = 0;
byte addresses[][6] = {"1Node","2Node","3Node","4Node","5Node"};
bool role = 0;
char text[9] = "";
char label[9] = "ack23";
String valued;
bool node = 0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
    radio.begin();
    radio.setPALevel(RF24_PA_LOW);
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1,addresses[2]);//change index from 1 to 4 for every slave
    
    radio.startListening();
}


void loop() {
       
        if( radio.available()){
            // Variable for the received timestamp
            while(radio.available()&& role==0) {                                   
                radio.read( &text, sizeof(text) );  
                Serial.println(text);
                role=1;
            }
            if(role==1){
            radio.stopListening();                                        // First, stop listening so we can talk
            node=radio.write(&label, sizeof(label) );   
            Serial.println(label);
            Serial.println(node);
            role=0;
            radio.startListening();                                       // Now, resume listening so we catch the next packets
        }}
    }
