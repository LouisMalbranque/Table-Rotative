#include "BLE_client.h"
#include "MoteurBluetooth.h"
#include "bluetooth.h"
#include "Instruction.h"
#include "QueueList.h"
#include "CameraThread.h"
#include "lcd.h"
#include "CameraBluetooth.h"

/* code principale du boitier de commande
  
  gere les périphériques bluetooth
  gere les communications avec le téléphone
  gere le séquençage des commandes et le traitement des instructions élémentaires

*/


// création des objets pour les péripheriques
MoteurBluetooth moteur("4fafc201-1fb5-459e-8fcc-c5c9c331914b", "beb5483e-36e1-4688-b7f5-ea07361b26a8"); // moteur créé
// MoteurBluetooth moteur2("ServiceUUID", "CharacteristicsUUID"); pour créer un nouvel object moteur

CameraThread camera; // caméras connectées directement au bloc de commande (compte pour une seule caméra même si plusieurs appareils y sont connectés

CameraBluetooth* camerabt[] = {new CameraBluetooth("1c1e2ea0-7c18-4c35-b38d-04aa84086d66","238df85b-af2f-4817-841f-7ce4330ad0a8"), // liste des caméras focus stacking créées
                               new CameraBluetooth("1540c1dc-b7a8-484d-bfb6-6c5897339ab3","54b2a4c4-c9ce-41bb-9441-705981242337")
                               // new CameraBluetooth("ServiceUUID", "CharacteristicsUUID") pour créer une nouvelle caméra bluetooth
                              };

Peripherique* camerasConnectees[10]; // liste des caméras connectées, elle est remplie lors de la reception des périphériques à connecter 

ESP_bluetooth esp;      // client BLE 
Bluetooth telephone;    // gestion du bluetooth série avec le téléphone
Lcd lcd;                // ecran LCD controllé par i2c


// liste d'instruction qui garantie l'execution des instructions dans le bon ordre et sans désynchronisations
QueueList<Instruction> instructions;
Instruction instructionEnCours;

// divers
int* values;  
String datagramme;
int commandeEnCours;





void setup() {
  Serial.begin(115200);

  // configuration de la led de statut
  pinMode(LED,OUTPUT);
  digitalWrite(LED,LOW);

  // démarrage de la gestion du téléphone
  telephone.begin();

  // démarrage de la gestion du LCD
  lcd.begin();

  // démarrage du thread pour la gestion des cameras connectées sur le boitier de commande
  camera.begin();

  // démarrage du client BLE pour la communication avec périphériques
  esp.begin();  

  // configuration du bouton d'interruption
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

      // récupération et traitement du MODE
      int mode = values[MODE];

      // mode programmé
      if (mode == 0){         
        Serial.println(" Mode programmé");
        
        for (int i=0; i<values[NOMBRE_DE_PHOTOS]; i++){
          
          // creation instruction moteur
           datagramme = "creation,"+String(values[ID_COMMANDE])+","+String(2*i+1)+",moteur,"+moteur.createDatagramme(values);
           telephone.print(datagramme); // envoie d'une info de création au téléphone
           Instruction newInstr1 = {values[ID_COMMANDE], 2*i+1, &moteur, moteur.createDatagramme(values)}; // création de l'instruction
           instructions.push(newInstr1); // ajout de l'instruction à la file
          
          // si une ou plusieurs caméra thread est utilisée, creation des instructions
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

        // si une ou plusieurs cameras sont connectées au bloc de commande, l'objet camera est ajouté à la liste des cameras disponnibles
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


        // envoie d'un message au téléphone lui indicant que les connexions sont terminées
        String datagramme = "connexion";
        telephone.print(datagramme);
        // allumage de la led de statut
        digitalWrite(LED,HIGH);
      }

      // paramétrage focus stacking
      else if (mode == 8){
        int params[8];
        for (int i=0; i<8; i++){
          params[i] = values[i+3]; 
        }
        // la caméra ciblée reçoit ses paramètres de focus stacking
        camerabt[values[2]]->setParams(params);
        // création d'une instruction pour que la caméra reviennne à sa position initiale
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
// cette partie ne devrait pas avoir besoin d'être modifiée pour l'ajout de nouveaux modes ou de nouveaux périphériques



    // si la file d'instruction n'est pas vide, il faut traiter la prochaine
    if (!instructions.isEmpty()){
      // on récupère l'instruction en cours, qui est la première instruction dans la liste
      instructionEnCours = instructions.peek();



      // si la cible de cette instruction est à 0, ça signifie qu'il est disponible, donc qu'il n'a pas encore reçu le datagramme, on lui écrit
      if (instructionEnCours.target->read() == "0"){
        Serial.print("Sending datagramme : ");
        Serial.println(instructionEnCours.data); 

        // écriture du datagramme dans la cible
        instructionEnCours.target->write(instructionEnCours.data);

        // envoie d'une information au téléphone pour déclarer le démarrage de cette instruction
        datagramme = "en cours,"+String(instructionEnCours.id_commande)+","+String(instructionEnCours.id_instruction);
        telephone.print(datagramme);
      }


      // si la cible est à 1, c'est que l'instruction est en cours, pas besoin de faire quoi que ce soit
      if (instructionEnCours.target->read() == "1"){
        // si une action doit être réalisée pendant qu'un périphérique est en cours de fonctionnement, c'est ici
      }


      // si la cible est à 2, c'est que l'action est finie, on peut donc libérer ce périphérique et passer à la prochaine instruction
      if (instructionEnCours.target->read() == "2"){
        Serial.println("Instruction finished");

        // reset des informations écrites sur le lcd
        lcd.resetValues();
        
        // le périphérique est libéré
        instructionEnCours.target->write("0");

        
        // on supprime le premier élément de la file d'instruction pour passer à la suivante
        instructions.pop();

        
        delay(10);

        // si cette instruction était la dernière instruction d'une commande, on notifie le téléphone que la commande est terminée
        if (instructions.isEmpty()) telephone.print("fini,"+String(instructionEnCours.id_commande));
        else if (instructions.peek().id_commande != instructionEnCours.id_commande) telephone.print("fini,"+String(instructionEnCours.id_commande));
      }
    }

    // actualisation de l'affichage LCD
    lcd.display();
}


// routine d'interruption attachée sur le bouton de reset
void interrupt(){
  ESP.restart();
}
