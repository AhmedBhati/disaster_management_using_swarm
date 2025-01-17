#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
char text[20] = "";
RF24 radio(48, 49); // CE, CSN
const byte address[6] = "00001";
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}
void loop() {
  if (radio.available()) { 
    radio.read(&text, sizeof(text));
    Serial.println(text);
  }
}
