#include <Arduino.h> 
#include <HX711.h>

float angleSensorValue; //straight value from potentiometer
int angle; //calculated later on based on angle sensor value
#define potPin A0 //analog pin for potentiometer
const int LOADCELL_DOUT_PIN = 2; //digital pin for output of load cell
const int LOADCELL_SCK_PIN = 3; // digital pin for socket on load cell
HX711 scale; //define name for load cell

//setup routine runs once whenever uploaded or reset button is pushed
void setup() {
  pinMode(potPin,INPUT); //potentiometer

  Serial.begin(57600); //initialize serial monitor for HC-05
 
  Serial.println("Initializing sensor. Do not apply pressure to sensor.");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);      
            
  scale.set_scale(44357); //calibration factor to measure in pounds *for this particular load cell*

  scale.tare();               

  Serial.println("Initialization Complete. Begin Test.");       
}

// the loop routine runs over and over again while power is on:
void loop() {                         
  if (Serial.read()=='a'){ 
    Serial.println("Received instructions");
     while(Serial.read() != 's'){  //until you tell it to stop
      angleSensorValue = analogRead(potPin); //read the input on the potentiometer:
      angle=((angleSensorValue-720)/(-4.13));
      Serial.println(angle); // print out the value calculated
      delay(500);
     }
    Serial.println("Data collection stopped");
  }
  if (Serial.read()=='f'){ 
    Serial.println("Recieved instructions");
     while(Serial.read() != 's'){  //until you tell it to stop
      Serial.print(scale.get_units(), 1);
      Serial.println("  lbs.");
      delay(1000);
      }
    Serial.println("Data Collection Stopped.");
  }
  if (Serial.read()=='r'){ //this will re-tare the load cell and reinitialize
    Serial.println("Initializing sensor. Do not apply pressure to sensor.");

    scale.set_scale(44357); //calibration factor to measure in pounds *for this particular load cell*

    scale.tare();               

    Serial.println("Initialization Complete. Begin Test.");
  }
  if (Serial.available()==false){
    digitalWrite(readyLED, LOW);
  }
  delay(100);
 }
