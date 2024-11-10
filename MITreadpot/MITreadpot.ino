
//  include library
#include "bleconfig.h"

#define potPin A0
#define ledIndicator 8

float potValue;
float angleValue;

void setup(){
  Serial.begin(9600);
  Serial.println("I'm in!");
  delay(1000);

  pinMode(ledIndicator, OUTPUT);

  BLE.begin();

  if (!BLE.begin()){ //initialize BLE
    Serial.println("Starting BLE failed!");
    while(1);
  }

  BLE.setLocalName("TheraLink FLX"); //connection name
  BLE.setAdvertisedService(bleService); //advertise service
  bleService.addCharacteristic(potChar); //add characteristic to service
  BLE.addService(bleService); 
  potChar.writeValue(oldPotValue); //set starting string
  
  BLE.advertise();  //start advertising

  Serial.print("Peripheral device MAC: ");
  Serial.println(BLE.address());
  Serial.println("Waiting for connections...");

}


void loop(){

  BLEDevice central = BLE.central(); //Wait for a BLE central device to connect
  //if a central device is connected to the peripheral:
  if(central){
    Serial.print("Connected to central MAC: ");
    Serial.println(central.address()); //print the central device's BT address
   
    while (central.connected()){

      long currentMillis=millis();
      digitalWrite(ledIndicator, HIGH); //turn on LED to indicate BT connection

      if(currentMillis-previousMillis>=200){
        previousMillis=currentMillis;

        potValue =analogRead(potPin); //read potentiometer value
        angleValue=(potValue/1023)*265; //convert value from potentiometer (number between 0 and 1023) to angle

        //Serial.println("Sending notifications");
        Serial.println(angleValue);
        potChar.writeValue(angleValue);
    
        delay(1000);
      }
    } //keep looping while connected
  
  //when the central device disconnects, turn off the LED
  digitalWrite(ledIndicator, LOW);
  Serial.print("Disconnected from central MAC: ");
  Serial.println(central.address());
  //reinitialize BLE when disconnected
  BLE.stopAdvertise();
  BLE.begin();
  BLE.advertise();
  }
}


