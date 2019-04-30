#include "CameraThread.h"

String data="0";
int pinCamera[9];
int relays_number=7;
int values_camera[3];



// fonction de décodage du message
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


// fonction exécutée par le thread en continue
void* run(void* argument) {
  // équivalent du setup
  int temps_pause;
  int nb_appareils;
  bool pause = false;


  // équivalent du loop
  while (true) {
    String d = data; // lecture de la chaine partagée
    
    // si on est à 0, c'est qu'on est dispo, rien à faire de particulier
    if (d == "0") {

    }
    // si on est à 1, c'est que la tache est en cours
    else if (d == "1") {
      // démarrage de la prise de prhotos
      Serial.print("Starting ");
      Serial.print(nb_appareils);
      Serial.println(" photos");
      
      // prise de photos avec chaque caméras
      for (int i = 0; i < nb_appareils; i++) {
        Serial.print("Photo avec l'appareil ");
        Serial.println(pinCamera[i]);         
        digitalWrite(pinCamera[i], HIGH);
        digitalWrite(LED, HIGH);
        delay(1500);  // delay de 1.5 secondes pour être sur que la photo est bien déclanchée
        digitalWrite(LED, LOW);
        digitalWrite(pinCamera[i], LOW);

        delay(temps_pause); // on attend le temps donné comme temps de pause entre les photos
      }

      Serial.println("Photo finished");
      
      // une fois que c'est fini, on peut se mettre à 2 pour indiquer que la prise est finies
      data = "2";
    }
    // si on est à 2 on a rien à faire
    else if (d == "2") { 

    }
    // si on est à 3, c'est qu'une pause est activée/desactivée
    else if (d == "3") {
      pause = !pause;
      if (pause) data = "1"; // si la pause était déja activée, on reprend l'action
      else data = "4";      // on passe en attente de fin de pause
    }
    // une pause est en cours, rien à faire
    else if (d == "4") {

    }

    // si le message est plus long qu'1 caractère, c'est que c'est un datagramme, qu'il faut décoder et interpréter
    else if (d.length() > 1){
      decode(d);
      if (values_camera[0] == 0) {
        temps_pause = values_camera[1];
        nb_appareils = values_camera[2];
      } else {
        temps_pause = 0;
        nb_appareils = values_camera[2];
      }
      // on écrit 1 pour indiquer que le traitement est en cours
      data = "1"; 
    }
    delay(100);
    
  }
}

// démarrage du thread
void CameraThread::begin() {
  int argument = 0;
  pthread_create(&thread, NULL, run, (void*) argument);
}

// fonction d'écriture dans le thread
void CameraThread::write(String d) {
  data = d;
}

// fonction de lecture dans le thread
String CameraThread::read() {
  return data;
}

// fonction de création du datagramme à partir des valeurs du téléphone
String CameraThread::createDatagramme(int* values) {
  String datagramme = String(0) + "," + String(values[PAUSE_ENTRE_CAMERAS]) + ",";
  if (values[NOMBRE_DE_CAMERAS] > nb_camera){
    datagramme += String(nb_camera);
  }
  else datagramme += String(values[NOMBRE_DE_CAMERAS]);
  return datagramme;
}

// donne le nombre de caméras et les numeros des caméras connectées
void CameraThread::setCameras(int nb_camera, int* cameras) {
    this->nb_camera = nb_camera;
    for (int i=0; i<nb_camera; i++){
    pinCamera[i] = cameras[i];
  }
  
  // déclaration des cameras comme sortie
  for (int i = 0; i < nb_camera; i++) {
    pinMode(pinCamera[i], OUTPUT);
    digitalWrite(pinCamera[i], LOW);
  }
}
