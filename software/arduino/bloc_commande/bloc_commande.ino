#define ESP32 1

#include "constantes.h"

#include "bluetooth.h"
#include "lcd.h"
#include "relays.h"
#include "ESP_bluetooth.h"



Bluetooth bluetooth;
Lcd lcd;
Relays relays;
ESP_bluetooth esp_bluetooth;


void blink(){
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);
}

void setup() {
  bluetooth.begin();
  lcd.begin();
  relays.begin();
  esp_bluetooth.begin();

  digitalWrite(LED, LOW);

  pinMode(RESET, INPUT);
  attachInterrupt(RESET, reset, FALLING);
  
  static BLEUUID serviceUUID("4fafc201-1fb5-459e-8fcc-c5c9c331914b");
  esp_bluetooth.scan();
  Serial.println("Scan finished, trying to connect...");
  while (!esp_bluetooth.connect(serviceUUID)){
    Serial.println("trying to connect");
  }
  blink();
  
}

void loop() {

  while(!bluetooth.receive());
  blink();
  bluetooth.decode();
  

  lcd.setValues(bluetooth.getValues());
  relays.setValues(bluetooth.getValues());

  lcd.display();

  if (bluetooth.getValue(MODE) == 0) {
    int steps = (int) (bluetooth.getValue(STEPS) / bluetooth.getValue(FRAME));
    int datagramme[] = {bluetooth.getValue(ACCELERATION), bluetooth.getValue(SPEED), bluetooth.getValue(DIRECTION), steps , bluetooth.getValue(ROTATION_TIME)};
    for (int i = 0; i < bluetooth.getValue(FRAME); i++) {
      esp_bluetooth.write(datagramme);
      delay(100);
      while (esp_bluetooth.read() != "2");
      relays.triggerAll();
    }
  }
  else if (bluetooth.getValue(MODE) == 1) {
    int steps = (int) (bluetooth.getValue(STEPS) * bluetooth.getValue(ROTATION_NUMBER));
    int datagramme[] = {bluetooth.getValue(ACCELERATION), bluetooth.getValue(SPEED), bluetooth.getValue(DIRECTION), steps , bluetooth.getValue(ROTATION_TIME)};
    esp_bluetooth.write(datagramme);
    delay(100);
    while (esp_bluetooth.read() != "0");
  }

  bluetooth.resetValues();
  lcd.resetValues();

}

void reset(){
  ESP.restart();
}
