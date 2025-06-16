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
#include <SPI.h>
#include <Ethernet.h>

#define DHTPIN 2
#define DHTTYPE DHT22
#define PIRPIN 4
#define CS_PIN 10

DHT dht(DHTPIN, DHTTYPE); // create global DHT object

// MAC 02-DE-AD-BE-EF-01
byte mac[] = { 0x02, 0xDE, 0xAD, 0xBE, 0xEF, 0x01 };

// setup runs once after reset
void setup() {
  Serial.begin(115200); // initializes UART at 115200 baud
  while (!Serial) { } // waiting for USB

  dht.begin(); // sets pinMode + timers
  pinMode(PIRPIN, INPUT);

  Ethernet.init(CS_PIN);
  if (Ethernet.begin(mac) == 0) {
    Serial.println(F("DHCP failed, falling back to static"));
    IPAddress ip(10,1,1,80);
    IPAddress dns(10,1,1,2);
    IPAddress gw(10,1,1,1);
    IPAddress mask(255,255,255,0);
    Ethernet.begin(mac, ip, dns, gw, mask);
  }
  delay(1000);

  Serial.print(F("IP  : ")); Serial.println(Ethernet.localIP());
  Serial.print(F("DNS : ")); Serial.println(Ethernet.dnsServerIP());
  Serial.print(F("GW  : ")); Serial.println(Ethernet.gatewayIP());
  Serial.print(F("Mask: ")); Serial.println(Ethernet.subnetMask());
}

// loop runs forever
void loop() {
  // calls initiate a start-signal pulse, wait ~1ms for a 40 bit reply, then parse it
  float humidityValue = dht.readHumidity();
  float tempValue = dht.readTemperature(true); // true bool returns temp in Fahrenheit

  bool motion = digitalRead(PIRPIN); // returns true if PIRPIN is > 2 V

  if (isnan(humidityValue) || isnan(tempValue)) {
    Serial.println(F("Sensor read failed")); // F macro stores string literals in flash (PROGMEM) instead of scarce 2 KB SRAM
  } else {
    Serial.print(F("Humidity: ")); Serial.print(humidityValue); Serial.print(F("%  |  "));
    Serial.print(F("Temp: ")); Serial.print(tempValue); Serial.print(" °F  |  ");
  }

  Serial.print(F("PIR: ")); Serial.println(motion ? F("MOTION DETECTED") : F("idle")); 

  delay(5000); // DHT22 needs >= 2s between reads
}