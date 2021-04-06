//Liquid Crystal Display for Alarm Clock

//Including the Liquid Crystal Library
#include <LiquidCrystal.h>

//Initializing Arduino pins for Display Inputs and Outputs
//bc -> Brightness Control pin
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bc = 11;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set the lcd number of rows and columns
  lcd.begin(16, 2);
  lcd.print("Hello, World!");
  pinMode(bc, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0,1);
  lcd.print(millis()/1000);
  analogWrite(bc, 0);
}
