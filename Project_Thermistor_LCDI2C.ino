#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define LDRPin A1
#define thermistorPin A0
#define redLEDPin 10
#define greenLEDPin 11
#define buttonPin 12
#define buzzerPin 9
#define cooldownTime 10000

int thermistorSensorValue;
int ldrSensorValue;
String tempOutput;
String ldrOutput;
const int maxLdrValue = 950;
const int minLdrValue = 50;
int brightnessPercentage;
float TCelsius;
int alarmState = 0;
unsigned long previousTime = 0;
int buttonState = 1;
int previousTimeButton = 0;
int deactivateState = 0;
unsigned long currentTime;
unsigned long timePressed;
int isPressed = 0;
int deactivatedTime = -9999;

LiquidCrystal_I2C lcd(0x27, 2,1,0,4,5,6,7,3,POSITIVE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(redLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
  pinMode(buttonPin,INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.print("Hello,UCTRONICS!");

}

void loop() {
  // put your main code here, to run repeatedly:
  displayReadings();
  if (TCelsius>35.0){
    if (millis()-deactivatedTime>cooldownTime)
      activateAlarm();
  }
  delay(100);
}
