#include "CameraThread.h"

String data="0";
int pinCamera[9];
int relays_number=7;
int values_camera[3];




void decode(String d) {
  char* valuesent;
  int i = 0;
  if (d != "") {
    i = 0;
    char buf[d.length() + 1];
    d.toCharArray(buf, d.length() + 1);
    valuesent = strtok(buf, ",");
    while (valuesent != NULL) {
      values_camera[i] = atoi(valuesent);
      i++;
      valuesent = strtok(NULL, ",");
    }
    d = "";
  }
}

void* run(void* argument) {

  int temps_pause;
  int nb_appareils;

  while (true) {
    String d = data;
    if (d == "0") { //dispo

    }
    else if (d == "1") { //en cours
      Serial.print("Starting ");
      Serial.print(nb_appareils);
      Serial.println(" photos");
      
      for (int i = 0; i < nb_appareils; i++) {
        Serial.print("Photo avec l'appareil ");
        Serial.println(pinCamera[i]);         
        digitalWrite(pinCamera[i], HIGH);
        digitalWrite(LED, HIGH);
        delay(1500);
        digitalWrite(LED, LOW);
        digitalWrite(pinCamera[i], LOW);

        delay(temps_pause);
      }
      Serial.println("Photo finished");
      data = "2";
    }
    else if (d == "2") { //fini

    }
    else if (d == "3") { //pause

    }
    else if (d == "4") { //pause en cours

    }
    else if (d.length() > 1){
      decode(d);
      if (values_camera[0] == 0) {
        temps_pause = values_camera[1];
        nb_appareils = values_camera[2];
      } else {
        temps_pause = 0;
        nb_appareils = values_camera[2];
      }
      data = "1"; 
    }
    delay(100);
    
  }
}
void CameraThread::begin() {
  int argument = 0;
  pthread_create(&thread, NULL, run, (void*) argument);
}

void CameraThread::write(String d) {
  data = d;
}

String CameraThread::read() {
  return data;
}

String CameraThread::createDatagramme(int* values) {
  String datagramme = String(0) + "," + String(values[PAUSE_ENTRE_CAMERAS]*1000) + "," + String(values[NOMBRE_DE_CAMERAS]);
  return datagramme;
}

void CameraThread::setCameras(int nb_camera, int* cameras) {
    for (int i=0; i<nb_camera; i++){
    pinCamera[i] = cameras[i];
  }
  
  for (int i = 0; i < nb_camera; i++) {
    pinMode(pinCamera[i], OUTPUT);
    digitalWrite(pinCamera[i], LOW);
  }
}
