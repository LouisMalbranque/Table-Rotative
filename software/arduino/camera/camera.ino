#include "moteur.h"
#include "esp_server.h"
#include "appareil.h"

// creation des objets
Motor motor;
ESP_server esp_server;
Appareil appareil;

// variables globales
String value;
int nb_photos = 0;
int temps_pause = 0;
int pas_apres_photos[9];
int mode = 0;
int nombre_de_pas = 0;

void setup() {
  Serial.begin(115200);

  // demarrage des modules
  motor.begin();
  esp_server.begin();
  esp_server.writeData("0");
  appareil.begin(PIN_APPAREIL);

  // parametrage des vitesses accelerations du moteur
  motor.setParams(4000, 400, 1);



  Serial.println("Initialisation terminée.");
}

void loop() {
  // récupération des charactéristiques du serveur
  value = esp_server.read();

  // si "0", on est disponible donc rien a faire
  if (value == "0") {

  }
  // si "1", on est en cours
  else if (value == "1") {
    if (mode == 0){
      // mode prise de vue
      Serial.println("Début des photos");
      for (int i=0; i<nb_photos; i++){
        // boucle autant de fois qu'il n'y a de photo
        Serial.print("Photo n");
        Serial.println(i);
        
        // prise de photo avec activation pdt 1 seconde
        appareil.prendrePhoto(1000);
        
        // mise à zéro du moteur pour la prochaine rotation
        motor.setZero();

        // rotation de moteur 
        motor.rotate(pas_apres_photos[i]);
        while(motor.isRotating()){
          motor.run();
        }
        
        // pause entre les photos
        delay(temps_pause);
      }
    }

    // mode temps réel pour le réglage
    else if (mode == 1){
      Serial.print("Rotation de ");
      Serial.print(nombre_de_pas);
      Serial.println(" pas");

      // mise à zéro du moteur pour la prochaine rotation
        motor.setZero();

      // rotation de moteur 
      motor.rotate(nombre_de_pas);
      while(motor.isRotating()){
        motor.run();
      }
    }
    

    // on remet le périph disponible
    esp_server.writeData("2");
  }
  // mode 2 = tache terminée, rien a faire
  else if (value == "2") {

  }
  // pause, non implémentée
  else if (value == "3") {
   
  }
  // pause, non implémentée
  else if (value == "4") {

  }
  // sinon, une nouvelle data est reçue
  else {
    Serial.print("Data received: ");
    Serial.println(value);
    // décodage
    esp_server.decode();
    
    // remise à zéro du moteur
    motor.setZero();

    mode = esp_server.getValue(MODE);
    // mode normal
    if (mode == 0){
      temps_pause = esp_server.getValue(TEMPS_PAUSE);
      nb_photos = esp_server.getValue(NOMBRE_DE_FOCUS);
      for (int i = 0; i < nb_photos; i++){
        pas_apres_photos[i] = esp_server.getValue(PAS_ENTRE_PHOTO + i);
      }
    }

    // mode magneto
    else if (mode == 1){
      if (!esp_server.getValue(DIRECTION)) nombre_de_pas = esp_server.getValue(NOMBRE_DE_PAS);
      else nombre_de_pas = -esp_server.getValue(NOMBRE_DE_PAS);
    }
    
    // l'ordre est reçu, on passe en mode 1 pour passer "en cours" 
    esp_server.writeData("1");
  }  
}
