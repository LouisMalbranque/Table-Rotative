#include "ESP_bluetooth.h"
#include "MoteurBluetooth.h"
#include "bluetooth.h"
#include "Instruction.h"
#include "QueueList.h"
#include "CameraThread.h"
#include "lcd.h"
#include "CameraBluetooth.h"

// création des objets pour les péripheriques
MoteurBluetooth moteur("4fafc201-1fb5-459e-8fcc-c5c9c331914b", "beb5483e-36e1-4688-b7f5-ea07361b26a8");
CameraThread camera;

CameraBluetooth* camerabt[] = {new CameraBluetooth("1c1e2ea0-7c18-4c35-b38d-04aa84086d66","238df85b-af2f-4817-841f-7ce4330ad0a8"),
                               new CameraBluetooth("1540c1dc-b7a8-484d-bfb6-6c5897339ab3","54b2a4c4-c9ce-41bb-9441-705981242337")};

Peripherique* camerasConnectees[10]; 


ESP_bluetooth esp;
Bluetooth telephone;
Lcd lcd;


// liste d'instruction qui garantie l'execution des instructions dans le bon ordre et sans désynchronisations
QueueList<Instruction> instructions;
Instruction instructionEnCours;


int* values;
String datagramme;
int commandeEnCours;

void setup() {
  Serial.begin(115200);

  pinMode(LED,OUTPUT);
  digitalWrite(LED,LOW);
  
  telephone.begin();
  lcd.begin();

  camera.begin();
  esp.begin();  

  pinMode(RESET, INPUT);
  attachInterrupt(digitalPinToInterrupt(RESET), interrupt, FALLING);
}

void loop() {

//*************************************************************************************//
//*************************************************************************************//
//*************************************************************************************//
//*********************   RECEPTION DES DONNEES TELEPHONE    **************************//
//*************************************************************************************//
//*************************************************************************************//
//*************************************************************************************//
//*************************************************************************************//
  
    if (telephone.receive()){
      Serial.print("Data received : ");
      Serial.println(telephone.getData());
      // le message reçu est décodée et renvoie un tableau d'entier
      values = telephone.decode();

      // le lcd récupère les données reçus
      lcd.setValues(values);

      int mode = values[MODE];
     

      // mode programmé
      if (mode == 0){         
        Serial.println(" Mode programmé");
        
        for (int i=0; i<values[NOMBRE_DE_PHOTOS]; i++){
          
          // creation instruction moteur
           datagramme = "creation,"+String(values[ID_COMMANDE])+","+String(2*i+1)+",moteur,"+moteur.createDatagramme(values);
           telephone.print(datagramme);
           Instruction newInstr1 = {values[ID_COMMANDE], 2*i+1, &moteur, moteur.createDatagramme(values)};
           instructions.push(newInstr1);
          
          // si une ou plusieurs caméra thread, creation des instructions
           int premiereCameraBluetooth = 0;
           if (camera.nb_camera > 0){
              datagramme = "creation,"+String(values[ID_COMMANDE])+","+String(2*i+2)+",camera thread,"+camera.createDatagramme(values);
              telephone.print(datagramme);
              Instruction newInstr2 = {values[ID_COMMANDE], 2*i+2, &camera, camera.createDatagramme(values)};
              instructions.push(newInstr2);
              premiereCameraBluetooth = 1;
           }
          // creation instruction camera bluetooth
           for (int j = premiereCameraBluetooth; j<values[NOMBRE_DE_CAMERAS] + premiereCameraBluetooth - camera.nb_camera; j++){
             datagramme = "creation,"+String(values[ID_COMMANDE])+","+String(2*i+2)+",camera " + String(j) + ","+camerasConnectees[j]->createDatagramme(values);
             telephone.print(datagramme);
             Instruction newInstr2 = {values[ID_COMMANDE], 2*i+2, camerasConnectees[j], camerasConnectees[j]->createDatagramme(values)};
             instructions.push(newInstr2);
           }
        }
      }

      //mode temps réel
      else if (mode == 1){
        // création de l'instruction moteur correspondante
        Serial.println(" Mode temps réel");
        datagramme = "creation,"+String(values[ID_COMMANDE])+","+String(1)+",moteur,"+moteur.createDatagramme(values);
        telephone.print(datagramme);
        Instruction newInstr = {values[ID_COMMANDE], 1, &moteur, moteur.createDatagramme(values)};
        instructions.push(newInstr);
      }

      // pause
      else if (mode == 3){
        // le périphérique en cours reçoit un "3", il se met en pause (s'il écoute)
        instructionEnCours.target->write("3");
      }

      // stop instruction
      else if (mode == 4){
        // force la cible à s'arreter immédiatement (s'il écoute)
        instructionEnCours.target->write("2");
      }

      // magneto focus stacking
      else if (mode == 5){
        // création instruction
        Instruction newInstr = {values[ID_COMMANDE], 1, camerabt[ values[NUMERO_CAMERA] ], camerabt[ values[NUMERO_CAMERA] ] -> createDatagramme(values)};
        instructions.push(newInstr);
      }

      // connexion aux périphériques
      else if (mode == 7){
        // scan des périphériques 
        esp.scan();
        // connexion aux camera threads
        int tmp[9];
        int nombre_de_camera = 0;
        for (int i=0; i<9; i++){
          if (values[i+3]){
            Serial.print("Camera ");
            Serial.print(CAMERA[i]);
            Serial.println(" connectée");
            tmp[nombre_de_camera] = CAMERA[i];
            nombre_de_camera++;
          }
        }
        int cameras[nombre_de_camera];
        for (int i=0; i<nombre_de_camera; i++){
          cameras[i] = tmp[i];
        }
        camera.setCameras(nombre_de_camera, cameras);
                
        int indiceCameraBluetooth = 0;
        if (nombre_de_camera > 0){
          camerasConnectees[0] = &camera;
          indiceCameraBluetooth = 1;
        }
        // connexion aux cameras bluetooth
        for (int i=0; i<9; i++){
          if (values[i+12]){
            Serial.print("Connexion à la caméra ");
            Serial.println(i);
            esp.connect(camerabt[i]);
            camerasConnectees[indiceCameraBluetooth] = camerabt[i];
            indiceCameraBluetooth++;
          }
        }
        // connexion au moteur
        if (values[2]){
          Serial.println("Connexion au moteur");
          esp.connect(&moteur);
        }
        String datagramme = "connexion";
        telephone.print(datagramme);
        digitalWrite(LED,HIGH);
      }

      // paramétrage focus stacking
      else if (mode == 8){
        int params[8];
        for (int i=0; i<8; i++){
          params[i] = values[i+3]; 
        }
        camerabt[values[2]]->setParams(params);
        Instruction newInstr = {-1, 1, camerabt[ values[2] ], camerabt[ values[2] ] -> createDatagramme(values)};
        instructions.push(newInstr);
      }
    }

//*************************************************************************************//
//*************************************************************************************//
//*************************************************************************************//
//***********************   TRAITEMENT DES INSTRUCTIONS    ****************************//
//*************************************************************************************//
//*************************************************************************************//
//*************************************************************************************//
//*************************************************************************************//

    if (!instructions.isEmpty()){
      instructionEnCours = instructions.peek();
      if (instructionEnCours.target->read() == "0"){
        
        Serial.print("Sending datagramme : ");
        Serial.println(instructionEnCours.data);
        
        datagramme = "en cours,"+String(instructionEnCours.id_commande)+","+String(instructionEnCours.id_instruction);
        telephone.print(datagramme);
        
        instructionEnCours.target->write(instructionEnCours.data);
      }

      if (instructionEnCours.target->read() == "1"){
      }

      if (instructionEnCours.target->read() == "2"){
        Serial.println("Instruction finished");

        lcd.resetValues();
        
        instructionEnCours.target->write("0");
        instructions.pop();
        delay(10);

        if (instructions.isEmpty()) telephone.print("fini,"+String(instructionEnCours.id_commande));
        else if (instructions.peek().id_commande != instructionEnCours.id_commande) telephone.print("fini,"+String(instructionEnCours.id_commande));
      }
    }
    lcd.display();
}

void interrupt(){
  ESP.restart();
}
