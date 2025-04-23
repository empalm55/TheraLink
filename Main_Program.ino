#include <Arduino.h> 
#include <HX711.h>

#define potPin A0 //analog pin for potentiometer
#define LOADCELL_DOUT_PIN 2 //digital pin for output of load cell
#define LOADCELL_SCK_PIN 3 //digital pin for socket on load cell
#define bluePin 5 //RGB LED blue pin
#define greenPin 6 //RGB LED green pin
#define redPin 7 //RGB LED red pin

float angleSensorValue; //straight value from potentiometer
int angle; //calculated later on based on angle sensor value
char input_val; //input character (a, f, s, z, or r)

HX711 scale; //define name for load cell

//setup routine runs once whenever uploaded or reset button is pushed
void setup() {
  pinMode(redPin, OUTPUT); //this and greenPin, bluePin are for RGB LED
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(potPin,INPUT); //potentiometer
  
  Serial.begin(57600); //initialize serial monitor

  setColor(255,50,0);
    Serial.println("Initializing. Do not apply pressure to sensor.");

    scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);      
  
    scale.set_scale(44456); //calibration factor to measure in pounds *for this particular load cell*
    
    scale.tare();               
    delay(1000);
    Serial.println("Initialization Complete.");
  
  setColor(0,100,0);
}

// the loop routine runs over and over again while power is on:
void loop() {
  input_val = Serial.read();
  
  if (input_val=='a'){ 
    Serial.println("Received instructions");
     while(Serial.read() != 's'){  //until you tell it to stop
       setColor(0,0,0); //turn off LED
       delay(500);
       setColor(255,0,0); //set LED to red
       angleSensorValue = analogRead(potPin); //read the input on the potentiometer:
      angle=((angleSensorValue-720)/(-4.13));
      Serial.println(angle); // print out the value calculated
      delay(500);
     }
    Serial.println("Data collection stopped");
    setColor(0,100,0); //set LED to green
  }
  else if (input_val=='f'){ 
    Serial.println("Recieved instructions");
    
    setColor(255,50,0); //set to yellow during initialization
 
    Serial.println("Remove all pressure from sensor. Initializing...");

    scale.tare();               

    delay(1000);
  
    Serial.println("Initialization Complete. Begin Test."); 
  
    setColor(0,100,0); //set to green for ready
    
    while(Serial.read() != 's'){  //until you tell it to stop
       setColor(0,0,0); //turn LED off
       delay(500);
       setColor(250,0,0);
      Serial.print(scale.get_units(), 1);
      Serial.println("  lbs.");
      delay(500);
      }
    Serial.println("Data Collection Stopped.");
    setColor(0,100,0);
  }
  else if (input_val=='r'){ //this will re-tare the load cell and reinitialize
    setColor(255,50,0);
    Serial.println("Re-initializing sensor. Do not apply pressure to sensor.");

    scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);      
  
    scale.set_scale(44357); //calibration factor to measure in pounds *for this particular load cell*
    
    scale.tare();               
    delay(1000);
    Serial.println("Re-initialization Complete.");
    setColor(0,100,0);
  }
  else{
  delay(100);
  }
 }

void setColor(int redValue, int greenValue, int blueValue){
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}
