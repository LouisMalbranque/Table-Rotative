#include "moteur.h"
#include "ESP_bluetooth1.h"

Motor motor;
ESP_bluetooth esp_bluetooth;

String value;
boolean Pause = false;
int acceleration = 0;
int speed = 0;
int direction = 0;
int steps = 0;
int timetable = 0;
long initialTime;
int distance_restante = 0;
int temps_restant = 0;

void setup() {
  Serial.begin(9600);

  motor.begin();
  esp_bluetooth.begin();
  esp_bluetooth.writeData("0");

}

void loop() {

  value = esp_bluetooth.read();
  if (value == "0") {

  }
  else if (value == "1") {
    if (steps >= 0) {
      if (!motor.isRotating()) {
        esp_bluetooth.writeData("2");
      }
    }
    else if (timetable >= 0) {
      if (millis() - initialTime >= timetable) {
        esp_bluetooth.writeData("2");
      }
    }
    if (!Pause) {
      motor.run();
    }
  }
  else if (value == "2") {

  }
  else if (value == "3") {
    Pause = !Pause;
    if (Pause) {
      esp_bluetooth.writeData("4");
      if (timetable >= 0) {
        temps_restant = timetable - (millis() - initialTime);
      }
      else if (steps >= 0) {
        distance_restante = (steps - motor.distanceLeft());
      }
    }
    else {
      esp_bluetooth.writeData("1");
      if (timetable >= 0) {
        timetable = temps_restant;
        initialTime = millis();
        motor.setZero();
        motor.rotate(1);
      }
      else if (steps >= 0) {
        motor.setZero();
        motor.rotate(distance_restante);
      }
    }
  }
  else if (value == "4") {

  }
  else {
    esp_bluetooth.writeData("1");
    esp_bluetooth.decode();

    acceleration = esp_bluetooth.getValue(ACCELERATION);
    speed = esp_bluetooth.getValue(SPEED);
    direction = esp_bluetooth.getValue(DIRECTION);
    steps = esp_bluetooth.getValue(STEPS);
    timetable = esp_bluetooth.getValue(TIME);

    initialTime = millis();

    motor.setParams(speed, acceleration, direction);

    motor.setZero();

    if (steps >= 0) {
      motor.rotate(steps);
    }
    else if (timetable >= 0) {
      motor.rotate(1);
    }
  }
}
