
#include <LiquidCrystal.h>
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 =11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 1);
  // Print a message to the LCD.
}

void loop() {
    lcd.print("Range of motION");

 int Poti = 720;

int Pot = analogRead(A0);
float ROM = ((Pot-720)/-4.1321);
Serial.println(ROM);
lcd.println(ROM)

if(Pot == Poti){
  Poti = Pot;

}

 else{
    Poti = Pot;
Serial.println(ROM);
 }


}
