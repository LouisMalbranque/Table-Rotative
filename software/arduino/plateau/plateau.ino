#include "moteur.h"
#include "ESP_server.h"

Motor motor;
ESP_server esp_bluetooth;

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
    Serial.println("Receive Value");
    if (steps >= 0) {
     Serial.println("Rotation nombre de tours");
      if (!motor.isRotating()) {
        Serial.println("fin rotation nombre de tours");
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
        steps = distance_restante;
        motor.rotate(steps);
      }
    }
  }
  else if (value == "4") {

  }
  else {
    esp_bluetooth.writeData("1");
    esp_bluetooth.decode();

    acceleration = esp_bluetooth.getValue(ACCELERATION);
    speed = esp_bluetooth.getValue(VITESSE);
    direction = esp_bluetooth.getValue(DIRECTION);
    switch (esp_bluetooth.getValue(CHOIX_ROTATION)){
      case 0: 
        steps = esp_bluetooth.getValue(NOMBRE_DE_PAS);
        timetable = -1;
        break;
      case 1:
        timetable = esp_bluetooth.getValue(TEMPS_DE_ROTATION);
        steps = -1;
        break; 
    }

   

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
