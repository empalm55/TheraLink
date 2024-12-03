#include <SoftwareSerial.h>

float angleSensorValue; //straight value from potentiometer
float forceSensorValue; //straight value from force sensor
float angle; //calculated later on based on angle sensor value
float force; //calculated later based on force sensor value
#define potPin A0 //analog pin for potentiometer
#define forcePin A3 //analog pin for force sensor; currently represented by potentiometer

SoftwareSerial dataStream(8,7); //initialize RX and TX pins (reciever and transmitter)

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second
  pinMode(potPin,INPUT); //potentiometer
  pinMode(redLED,OUTPUT); //LED recorder indicator
  pinMode(blueLED, OUTPUT); //bluetooth connection indicator
  dataStream.begin(115200); //initialize serial monitor for HC-05
}

// the loop routine runs over and over again while power is on:
void loop() {
  digitalWrite(blueLED,LOW);
  digitalWrite(redLED,LOW);
  while(!dataStream){ //wait for serial to connect & flash blue light to indicate that it is awaiting connection
    digitalWrite(blueLED,HIGH);
    delay(500);
    digitalWrite(blueLED,LOW);
    delay(500);
  }
  if(dataStream.available()==true){
    digitalWrite(blueLED,HIGH);
  }
  if (dataStream.read()=='g'){ //tell 
     while(dataStream.read() !='s'){  //until you tell it to stop
        digitalWrite(redLED, HIGH); //start flashing "recording" light, along with LOW later on in this loop
        // read the input on analog pin 0, the potentiometer:
        angleSensorValue = analogRead(potPin);
        angle=(angleSensorValue/1023)*265;
        forceSensorValue = analogRead(forcePin);
        force=(forceSensorValue/1023)*800;
      // print out the values you read:
      dataStream.print(angle);
      dataStream.print(", ");
      dataStream.println(force);
      delay(500);
      digitalWrite(redLED,LOW);
      delay(500);
      }
digitalWrite(redLED, LOW); //when recording is stopped, turn off recorder light
 }
  /*if (dataStream.read()=='f'){ 
     while(dataStream.read() !='s'){  //until you tell it to stop
        digitalWrite(redLED, HIGH); //start flashing recording light
        // read the input on analog pin 1, the force sensor:
        forceSensorValue = analogRead(forcePin);
        force=(forceSensorValue/1023)*800;
      // print out the value you read:
      dataStream.println(force);
      delay(500);
      digitalWrite(redLED,LOW);
      delay(500);
      }
  digitalWrite(redLED, LOW); //when recording is stopped, turn off recorder light
 }*/
}
