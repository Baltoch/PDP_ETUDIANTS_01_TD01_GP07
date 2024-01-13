#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// Define the pins that we will use
#define SENSOR 33
#define LED 26

#define SENSOR_TYPE DHT11
#define DELAY (uint64_t) 5000000 // delay in us

DHT_Unified dht(SENSOR, SENSOR_TYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(LED, OUTPUT);

  // Initialize device.
  dht.begin();

  sensors_event_t event;

  // Afficher l'humidité relative avec un peu de formatage

  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }

  // Afficher la température avec un peu de formatage

  // Get temperature event and print its value.
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }

  // Waiting for the transmission of outgoing serial data to complete before going to sleep
  Serial.flush();

  // Put ESP into deep sleep for 5s
  esp_sleep_enable_timer_wakeup(DELAY);
  esp_deep_sleep_start();
}

void loop() {}