//Liquid Crystal Display for Alarm Clock

//Including the Liquid Crystal Library and string library
#include <LiquidCrystal.h>

//Initializing Arduino pins for Display Inputs and Outputs
//bc -> Brightness Control pin
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;

//bc can be used to handle the brightness  but a LC filter must be used to output a near dc value bc = 11


//initializing variables for clock and alarm
int clockMinutes = 0, clockHours = 0;
int alarmMinutes = 0, alarmHours = 0;
int refMinutes = 0, refHours = 0;
int alarmTone = 1;
int brightness = 5;
int a = 1;

//Creating directory/tree to identify type of display to show
int directory[3] = {0, 0, 0};

//Analog pin to identify button presses
const int analogPin = A2;
int analogVal;

//declaring buttons
int select = 0, up = 1, down = 2, deselect = 3;

//declaring function to identify the button
int buttonRead(int analogValue);

//declaring the button variable to store button value
int button;

//declaring function to output formatted string
String formatTime(int hours, int minutes);
String hourStr, minuteStr;

//Function for time calculation
int timeOut(void);

int seconds, durationSeconds, refSeconds = 0;
String Clock;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

/*Setup area */
void setup() {
  // set the lcd number of rows and columns
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(analogPin,INPUT);
}

/*Loop area*/
void loop() {
  // set cursor to 0th position of 0th row
  lcd.setCursor(0,0);
  //resetting the button;
  button = -1;

  //reading the analog pin value and determine the button pressed
  analogVal = analogRead(analogPin);
  button = buttonRead(analogVal);
  
  //time in hours and minutes
  clockHours, clockMinutes = timeOut();
  //Serial.println(clockHours);
  Clock = formatTime(clockHours, clockMinutes);
  lcd.print(Clock);
  delay(500);
}

/*User defined functions*/
//function to identify button pressed
int buttonRead(int analogValue){
  if (analogValue < 200) button = select;
  else if (analogValue < 430 ) button = up;
  else if (analogValue < 620 ) button = down;
  else if (analogValue < 800 ) button = deselect;
  return button;
  }

//format hours and minutes into standard hh:mm format
String formatTime(int hours, int minutes){
  if (hours<10) {
    hourStr = String("0")+String(hours);
    }
  else {
    hourStr = String(hours);
    }
  if (minutes<10) {
    minuteStr = String("0") + String(minutes);
  }
  else{
    minuteStr = String(minutes);
    }
  Serial.println(hourStr);
  Serial.println(minuteStr);
  return hourStr+":"+minuteStr;
  }
  

int timeOut(void){
  int minutes, hours;
  seconds = millis()/1000;
  durationSeconds = seconds - refSeconds;
  minutes = (durationSeconds/60);
  hours = minutes/60;
  minutes += refMinutes;
  if (minutes>=60){
    minutes = minutes%60;
    hours = (1+hours+refHours)%24;
    }
  else{
    hours = (hours+refHours)%24;
    }
  return hours,minutes;
  }
