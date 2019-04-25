#include "moteur.h"
#include "esp_server.h"
#include "appareil.h"

Motor motor;
ESP_server esp_server;
Appareil appareil;

String value;
int nb_photos = 0;
int temps_pause = 0;
int pas_apres_photos[9];
int mode = 0;
int nombre_de_pas = 0;

void setup() {
  Serial.begin(115200);

  motor.begin();
  esp_server.begin();
  esp_server.writeData("0");

  motor.setParams(4000, 400, 1);

  appareil.begin(PIN_APPAREIL);

  Serial.println("Début loop");
}

void loop() {

  value = esp_server.read();
  if (value == "0") {

  }
  else if (value == "1") {
    if (mode == 0){
      Serial.println("Début des photos");
      for (int i=0; i<nb_photos; i++){
        Serial.print("Photo n");
        Serial.println(i);
        
        appareil.prendrePhoto(1000);
        
        motor.setZero();
        motor.rotate(pas_apres_photos[i]);
        while(motor.isRotating()){
          motor.run();
        }
  
        delay(temps_pause);
      }
    }
    else if (mode == 1){
      Serial.print("Rotation de ");
      Serial.print(nombre_de_pas);
      Serial.println(" pas");
      motor.setZero();
      motor.rotate(nombre_de_pas);
      while(motor.isRotating()){
        motor.run();
      }
    }
      
    esp_server.writeData("2");
  }
  else if (value == "2") {

  }
  else if (value == "3") {
   
  }
  else if (value == "4") {

  }
  else {
    Serial.print("Data received: ");
    Serial.println(value);
    esp_server.decode();
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
    
    esp_server.writeData("1");
  }
  
}
