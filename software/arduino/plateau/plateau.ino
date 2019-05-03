#include "moteur.h"
#include "ESP_server.h"

// création des objets
Motor motor;
ESP_server esp_bluetooth;

// valeurs globales
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
  Serial.begin(115200);

  // démarrage des modues
  motor.begin();
  esp_bluetooth.begin();
  esp_bluetooth.writeData("0");

}

void loop() {
  // récupération de la data sur les charactéristiques
  value = esp_bluetooth.read();
  // "0" signifie disponible, donc rien à faire
  if (value == "0") {

  }
  // "1" signifie en cours, donc le moteur tourne
  else if (value == "1") {
    if (steps >= 0) {
     // si le nombre de pas est positif, alors la rotation est en nombre de tours
     Serial.println("Rotation nombre de tours");
     // si le moteur a fini de tourner, on termine l'action
      if (!motor.isRotating()) {
        Serial.println("fin rotation nombre de tours");
        esp_bluetooth.writeData("2");
      }
    }
    else if (timetable >= 0) {
      // si le temps est positif, alors on est en rotation en temps
      if (millis() - initialTime >= timetable) {
        // si le temps est écoulé, on fini l'action
        esp_bluetooth.writeData("2");
      }
    }
    // si le moteur n'est pas en pause, on tourne
    if (!Pause) {
      motor.run();
    }
  }
  // "2" signifie terminé, donc rien à faire
  else if (value == "2") {

  }
  // "3" signifie le toggle de la pause
  else if (value == "3") {
    Pause = !Pause; // toggle la pause
    
    if (Pause) {
      // si on passe en pause on se met à "4"
      esp_bluetooth.writeData("4");
      // on sauvegarde le nombre de pas / le temps restant pour la reprise
      if (timetable >= 0) {
        temps_restant = timetable - (millis() - initialTime);
      }
      else if (steps >= 0) {
        distance_restante = (steps - motor.distanceLeft());
      }
    }
    else {
      // si on quitte la pause, on repasse en fonctionnement
      esp_bluetooth.writeData("1");
      // on recharge le temps / le nombre de pas restant
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
  // mode "4" est un mode d'attente de fin de pause, rien a faire
  else if (value == "4") {

  }
  // sinon, une data est reçue
  else {
    // si on a recu la data on décode
    esp_bluetooth.decode();

    // récupération des données reçues
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

   
    // récupération du temps actuel comme temps de démarrage de la rotation
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
