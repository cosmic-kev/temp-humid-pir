/*
Kevin Dillon
cosmic.kev.606@gmail.com
-------------------------
Project using Arduino Uno R3 to monitor temperature, humidity, and motion
Component list:
-- Arduino Uno R3
-- W5500
-- SR501 
-- DHT22
*/

#include <Arduino.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22
#define PIRPIN 4

DHT dht(DHTPIN, DHTTYPE); // create global DHT object

// setup runs once after reset
void setup() {
  Serial.begin(115200); // initializes UART at 115200 baud
  Serial.println(F("DHT22 + PIR smoke test")); // F macro stores string literals in flash (PROGMEM) instead of scarce 2 KB SRAM
  dht.begin(); // sets pinMode + timers

  pinMode(PIRPIN, INPUT);
}

// loop runs forever
void loop() {
  // calls initiate a start-signal pulse, wait ~1ms for a 40 bit reply, then parse it
  float humidityValue = dht.readHumidity();
  float tempValue = dht.readTemperature(true); // true bool returns temp in Fahrenheit

  bool motion = digitalRead(PIRPIN); // returns true if PIRPIN is > 2 V

  if (isnan(humidityValue) || isnan(tempValue)) {
    Serial.println(F("Sensor read failed"));
  } else {
    Serial.print(F("Humidity: ")); Serial.print(humidityValue); Serial.print(F("%  |  "));
    Serial.print(F("Temp: ")); Serial.print(tempValue); Serial.print(" °F  |  ");
  }

  Serial.print(F("PIR: ")); Serial.println(motion ? F("MOTION DETECTED") : F("idle")); 

  delay(2000); // DHT22 needs >= 2s between reads
}