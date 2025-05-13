#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "DHT.h"

LiquidCrystal_I2C lcd (0x27, 16, 2);
#define DHTPIN 3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
#define WATER_SENSOR_PIN A0 
int AWG = 13;
unsigned long runTime = 600000;
unsigned long startTime;
bool awgOn = false;

void setup() {
  pinMode(AWG, OUTPUT);
  lcd.init();
  lcd.backlight();
  dht.begin();
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  int sensorValue = analogRead(WATER_SENSOR_PIN);
  int waterPercent = map(sensorValue, 0, 1023, 0, 100);

  if (waterPercent < 30 && temp >= 28 && hum >= 65 && awgOn == false) {
    awgOn = true;
    digitalWrite(AWG, HIGH);
    startTime = millis();
}

if (awgOn && millis() - startTime >= runTime) {
    digitalWrite(AWG, LOW);
    delay(60000);
    digitalWrite(AWG, HIGH);
    startTime = millis();   
}

if (waterPercent >= 90) {
    digitalWrite(AWG, LOW);
    awgOn = false;
}

}
