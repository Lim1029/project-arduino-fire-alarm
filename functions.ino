int calcTemp(int tempReading) {
  double tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
  tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );       //  Temp Kelvin
  float tempC = tempK - 273.15;            // Convert Kelvin to Celcius
  float tempVolts = tempReading * 5.0 / 1024.0;
  tempC = (tempVolts - 0.5) * 10.0;
  return tempC;
}

void displayReadings() {
  thermistorSensorValue = analogRead(thermistorPin);
  ldrSensorValue = analogRead(LDRPin);

  brightnessPercentage = map(ldrSensorValue, 50, 950, 0, 100);
  TCelsius = calcTemp(thermistorSensorValue);

  tempOutput = "Temp: " + String(TCelsius);
  ldrOutput = "Brightness: " + String(brightnessPercentage) + "%";
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(tempOutput);
  lcd.setCursor(0, 1);
  lcd.print(ldrOutput);
}

void activateAlarm(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Suspect Fire");
  lcd.setCursor(0, 1);
  lcd.print("Alarm Activated");
  deactivateState = 0;
  while (deactivateState == 0){
    digitalWrite(greenLEDPin, LOW);
    currentTime = millis();
    if (currentTime-previousTime>1000){
      previousTime = currentTime;
      digitalWrite(redLEDPin, !digitalRead(redLEDPin));
    }
    digitalWrite(buzzerPin, HIGH);
    checkButton();
  }

}

void deactivateAlarm(){
  digitalWrite(redLEDPin, LOW);
  digitalWrite(buzzerPin, LOW);
  digitalWrite(greenLEDPin, HIGH);
  deactivateState = 1;
  deactivatedTime = millis();
}

void checkButton(){
  buttonState = digitalRead(buttonPin);
  if (buttonState == 0){
    if (isPressed == 0){
      timePressed = millis();
      isPressed = 1;
      }
    else{
      if (millis() - timePressed > 1000)
      {
        deactivateAlarm();
      }
    }
  } else {
    isPressed = 0;
  }


}