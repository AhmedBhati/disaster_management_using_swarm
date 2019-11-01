#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

RF24 receive (48,49);                         //create object called receive
byte address [5] = "00001";                 //create an array with 5 elements, where each element is 1 byte;
struct package
  {
    int starting_x=0;
    int destination_x=0;
    int starting_y=0;
    int destination_y=0;
  };
  typedef struct package Package;
  Package data;

void setup() {
  Serial.begin(115200);
  Serial.print("Starting Receiver \n");
  receive.begin();
  receive.openReadingPipe(0,address);      //open reading pipe 0 at address 00001
  receive.setPALevel(RF24_PA_MIN);         //Set RF output to minimum
  receive.setDataRate(RF24_250KBPS);       //set datarate to 250kbps
  receive.setChannel(100);                 //set frequency to channel 100
  receive.startListening();                

  }

void loop() {

  if (receive.available())                //check when received data available
  {
    receive.read(&data, sizeof(data));
    Serial.print(data.starting_x);                //print data to serial monitor
    Serial.print("\t");
    Serial.print(data.starting_y);                   //print data to serial monitor
    Serial.print("\t");
    Serial.print(data.destination_x);                   //print data to serial monitor
    Serial.print("\t");
    Serial.print(data.destination_y);                   //print data to serial monitor
    Serial.print("\t");
  }

}
