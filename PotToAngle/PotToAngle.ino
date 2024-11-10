/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.

  Some of this is based on a tutorial from Arduino:
  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogReadSerial
*/

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  float sensorValue = analogRead(A0);
  float angle=(sensorValue/1023)*265; //total angle range of potentiometer I am using is about 265 degrees
  // print out the value read:
  Serial.println(angle);
  delay(1000);  // delay in between reads for stability
}
