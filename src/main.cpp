#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// Define the pins that we will use
#define SENSOR 33
#define LED 26

#define SENSOR_TYPE DHT11
#define DELAY 5000 

DHT_Unified dht(SENSOR, SENSOR_TYPE);
long lastMeasure;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(LED, OUTPUT);
  // Initialize device.
  dht.begin();
  lastMeasure = millis();
}

void loop() {
  // Effectuer une mesure toutes les 5s
  // It is best practice not to use delays in the loop a better implementation is shown bellow
  if(millis() - lastMeasure > DELAY) {
    lastMeasure = millis();
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
  }
}