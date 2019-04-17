#include "ESP_bluetooth.h"
#include "MoteurBluetooth.h"
#include "bluetooth.h"
#include "Instruction.h"
#include "QueueList.h"
#include "CameraThread.h"
#include "lcd.h"

MoteurBluetooth moteur("4fafc201-1fb5-459e-8fcc-c5c9c331914b", "beb5483e-36e1-4688-b7f5-ea07361b26a8");
CameraThread camera;

ESP_bluetooth esp;
Bluetooth telephone;
Lcd lcd;

QueueList<Instruction> instructions;
Instruction instructionEnCours;
Instruction newInstr;

int* values;
String datagramme;
int commandeEnCours;

void setup() {
  Serial.begin(115200);
  
  telephone.begin();
  lcd.begin();


  camera.begin();
  esp.begin();
  esp.scan();

  

}

void loop() {
    if (telephone.receive()){
      Serial.print("Data received : ");
      Serial.println(telephone.getData());
      values = telephone.decode();

      lcd.setValues(values);
      
      switch(values[MODE]){
        case 0: // mode programmé
          Serial.println(" Mode programmé");
          for (int i=0; i<values[NOMBRE_DE_PHOTOS]; i++){
             datagramme = "creation,"+String(values[ID_COMMANDE])+","+String(2*i+1)+",moteur,"+moteur.createDatagramme(values);
             telephone.print(datagramme);
             newInstr.id_commande = values[ID_COMMANDE];
             newInstr.id_instruction = 2*i+1;
             newInstr.target = &moteur;
             newInstr.data = moteur.createDatagramme(values);
             instructions.push(newInstr);
             
             datagramme = "creation,"+String(values[ID_COMMANDE])+","+String(2*i+2)+",camera,"+camera.createDatagramme(values);
             telephone.print(datagramme);
             newInstr.id_commande = values[ID_COMMANDE];
             newInstr.id_instruction = 2*i+2;
             newInstr.target = &camera;
             newInstr.data = camera.createDatagramme(values);
             instructions.push(newInstr);
          }
          break;

          
        case 1: // mode temps reel
          Serial.println(" Mode temps réel");
          datagramme = "creation,"+String(values[ID_COMMANDE])+","+String(1)+",moteur,"+moteur.createDatagramme(values);
          telephone.print(datagramme);
          newInstr.id_commande = values[ID_COMMANDE];
          newInstr.id_instruction = 1;
          newInstr.target = &moteur;
          newInstr.data = moteur.createDatagramme(values);
          instructions.push(newInstr);
          break;
        case 2:
          break;
        case 3:
          instructionEnCours.target->write("3");
          break;
        case 4:
          instructionEnCours.target->write("2");
          break;
        case 5:
          break;
        case 6:
          break;
        case 7:
          if (values[2]){
            Serial.println("Connexion au moteur");
            esp.connect(&moteur);
          }
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
