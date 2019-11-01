#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <DHT.h>
float temperature_old = 0;
float humidity_old = 0;
float rainfall_old = 0;
RF24 transmit (48,49);                            //create RF24 object called transmit
byte address [5] ="00001";                     //set address to 00001                          //set rain sensor to pin 4
struct package
  {
    String temperature="34";
    float humidity = 5;
    float rainfall = 5;
  };
typedef struct package Package;
Package data;
void setup() {
  //dht.begin();
  transmit.begin();
  transmit.openWritingPipe(address);            //open writing pipe to address 00001
  transmit.setPALevel(RF24_PA_MIN);             //set RF power output to minimum
  transmit.setDataRate(RF24_250KBPS);           //set data rate to 250kbps
  transmit.setChannel(100);                               //set frequency to channel 100
  transmit.stopListening();
 // digitalWrite(rain_sensor, LOW);               //set pin 4 low
  //pinMode(rain_sensor, INPUT);                  //set pin 4 as an input
  }

//********************Function****************************************************
float get_rainfall()                          //get_rainfall function
{
 
          {
           data.rainfall = 5.2;
          }                 
}

//********************************************************************************

void loop() {
get_rainfall();
data.temperature = "5.0";
data.humidity = 5.1;
transmit.write(&data,sizeof(data));         //transmit the data         //update temperature_old to new reading
humidity_old = data.humidity;               //update humidity_old to new reading
rainfall_old = data.rainfall;               //update rainfall_old to new reading 
delay(300);                                 //delay to prevent false rainfall readings

}
