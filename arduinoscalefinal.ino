#include <Arduino.h> 
#include "HX711.h" //library installable withing Arduino IDE, authored by Bogdan Necula

const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

HX711 scale;

void setup() {
  Serial.begin(57600);
  Serial.println("Initializing sensor. Do not apply pressure to sensor.");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);      
            
  scale.set_scale(44561); //calibration factor to measure in pounds *for this particular load cell*

  scale.tare();               

  Serial.println("Initialization Complete. Begin Test.");       
  Serial.println("Readings:");
}

void loop() {
  Serial.print("one reading:\t");
  Serial.println(scale.get_units(), 1);
  delay(2000);
}  