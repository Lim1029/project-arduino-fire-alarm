#include <LiquidCrystal_I2C.h>
#include <Wire.h>

int pinLedRed = 5;
int pinLedGreen = 6;
int pinBuzzer = 7;

int pinLdr = A0;
int pinThermistor = A1;

int pinPushButton = 8;

int thermistorReading;
int ldrReading;

LiquidCrystal_I2C lcd(0x27, 2, 1,0,4,5,6,7,3,POSITIVE);

void setup() {
  // put your setup code here, to run once:
pinMode(pinLedRed, OUTPUT);
pinMode(pinLedGreen, OUTPUT);
pinMode(pinBuzzer, OUTPUT);
pinMode(pinLdr, INPUT);
pinMode(pinThermistor, INPUT);
pinMode(pinPushButton, INPUT);

Serial.begin(9600);
lcd.begin(16,2);
lcd.backlight();
lcd.print("Hello World");

// LiquidCrystal_I2C lcd(0x27, 2, 1,0,4,5,6,7,3,POSITIVE);

}

void loop() {
  // put your main code here, to run repeatedly:
thermistorReading = analogRead(pinThermistor);
// Serial.println(thermistorReading);

float termistorVoltage = 5.0/1024.0*(1024.0 - thermistorReading);
float termistorResistance = termistorVoltage*10000.0 / 
                            (5-termistorVoltage);
float tempK = 1.0 / ((1.0/298.15)- 
(log (10000.0/termistorResistance))/3950);
float tempC = tempK - 273.15; 

String lcdOutput1 = "Temp: " + String(tempC) + " deg C";
lcd.clear();  //clear the lcd text
lcd.print(lcdOutput1); //print on (by default) column 1 row 1
ldrReading = analogRead(pinLdr);
Serial.println(ldrReading);

int brightnessPercentage = map(ldrReading,100,1000,0,100);

String lcdOutput2 = "Brightness: " + String(brightnessPercentage) + "%";
lcd.setCursor(0,1); // set cursor to row 2, column 1
lcd.print(lcdOutput2);

if (tempC > 45)
{
  digitalWrite(pinBuzzer, HIGH);
  digitalWrite(pinLedRed, HIGH);
  digitalWrite(pinLedGreen, LOW);
} else {
  digitalWrite(pinBuzzer, LOW);
  digitalWrite(pinLedRed, LOW);
  digitalWrite(pinLedGreen, HIGH);
}

if (ldrReading < 200)
{
  digitalWrite(pinLedGreen, HIGH);
} else 
{
  digitalWrite(pinLedGreen, LOW);
}
delay(100);
}
