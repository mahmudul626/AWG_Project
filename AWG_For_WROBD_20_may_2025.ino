#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11
#define WATER_SENSOR A0
#define AWG 12 

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(AWG, OUTPUT);
  digitalWrite(AWG, LOW);
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();
}

void loop() {
  float humidity = dht.readHumidity();
  float temp = dht.readTemperature();
  int value = analogRead(WATER_SENSOR);
  int moisturePercent = map(value, 0, 1023, 0, 100);

  if (isnan(humidity) || isnan(temp)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error!");
    delay(2000);
    return;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T: ");
  lcd.print(temp);
  lcd.print("C H:");
  lcd.print(humidity);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("Water: ");
  lcd.print(moisturePercent);
  lcd.print("%");

  // Control logic
  if (temp >= 30 && humidity >= 65 && moisturePercent <= 90) {
    digitalWrite(AWG, HIGH);
  } else {
    digitalWrite(AWG, LOW);
  }

  delay(2000);
}
