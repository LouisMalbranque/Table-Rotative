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


void setup() {
  Serial.begin(115200);
  Serial.println("start");
  bluetooth.begin();
  lcd.begin();
  relays.begin();
  esp_bluetooth.begin();

  static BLEUUID serviceUUID("4fafc201-1fb5-459e-8fcc-c5c9c331914b");
  esp_bluetooth.scan();
  Serial.println("Scan finished, trying to connect...");
  while (!esp_bluetooth.connect(serviceUUID)){
    Serial.println("trying to connect");
  }
}

void loop() {
/*
  Serial.println("sending data");
  esp_bluetooth.write("10");
  delay(100);
  while (esp_bluetooth.read() != "0") Serial.println(esp_bluetooth.getData());
  Serial.print("received data: ");
  Serial.print(esp_bluetooth.getData());
  
*/
  while(!bluetooth.receive());
  bluetooth.decode();

  lcd.setValues(bluetooth.getValues());
  relays.setValues(bluetooth.getValues());

  lcd.display();

  if (bluetooth.getValue(MODE) == 0) {
    int steps = (int) (bluetooth.getValue(STEPS) / bluetooth.getValue(FRAME));
    int datagramme[NRF_DATA_LENGTH] = {bluetooth.getValue(ACCELERATION), bluetooth.getValue(SPEED), bluetooth.getValue(DIRECTION), steps , bluetooth.getValue(ROTATION_TIME)};
    for (int i = 0; i < bluetooth.getValue(FRAME); i++) {
      esp_bluetooth.write(datagramme);
      delay(100);
      while (esp_bluetooth.read() != "2");
      relays.triggerAll();
    }
  }
  else if (bluetooth.getValue(MODE) == 1) {
    int steps = (int) (bluetooth.getValue(STEPS) * bluetooth.getValue(ROTATION_NUMBER));
    int datagramme[NRF_DATA_LENGTH] = {bluetooth.getValue(ACCELERATION), bluetooth.getValue(SPEED), bluetooth.getValue(DIRECTION), steps , bluetooth.getValue(ROTATION_TIME)};
    esp_bluetooth.write(datagramme);
    delay(100);
    while (esp_bluetooth.read() != "0");
  }

  bluetooth.resetValues();
  lcd.resetValues();

}
