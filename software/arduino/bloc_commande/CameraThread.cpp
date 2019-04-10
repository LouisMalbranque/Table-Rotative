#include "CameraThread.h"

String data="0";
unsigned int pinRelay[9] = {CAMERA1,CAMERA2,CAMERA3,CAMERA4,CAMERA5,CAMERA6,CAMERA7,CAMERA8,CAMERA9};
int relays_number=9;
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
        digitalWrite(pinRelay[i], HIGH);
        digitalWrite(LED, HIGH);
        delay(1500);
        digitalWrite(LED, LOW);
        digitalWrite(pinRelay[i], LOW);

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
  pinMode(LED, OUTPUT);
  for (int i = 0; i < relays_number; i++) {
    digitalWrite(pinRelay[i], LOW);
    pinMode(pinRelay[i], OUTPUT);
  }

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
  String datagramme = String(0) + "," + String(values[PAUSE_BETWEEN_CAMERA]) + "," + String(values[CAMERA_NUMBER]);
  return datagramme;
}
