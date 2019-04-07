#include "moteur.h"
#include "ESP_bluetooth1.h"

Motor motor;
ESP_bluetooth esp_bluetooth;

String value;

void setup() {
  Serial.begin(9600);
    
  motor.begin();
  esp_bluetooth.begin();

}

void loop() {

/*
 * 0 : disponible
 * 1 : en traitement
 * 2 : fin du traitement
 * 3 : pause
 * 4 : stop
 */
  esp_bluetooth.writeData("0");
  esp_bluetooth.read();
  String value = esp_bluetooth.getData();
  while (value == "0") {
    esp_bluetooth.read();
    value = esp_bluetooth.getData();
  }
  esp_bluetooth.writeData("1");

  esp_bluetooth.decode();
  
  int acceleration = esp_bluetooth.getValue(ACCELERATION);
  int speed = esp_bluetooth.getValue(SPEED);
  int direction = esp_bluetooth.getValue(DIRECTION);
  int steps = esp_bluetooth.getValue(STEPS);
  int time = esp_bluetooth.getValue(TIME);

  motor.setParams(speed, acceleration, direction);
  
  if (steps >= 0) {
    Serial.println("Rotation en nombre de pas");
    motor.setZero();
    motor.rotate(steps);
    
    while (motor.isRotating()) {
      Serial.println(motor.getCurrentPosition());
      esp_bluetooth.read();
      value = esp_bluetooth.getData();
      if (value=="3"){
        while (value=="3"){
          esp_bluetooth.read();
          value = esp_bluetooth.getData();
        }
      }else if (value=="4"){
        break;
      }
      motor.run();
    }
  }
  else if (time >= 0) {
    Serial.println("Rotation en temps");
    long initialTime = millis();
    while (millis() - initialTime < time) {
      Serial.println(millis() - initialTime);
      motor.setZero();
      motor.rotate(1);
      
      esp_bluetooth.read();
      value = esp_bluetooth.getData();
      if (value=="3"){
        while (value=="3"){
          esp_bluetooth.read();
          value = esp_bluetooth.getData();
        }
      }else if (value=="4"){
        break;
      }
      motor.run();
    }
  }
  Serial.println("Rotation finished");
  esp_bluetooth.writeData("2");
  delay(100);
}
