float sensorValue;
float angle;
#define potPin A0
#define ledPin 2

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second
  pinMode(potPin,INPUT); //potentiometer
  pinMode(ledPin,OUTPUT); //LED recorder indicator
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
 if (Serial.read()=='a'){ 
  while(Serial.read() !='s'){  //until you tell it to stop
    digitalWrite(ledPin, HIGH);
    // read the input on analog pin 0:
    sensorValue = analogRead(potPin);
    angle=(sensorValue/1023)*265;
    // print out the value you read:
    Serial.println(angle);
    delay(500);
    digitalWrite(ledPin,LOW);
    delay(500);
  }
  digitalWrite(ledPin, LOW);
 }

  delay(1000);  // delay in between reads for stability
}
