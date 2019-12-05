#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
char text[9] = "";
char label[9] = "orange";
RF24 radio(48, 49 ); // CE, CSN
const byte address[6] = "00001";
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, address);
  radio.setChannel(0x66);
  radio.setPALevel(RF24_PA_MIN);
  radio.enableAckPayload();
  radio.writeAckPayload(1, &label, sizeof(label));
  radio.startListening();
}
void loop() {
  if (radio.available()) { 
    radio.read(&text, sizeof(text));
    //radio.read(&text1, sizeof(text1));
    Serial.println(text);
    radio.writeAckPayload(1, &label, sizeof(label));
    //Serial.println(text1);
  
  }
}
